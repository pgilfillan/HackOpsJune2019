// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "GameCharacter.generated.h"

struct FMapState;
struct FRoom;

USTRUCT(BlueprintType)
struct FGameCharacter
{
	GENERATED_USTRUCT_BODY()
	
public:
	FGameCharacter() {}
	FGameCharacter(FString name, TSubclassOf<AActor> GameCharacterBP, TSharedPtr<FRoom> room);
	FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom);

	void SpawnCharacterBlueprint(AActor* ActorToSpawnWith, int verticalOffset);

	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State);
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State);

	TSharedPtr<FRoom> CurrRoom;
	TSharedPtr<FItem> HeldItem;
	bool IsDead = false;
	FString Name;

	TSubclassOf<class AActor> GameCharacterBP;
};