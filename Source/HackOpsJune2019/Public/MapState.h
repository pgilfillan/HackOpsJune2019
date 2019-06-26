// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GameCharacter.h"
#include "MapState.generated.h"

USTRUCT(BlueprintType)
struct FMapState
{
	GENERATED_BODY()

public:
	TArray<TSharedPtr<UGameCharacter>> Characters;
};
