// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "MapState.h"
#include "CoreMinimal.h"

UCLASS()
class UGameCharacter : public UObject
{
	GENERATED_BODY()

public:
	TSharedPtr<TArray<FMotivationAction>> GetPrioritisedMotivationActions(FMapState* State);

private:
	FString Name;
};
