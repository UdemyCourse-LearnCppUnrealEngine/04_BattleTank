// Fill out your copyright notice in the Description page of Project Settings.



#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	/*auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.GetSafeNormal().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is moving with velosity %s"), *TankName, *MoveVelocityString);*/
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntention);
	float RightThrow = CrossProduct.Z;
	IntendTurnRight(RightThrow);

	UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), RightThrow, ForwardThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO Prevent double speed due double control use
}


