// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "EngineMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h" 



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//found out the actual position of the barrel
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	
	return false;
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
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No aiming for %s is possible"), *TankName);
	}
	
}