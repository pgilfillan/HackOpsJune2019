// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Room.h"
#include "MapState.h"
#include "Action.h"
#include "Item.h"
#include "GameCharacter.generated.h"


UCLASS()
class HACKOPSJUNE2019_API UGameCharacter : public UObject
{
	GENERATED_BODY()
	
public:
	//TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(TSharedRef<FMapState> State);
	TArray<FInteractionAction> GetPrioritisedInteractionActions(TSharedRef<FMapState> State);

private:
	FString Name;
	TSharedPtr<FRoom> CurrRoom;
};
