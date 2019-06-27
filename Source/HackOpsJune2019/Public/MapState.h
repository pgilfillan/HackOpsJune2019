// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Room.h"

#include "GameFramework/Actor.h"

#include "MapState.generated.h"

struct FGameCharacter;
struct FRoom;

USTRUCT(BlueprintType)
struct FMapState
{
	GENERATED_USTRUCT_BODY()

	FMapState() {}
	FMapState(const FMapState& other);

	void GenerateMapState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations);
	void SpawnAllCharacterBlueprint(AActor* ActorToSpawnWith);

	TArray<TSharedPtr<FGameCharacter>> Characters;
	TArray<TSharedPtr<FRoom>> Rooms;
};
