// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameCharacter.h"
#include "Room.generated.h"

USTRUCT()
struct FRoom
{
	GENERATED_BODY()

	FRoom() {}
	FString Name;
	//TArray<TSharedPtr<FItem>> Items;
	TArray<TSharedPtr<UGameCharacter>> Characters;

	// Should include a self-reference, for staying in the same room
	TArray<TSharedPtr<FRoom>> AdjacentRooms;
};
