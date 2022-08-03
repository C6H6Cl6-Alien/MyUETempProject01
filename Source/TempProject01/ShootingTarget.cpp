// https://github.com/C6H6Cl6-Alien


#include "ShootingTarget.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerState.h"
#include "TempProject01Projectile.h"
#include "MyPlayerState.h"
#include "MyGameInstance.h"
#include "TempProject01Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShootingTarget::AShootingTarget()
	: PlayerState(nullptr),
	  GameInstance(nullptr),
	  HPLeft(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set Root Component
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	this->SetRootComponent(DefaultSceneRoot);
	// Load assets from file
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/Assets/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Assets/BasicAsset02.BasicAsset02"));
	// Create and setup mesh components if loaded successfully
	Head = CreateDefaultSubobject<USphereComponent>("Head");
	Head->SetupAttachment(this->RootComponent);
	Head->SetRelativeLocation(FVector(0.0f, 0.0f, 190.0f));
	Head->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	Head->OnComponentBeginOverlap.AddDynamic(this, &AShootingTarget::OnOverlap);
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("HeadMesh");
	MeshComponent->SetupAttachment(Head);
	MeshComponent->SetStaticMesh(SphereAsset.Object);
	MeshComponent->SetMaterial(0, MaterialAsset.Object);
	this->SetCapsuleComponent("Chest", Chest, FVector(0.0f, 0.0f, 148.0f), FRotator(0.0f, 0.0f, 0.0f), FVector(0.4f, 0.6f, 0.4f));
	this->SetCapsuleComponent("Belly", Belly, FVector(0.0f, 0.0f, 111.0f), FRotator(0.0f, 0.0f, 0.0f), FVector(0.4f, 0.6f, 0.34f));
	this->SetCapsuleComponent("LeftArm", LeftArm, FVector(0.0f, -50.0f, 144.0f), FRotator(0.0f, 0.0f, 70.0f), FVector(0.25f, 0.25f, 0.45f));
	this->SetCapsuleComponent("RightArm", RightArm, FVector(0.0f, 50.0f, 144.0f), FRotator(0.0f, 0.0f, -70.0f), FVector(0.25f, 0.25f, 0.45f));
	this->SetCapsuleComponent("LeftArtifice", LeftArtifice, FVector(0.0f, -86.0f, 126.0f), FRotator(0.0f, 0.0f, 55.0f), FVector(0.23f, 0.23f, 0.45f));
	this->SetCapsuleComponent("RightArtifice", RightArtifice, FVector(0.0f, 86.0f, 126.0f), FRotator(0.0f, 0.0f, -55.0f), FVector(0.23f, 0.23f, 0.45f));
	this->SetCapsuleComponent("LeftLeg", LeftLeg, FVector(0.0f, -30.0f, 72.0f), FRotator(0.0f, 0.0f, 25.0f), FVector(0.3f, 0.3f, 0.6f));
	this->SetCapsuleComponent("RightLeg", RightLeg, FVector(0.0f, 30.0f, 72.0f), FRotator(0.0f, 0.0f, -25.0f), FVector(0.3f, 0.3f, 0.6f));
	this->SetCapsuleComponent("LeftFoot", LeftFoot, FVector(0.0f, -50.0f, 24.0f), FRotator(0.0f, 0.0f, 20.0f), FVector(0.27f, 0.27f, 0.55f));
	this->SetCapsuleComponent("RightFoot", RightFoot, FVector(0.0f, 50.0f, 24.0f), FRotator(0.0f, 0.0f, -20.0f), FVector(0.27f, 0.27f, 0.55f));
}

// Called when the game starts or when spawned
void AShootingTarget::BeginPlay()
{
	Super::BeginPlay();
	this->PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
	this->GameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void AShootingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootingTarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// void AShootingTarget::OnHit(UPrimitiveComponent* Component)
{
	USphereComponent* SphereComponent = Cast<USphereComponent>(OverlappedComponent);
	UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(OverlappedComponent);
	if (SphereComponent == this->Head)
	{
		this->BeHit(100);
	}
	else if (CapsuleComponent == this->Chest)
	{
		this->BeHit(70);
	}
	else if (CapsuleComponent == this->Belly)
	{
		this->BeHit(49);
	}
	else if (CapsuleComponent == this->LeftArm || CapsuleComponent == this->RightArm)
	{
		this->BeHit(32);
	}
	else if (CapsuleComponent == this->LeftArtifice || CapsuleComponent == this->RightArtifice)
	{
		this->BeHit(20);
	}
	else if (CapsuleComponent == this->LeftLeg || CapsuleComponent == this->RightLeg)
	{
		this->BeHit(40);
	}
	else if (CapsuleComponent == this->LeftFoot || CapsuleComponent == this->RightFoot)
	{
		this->BeHit(24);
	}
	if (SphereComponent != nullptr || CapsuleComponent != nullptr)
	{
		OtherActor->Destroy();
	}
}

void AShootingTarget::SetCapsuleComponent(const FName& Name, UCapsuleComponent*& Component, const FVector& Location, const FRotator& Rotation, const FVector& Scale)
{
	Component = CreateDefaultSubobject<UCapsuleComponent>(Name);
	Component->SetupAttachment(this->RootComponent);
	Component->SetRelativeLocation(Location);
	Component->SetRelativeRotation(Rotation);
	Component->SetRelativeScale3D(Scale);
	Component->OnComponentBeginOverlap.AddDynamic(this, &AShootingTarget::OnOverlap);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/Assets/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Assets/BasicAsset02.BasicAsset02"));
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(Name.ToString() + "Mesh"));
	MeshComponent->SetupAttachment(Component);
	MeshComponent->SetStaticMesh(CylinderAsset.Object);
	MeshComponent->SetMaterial(0, MaterialAsset.Object);
}

void AShootingTarget::BeHit(int32 HPLost)
{
  if (HPLost >= this->HPLeft)
	{
		this->PlayerState->CurrentScore += HPLost * this->HPLeft * (1.0 + this->GameInstance->BuffLevel * 0.1) / 100;
		this->GameInstance->TotalScore += HPLost * this->HPLeft * (1.0 + this->GameInstance->BuffLevel * 0.1) / 100;
		this->HPLeft = 0;
		this->PlayerState->EnemyLeft--;
		this->Destroy();
	}
	else
	{
		this->PlayerState->CurrentScore += HPLost * HPLost * (1.0 + this->GameInstance->BuffLevel * 0.1) / 100;
		this->GameInstance->TotalScore += HPLost * HPLost * (1.0 + this->GameInstance->BuffLevel * 0.1) / 100;
		this->HPLeft -= HPLost;
	}
}
