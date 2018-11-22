// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
//Enum for firing state
UENUM()
enum class EFiringState : uint8
{
	
	Reloading,
	Aiming, 
	Locked	
};

//Forward Declaration
class UTankBarrel; 
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel * Barrel = nullptr;	
	UTankTurret * Turret = nullptr;
	void MoveBarrel(FVector AimDirection);

protected:	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

public:	
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//
	void AimAt(FVector HitLocation, float LaunchSpeed);
	// Sets default values for this component's properties
	UTankAimingComponent();
	//Initialising function for AimingComponent
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
};
