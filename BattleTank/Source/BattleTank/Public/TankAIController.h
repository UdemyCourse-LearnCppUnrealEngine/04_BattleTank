// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "BattleTank.h"
#include "Class.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
// BeginPlay() должен оставаться public если будет необходимо насследовать этот класс
public:
	virtual void BeginPlay() override;
private:
	ATank * GetAIControlledTank() const;
	
	ATank * GetPlayerTank() const;
};
