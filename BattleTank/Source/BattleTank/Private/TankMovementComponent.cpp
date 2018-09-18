// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
//#include "TankTrack.h"

/*
void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return;}
	LeftTrack = LeftTrackToSet;
	RightTrack = LeftTrackToSet;
}
*/
void UTankMovementComponent::IntendMove(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
}

/*
UTankMovementComponent::UTankMovementComponent()
{
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("UTankMovementComponent contrcuctor at %s"), *TankName);
}

// Called when the game starts
void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}
*/