// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void  ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"))
	ATank	* PossesedTank = GetControlledTank();
	if (PossesedTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is possessed at the BeginPlay!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s is possessed!"), *PossesedTank->GetName());
		isTankPossessed = true;
	}
}


void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank	* PossesedTank = GetControlledTank();	
	if (PossesedTank == nullptr)
	{
		if (isTankPossessed)
		{
			UE_LOG(LogTemp, Error, TEXT("Tick: Tank is not possessed!"));
			isTankPossessed = false;
		}		
	}
	else if (!isTankPossessed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tick: Tank %s is possessed!"), *PossesedTank->GetName());
		isTankPossessed = true;
	}
}


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default 
}