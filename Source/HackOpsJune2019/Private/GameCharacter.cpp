// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "GameCharacter.h"

FGameCharacter::FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom)
{
	this->HeldItem = Other.HeldItem;
	this->IsDead = Other.IsDead;
	this->Name = Other.Name;
	this->CurrRoom = CurrRoom;
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