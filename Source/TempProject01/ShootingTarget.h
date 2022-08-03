// https://github.com/C6H6Cl6-Alien

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "ShootingTarget.generated.h"

class UStaticMeshComponent;
class AMyPlayerState;
class UMyGameInstance;

UCLASS()
class TEMPPROJECT01_API AShootingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the actor collide with others
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// void OnHit(UPrimitiveComponent* Component);

public:
	// Components of the actor: when different parts of the target are shot, the player get different scores
	USphereComponent* Head;
	UCapsuleComponent* Chest;
	UCapsuleComponent* Belly;
	UCapsuleComponent* LeftArm;
	UCapsuleComponent* RightArm;
	UCapsuleComponent* LeftArtifice;
	UCapsuleComponent* RightArtifice;
	UCapsuleComponent* LeftLeg;
	UCapsuleComponent* RightLeg;
	UCapsuleComponent* LeftFoot;
	UCapsuleComponent* RightFoot;

	UPROPERTY(BlueprintReadWrite)
	AMyPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite)
	UMyGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite)
	int32 HPLeft;

private:

	void SetCapsuleComponent(const FName& Name, UCapsuleComponent*& Component, const FVector& Location, const FRotator& Rotation, const FVector& Scale);

	/** When the target is shot, this function will be called to calculate
	 *  HP Lost value and how many scores the player will obtain
	 */
	void BeHit(int32 HPLost);
};
