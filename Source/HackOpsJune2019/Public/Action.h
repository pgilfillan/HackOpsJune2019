// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
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

USTRUCT()
struct FInteractionAction
{
	GENERATED_BODY()

	InteractionActionType Type;

	//For specific action types, null if not taking that action
	TSharedPtr<FRoom> MovingTo;
	//TSharedPtr<FItem> ItemActingOn;
};

