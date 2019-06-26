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
UCLASS()
class HACKOPSJUNE2019_API UGameCharacter : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(TSharedRef<FMapState> State);
	TArray<FInteractionAction> GetPrioritisedInteractionActions(FMapState& State);
	TSharedPtr<FRoom> CurrRoom;
	bool IsDead = false;

private:
	FString Name;
};
