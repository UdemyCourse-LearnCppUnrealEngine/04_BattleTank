// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "BattleTank.h"
#include "Class.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	ATank * GetControlledTank() const;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	//deafult constructor
	ATankPlayerController();

private:
	bool isTankPossessed = false;
	
};
