// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "MapState.h"
#include "Room.h"
#include "CoreMinimal.h"
#include "GameCharacter.generated.h"

UCLASS()
class UGameCharacter : public UObject
{
	GENERATED_BODY()

public:
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(TSharedRef<FMapState> State);
	TArray<FInteractionAction> GetPrioritisedInteractionActions(TSharedRef<FMapState> State);

private:
	FString Name;
	TSharedPtr<FRoom> CurrRoom;
	TSharedPtr<FItem> CurrHeldItem;
};
