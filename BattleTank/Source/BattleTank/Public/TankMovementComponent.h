// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declarations
class UTankTrack;
/**
 * Responsible for driving tanks tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMove(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	//// Sets default values for this component's properties
	//UTankMovementComponent();

private:	
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
