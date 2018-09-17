// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void IntendMove(float Throw);

	//// Sets default values for this component's properties
	//UTankMovementComponent();
	
	
};
