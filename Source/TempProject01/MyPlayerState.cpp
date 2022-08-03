// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "ShootingTarget.h"
#include "BuffPickup.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerState::AMyPlayerState()
{
	this->CurrentScore = 0;
	this->PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> OutputActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AShootingTarget::StaticClass(), OutputActors);
	EnemyLeft = OutputActors.Num();
	CountTick = 0;
}

void AMyPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->EnemyLeft == 0)
	{
		if (UGameplayStatics::GetCurrentLevelName(this->GetWorld()) == TEXT("Level_01"))
		{
			UGameplayStatics::OpenLevel(this->GetWorld(), TEXT("Level_02"));
		}
		else
		{
			UGameplayStatics::OpenLevel(this->GetWorld(), TEXT("Level_03"));
		}
	}
	if (UGameplayStatics::GetCurrentLevelName(this->GetWorld()) == TEXT("Level_03")) {
		static ABuffPickup* BuffActor = nullptr;
		static FActorSpawnParameters ActorSpawnParams;
		static TArray<FVector> PossibleSpawnLocations = {
			FVector(1500.0, 1800.0, 0.0),
			FVector(2100.0, 1350.0, 0.0),
			FVector(2100.0, 1800.0, 200.0),
			FVector(900.0, 1800.0, 200.0),
			FVector(1800.0, 2700.0, 0.0),
			FVector(1950.0, 900.0, 200.0)
		};
		CountTick++;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		int32 SpawnLocationIndex = rand() % 6;
		if (CountTick == 180 || CountTick == 1020 || CountTick == 1920)
		{
			BuffActor = this->GetWorld()->SpawnActor<ABuffPickup>(ABuffPickup::StaticClass(), PossibleSpawnLocations[SpawnLocationIndex], FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
		}
		else if (CountTick == 780 || CountTick == 1620)
		{
			BuffActor->Destroy();
		}
	}
}

int32 AMyPlayerState::CountTick = 0;
