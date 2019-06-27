// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "Item.h"
#include "GameCharacter.generated.h"

struct FMapState;
struct FRoom;

// Should probably be a struct like the other classes but oh well
USTRUCT(BlueprintType)
struct FGameCharacter
{
	GENERATED_USTRUCT_BODY()
	
public:
	FGameCharacter() {}
	FGameCharacter(FString name, TSharedPtr<FRoom> room);

	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State);
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State);
	TSharedPtr<FRoom> CurrRoom;
	bool IsDead = false;
	FString Name;
};
