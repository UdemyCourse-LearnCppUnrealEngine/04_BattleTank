// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank.h"
#include "Class.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank; 

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
// BeginPlay() должен оставаться public если будет необходимо насследовать этот класс
public:
	

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	float AcceptanceRadius = 3000.f;
};
