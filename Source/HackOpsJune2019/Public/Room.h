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
	FRoom(const FString& GivenName): Name(GivenName) {}
	FRoom(const FRoom& Other);
	FString Name;
	FVector Location;

	TArray<UGameCharacter*> Characters;

	TArray<TSharedPtr<FItem>> Items;
	int32 NumCharactersInside = 0;
	int32 NumAllowedInside = 10000; //Default no effective limit

	// Should include a self-reference, for staying in the same room
	TArray<TSharedPtr<FRoom>> AdjacentRooms;
};
