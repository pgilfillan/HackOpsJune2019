// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "GameCharacter.generated.h"

struct FMapState;
struct FRoom;
class CharacterBehaviour;

USTRUCT(BlueprintType)
struct FGameCharacter
{
	GENERATED_USTRUCT_BODY()
	
public:
	FGameCharacter() {}
	virtual ~FGameCharacter();
	FGameCharacter(FString name, TSubclassOf<AActor> GameCharacterBP, TSharedPtr<FRoom> room, CharacterBehaviour* GivenBehaviour);
	FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom);

	void SpawnCharacterBlueprint(AActor* ActorToSpawnWith);

	TSharedPtr<FRoom> CurrRoom;
	TSharedPtr<FItem> HeldItem;
	bool IsDead = false;
	FString Name;
	TSubclassOf<class AActor> GameCharacterBP;
	CharacterBehaviour* Behaviour;
};