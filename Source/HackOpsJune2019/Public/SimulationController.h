// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapState.h"
#include "SimulationController.generated.h"

UCLASS()
class HACKOPSJUNE2019_API ASimulationController : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static TArray<FMapState> SimulateFrom(const FMapState& InitState);

	UFUNCTION(BlueprintCallable)
	static FMapState GetInitState();

private:
	const int MaxMoves = 20; //to change
};
