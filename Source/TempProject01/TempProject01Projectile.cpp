// Copyright Epic Games, Inc. All Rights Reserved.

#include "TempProject01Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShootingTarget.h"

ATempProject01Projectile::ATempProject01Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATempProject01Projectile::OnOverlap);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set assets
	UStaticMeshComponent* Sphere = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	Sphere->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/Assets/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Assets/BasicAsset02.BasicAsset02"));
	if (SphereAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		Sphere->SetStaticMesh(SphereAsset.Object);
		Sphere->SetMaterial(0, MaterialAsset.Object);
	}

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATempProject01Projectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// this->Destroy();
	}
}