// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

TSharedPtr<TArray<FMotivationAction>> UGameCharacter::GetPrioritisedMotivationActions(FMapState* State)
{
	auto Actions = MakeShared<TArray<FMotivationAction>>();
	FMotivationAction Action;
	Action.Type = MotivationActionType::Eat;
	Actions->Add(Action);
	return Actions;
}