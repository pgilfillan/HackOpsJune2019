// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "GameCharacter.h"

FGameCharacter::FGameCharacter(FString name, TSharedPtr<FRoom> room) :
	CurrRoom(room),
	Name(name)
{
	// Spawn Blueprint actor here.
}


TArray<TSharedPtr<FRoom>> FGameCharacter::GetPrioritisedMoveActions(const FMapState& State)
{
	//TODO: give priority to particular rooms based on motivation
	return CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> FGameCharacter::GetPrioritisedInteractionActions(const FMapState& State)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Eat;
	Actions.Add(Action);
	return Actions;
}