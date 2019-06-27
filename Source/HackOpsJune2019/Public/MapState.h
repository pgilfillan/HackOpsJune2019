// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MapState.generated.h"

struct FGameCharacter;
struct FRoom;

USTRUCT(BlueprintType)
struct FMapState
{
	GENERATED_USTRUCT_BODY()

	FMapState() {}
	FMapState(const FMapState& other);

	TArray<TSharedPtr<FGameCharacter>> Characters;
	TArray<TSharedPtr<FRoom>> Rooms;
};
