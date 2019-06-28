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
	TArray<FMapState> SimulateFrom(FMapState& InitState);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	void ResetSimulationState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations, TArray<FString> ItemNames);

	UFUNCTION(BlueprintCallable)
	FMapState& JumpSteps(UPARAM(ref) FMapState& Current, int32 NumSteps);

private:
	const int MaxMoves = 20; //to change

	TSharedPtr<FMapState> RootMapState = MakeShared<FMapState>();
};
