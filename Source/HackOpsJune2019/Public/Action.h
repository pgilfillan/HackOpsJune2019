// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.generated.h"

enum class MotivationActionType
{
	Move,
	Eat,
	Drink,
	Talk,
	Inspect,
	Use,
	Read
};

USTRUCT()
struct FMotivationAction
{
	GENERATED_BODY()

	MotivationActionType Type;

	//For specific action types

};

