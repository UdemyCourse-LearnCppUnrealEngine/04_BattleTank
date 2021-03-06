// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "BattleTank.h"
#include "Class.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


//Forward Declarations
class ATank; 
class UInputComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;
		

private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//deafult constructor
	ATankPlayerController();
	
	bool isTankPossessed = false;

	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();	

	// Determine where the crosshair hit the world
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333f;

	// Maximal Range
	UPROPERTY(EditAnywhere)
		float MaxRange = 100000.f;

};
