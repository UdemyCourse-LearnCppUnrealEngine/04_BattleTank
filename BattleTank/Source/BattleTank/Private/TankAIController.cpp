// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//#include "Kismet/GameplayStatics.h"


ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());		
}

void  ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"))
	ATank	* PossesedTank = GetAIControlledTank();
	ATank * PlayerTank = GetPlayerTank();
	if (PossesedTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is possessed at the BeginPlay!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s is controlled by AI!"), *PossesedTank->GetName());
	}
	if (PlayerTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank is found by %s"), *PossesedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has found a player Tank %s"), *PossesedTank->GetName(), *PlayerTank->GetName());
	}
}