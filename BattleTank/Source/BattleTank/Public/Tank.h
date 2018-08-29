// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declaration
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

// TODO In case anyone else is having this issue, we make some changes in the video"Working Round Awkward Bugs" (Lecture 150 at time of writing), which fixed the issue for me.
// The solution was to change the Collision Presets on the Turret and Barrel in the Tank blueprint, to “NoCollision” from “BlockAllDynamic”.Note, you may have to remove hidecategories = ('Collision') 
// in your TankTurret.h and TankBarrel.h files first, to allow you to see the collision settings to change in the blueprint.

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere, Category = Setup) // TODO EditAnywhere =>EditDefaultsOnly
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeinSeconds = 14;
	
	double LastFireTime = 0;

	//Local barrel reference for spawn of projectile
	UTankBarrel * Barrel = nullptr;
		
};
