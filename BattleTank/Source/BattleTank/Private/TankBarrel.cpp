// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move the barrel to the given amount for the single frame
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = Speed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto CorrectedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(CorrectedElevation, 0, 0));

}


