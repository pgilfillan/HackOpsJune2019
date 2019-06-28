// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

	FItem() {}
	FItem(const FString& GivenName, TSubclassOf<AActor> ItemBP ) : Name(GivenName), ItemBP(ItemBP) {}
	FString Name;

	void SpawnItemBlueprint(AActor* ActorToSpawnWith, FRoom* room);

	TSubclassOf<class AActor> ItemBP;
};
