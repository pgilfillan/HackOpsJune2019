// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> UGameCharacter::GetPrioritisedMoveActions(TSharedRef<FMapState> State)
{
	return CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> UGameCharacter::GetPrioritisedInteractionActions(TSharedRef<FMapState> State)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Eat;
	Actions.Add(Action);
	return Actions;
}