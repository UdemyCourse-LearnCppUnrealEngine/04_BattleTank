// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "EngineMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h" 



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO set on false

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

//void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	if (!BarrelToSet) { return; }
//	Barrel = BarrelToSet;
//}
//
//void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
//{
//	if (!TurretToSet) { return; }
//	Turret = TurretToSet;
//}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }
	//found out the actual position of the barrel
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
	return;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorsToIgnore = {};	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false, 
		0.0f, 
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,	// Must be here to prevent the bug occure
		FCollisionResponseParams::DefaultResponseParam, 
		ActorsToIgnore, 
		false
		);
	auto TankName = GetOwner()->GetName();
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No aiming for %s is possible"), *TankName);
	}
	
}