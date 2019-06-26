// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MapState.generated.h"

class UGameCharacter;

USTRUCT(BlueprintType)
struct FMapState
{
	GENERATED_USTRUCT_BODY()

	FMapState() {}
	TArray<TSharedPtr<UGameCharacter>> Characters;
};
