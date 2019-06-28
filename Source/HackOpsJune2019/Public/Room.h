// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.generated.h"

class UGameCharacter;
struct FItem;

USTRUCT(BlueprintType)
struct FRoom
{
	GENERATED_USTRUCT_BODY()

	FRoom() {}
	FRoom(const FString& GivenName): Name(GivenName) {}
	FRoom(const FRoom& Other);

	bool ItemInRoom(const FString& ItemName);

	FString Name;
	FVector Location;
	TArray<TSharedPtr<FItem>> Items;
	int32 NumCharactersInside = 0;
	int32 NumAllowedInside = 10000; //Default no effective limit

	// Should include a self-reference, for staying in the same room
	TArray<TWeakPtr<FRoom>> AdjacentRooms;
};
