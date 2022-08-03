// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "TempProject01Character.h"
#include "MyGameInstance.h"

// Sets default values
ABuffPickup::ABuffPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create and setup collision component
	USphereComponent* BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	BaseCollisionComponent->SetSphereRadius(64.0f);
	BaseCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuffPickup::OnOverlap);
	this->SetRootComponent(BaseCollisionComponent);
	// Load assets from file
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Game/Assets/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Assets/BasicAsset03.BasicAsset03"));
	// Create and setup mesh components if loaded successfully
	UStaticMeshComponent* CubeComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube1"));
	CubeComponent1->SetupAttachment(BaseCollisionComponent);
	CubeComponent1->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	CubeComponent1->SetRelativeScale3D(FVector(0.18f, 0.18f, 0.54f));
	UStaticMeshComponent* CubeComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube2"));
	CubeComponent2->SetupAttachment(BaseCollisionComponent);
	CubeComponent2->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	CubeComponent2->SetRelativeScale3D(FVector(0.54f, 0.18f, 0.18f));
	if (CubeAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		CubeComponent1->SetStaticMesh(CubeAsset.Object);
		CubeComponent1->SetMaterial(0, MaterialAsset.Object);
		CubeComponent2->SetStaticMesh(CubeAsset.Object);
		CubeComponent2->SetMaterial(0, MaterialAsset.Object);
	}
	// Add a RotatingMovementComponent so that it can rotate constantly
	URotatingMovementComponent* RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");
	this->AddInstanceComponent(RotatingMovement);
}

// Called when the game starts or when spawned
void ABuffPickup::BeginPlay()
{
	Super::BeginPlay();
	this->GameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void ABuffPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuffPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATempProject01Character* Character = Cast<ATempProject01Character>(OtherActor);
		if (Character != nullptr)
		{
			this->GameInstance->BuffLevel++;
			this->Destroy();
		}
	}
}