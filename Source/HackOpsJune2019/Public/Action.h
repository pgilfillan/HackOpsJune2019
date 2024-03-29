// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Action.generated.h"

enum class InteractionActionType
{
	Eat,
	Drink,
	Talk,
	Inspect,
	Use,
	Read,
	Kill,
	Nothing
};

struct FGameCharacter;

USTRUCT(BlueprintType)
struct FInteractionAction
{
	GENERATED_USTRUCT_BODY()

	InteractionActionType Type;

	//For specific action types, nullptr if not taking that action
	TSharedPtr<FItem> ItemActingOn;
	TSharedPtr<FGameCharacter> CharacterToKill;
	FString FlavourText;
};

