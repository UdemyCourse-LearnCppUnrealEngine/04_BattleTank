// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	
	//move the barrel to the given amount for the single frame
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = Speed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}

