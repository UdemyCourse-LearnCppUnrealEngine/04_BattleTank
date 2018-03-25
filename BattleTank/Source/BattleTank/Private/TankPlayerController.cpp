// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
// include draw debug helpers header file
#include "DrawDebugHelpers.h"

//#define DEBUG_OUTPUT	

void  ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"))
	ATank	* PossesedTank = GetControlledTank();
	if (PossesedTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is possessed at the BeginPlay!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s is possessed!"), *PossesedTank->GetName());
		isTankPossessed = true;
	}
}


void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	AimTowardsCrosshair();
}

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default 
}


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;	
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Error, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
	//Get world location of linetrace through crosshair
	// if it hits landscape 
		//Tell controlled tank to aium at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	// Get the Size of the Screen in Pixel
	GetViewportSize(ViewportSizeX, ViewportSizeY);	
	// Create the 2D Vector pointing on the Crosshair
	FVector2D ScreenLocation = { ViewportSizeX*CrossHairXLocation,  ViewportSizeY*CrossHairYLocation };
	// De-project the Screen Coordinates into World Coordinates
	FVector WorldLocation;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);	
#ifdef DEBUG_OUTPUT
	//Debuging output
	UE_LOG(LogTemp, Warning, TEXT("Screen size: %d x  %d"), ViewportSizeX, ViewportSizeY);
	UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s, WorldLocation: %s, WorldDirection: %s"), *ScreenLocation.ToString(), *WorldLocation.ToString(), *WorldDirection.ToString());
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1, 0, 1);
#endif		
	// Definition of Start and End point for Line Trace: Start is the WorldLocation of the Crosshair
	FVector TraceStart = WorldLocation;
	// Endpoint is the Vector along the WorldDirection, but increased to maximum range
	FVector TraceEnd = WorldLocation + WorldDirection * MaxRange;
	// Creating the Collision Paramters - TODO set this parameters if needed
	FCollisionQueryParams CollisionParams;
	// This will be our OUT Parameter for LineTrace
	FHitResult HitResult;
	// Hit detection against the line from crosshair
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECollisionChannel(ECollisionChannel::ECC_Visibility),
		CollisionParams
		);
	// Actor wich can be hit by line trace
	AActor * HitActor = HitResult.GetActor();
#ifdef DEBUG_OUTPUT
	// Wich location is been hit with our line trace
	//FString HitLocation = HitResult.Location.ToString();
	// Wich Actor is been hit with our line Trace
	//FString ActorName = HitResult.GetActor()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s, Actor: %s"), *HitLocation, *ActorName);
#endif // DEBUG_OUT
	// Output result
	OutHitLocation = HitResult.Location;
	if (HitActor != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

