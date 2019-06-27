// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Room.h"
#include "MapState.generated.h"

struct FGameCharacter;
struct FRoom;

USTRUCT(BlueprintType)
struct FMapState
{
	GENERATED_USTRUCT_BODY()

	FMapState() {}
	FMapState(const FMapState& other);
	FMapState(int Seed, TArray<FString>CharacterNames, TArray<TSharedPtr<FRoom>> Rooms);

	TArray<TSharedPtr<FGameCharacter>> Characters;
	TArray<TSharedPtr<FRoom>> Rooms;
};
