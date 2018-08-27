// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurrentToSet)
{
	TankAimingComponent->SetTurretReference(TurrentToSet);
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 
void ATank::AimAt (FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


// 
void ATank::Fire()
{	
	if (!Barrel) { return; }
	//spawn the projectile at the socket location of the barrel
	FVector Location = Barrel->GetSocketLocation("Projectile");
	FRotator Rotaion = Barrel->GetSocketRotation("Projectile");
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotaion);
	UE_LOG(LogTemp, Warning, TEXT("Firing from Location %s"), *Location.ToString());
}