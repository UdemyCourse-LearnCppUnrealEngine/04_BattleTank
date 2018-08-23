// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
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
	if (!GetControlledTank()){return;}
	FVector HitLocation;	//Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No HitLocation: %s"), *HitLocation.ToString());
	}
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
#ifdef DEBUG_OUTPUT
	//Debuging output
	UE_LOG(LogTemp, Warning, TEXT("Screen size: %d x  %d"), ViewportSizeX, ViewportSizeY);
#endif	
	// De-project the Screen Coordinates into World Coordinates
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return true;
		}		
	}
	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	// Definition of Start and End point for Line Trace: Start is the WorldLocation of the Crosshair
	APlayerCameraManager * PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	// Endpoint is the Vector along the WorldDirection, but increased to maximum range
	FVector TraceEnd = TraceStart + LookDirection * MaxRange;
	// Creating the Collision Paramters - TODO set this parameters if needed
	FCollisionQueryParams CollisionParams;
	// This will be our OUT Parameter for LineTrace
	FHitResult HitResult;
	// Hit detection against the line from crosshair
#ifdef DEBUG_OUTPUT
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1, 0, 1);
#endif // DEBUG_OUTPUT

	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECollisionChannel(ECollisionChannel::ECC_Visibility),
		CollisionParams
	);	
	// Output result
	OutHitLocation = HitResult.Location;
	AActor * HitActor = HitResult.GetActor();
	if (HitActor != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const
{
	FVector WorldLocation;
	bool wasSuccesfull = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
#ifdef DEBUG_OUTPUT
	//Debuging output
	UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s, WorldLocation: %s, WorldDirection: %s"), *ScreenLocation.ToString(), *WorldLocation.ToString(), *LookDirection.ToString());
#endif	
	return wasSuccesfull;
}