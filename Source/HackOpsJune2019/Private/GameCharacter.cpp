// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> UGameCharacter::GetPrioritisedMoveActions(TSharedRef<FMapState> State)
{
	//TODO: give priority to particular rooms based on motivation
	return CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> UGameCharacter::GetPrioritisedInteractionActions(FMapState& State)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Eat;
	Actions.Add(Action);
	return Actions;
}