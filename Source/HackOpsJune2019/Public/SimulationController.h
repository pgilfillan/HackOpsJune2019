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
	void SimulateFrom(FMapState& InitState);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	FMapState& ResetSimulationState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations, TArray<FString> ItemNames, TArray<TSubclassOf<AActor>> ItemBPs);

	UFUNCTION(BlueprintCallable)
	FMapState& JumpSteps(UPARAM(ref) FMapState& Current, int32 NumSteps);

	UFUNCTION(BlueprintCallable)
	void ChangeDoorOpen(UPARAM(ref) FMapState& Current, FString RoomName1, FString RoomName2, bool IsOpen);

	UFUNCTION(BlueprintCallable)
	FString GetRoomNameForCharacter(UPARAM(ref) FMapState& State, FString CharacterName);

private:
	const int MaxMoves = 20; //to change

	TSharedPtr<FMapState> RootMapState = MakeShared<FMapState>();
};
