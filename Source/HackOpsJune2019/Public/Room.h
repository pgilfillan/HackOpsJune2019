// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Room.generated.h"

class UGameCharacter;

USTRUCT(BlueprintType)
struct FRoom
{
	GENERATED_USTRUCT_BODY()

	FRoom() {}
	FString Name;
	//TArray<TSharedPtr<FItem>> Items;
	TArray<UGameCharacter*> Characters;

	// Should include a self-reference, for staying in the same room
	TArray<TSharedPtr<FRoom>> AdjacentRooms;
};
