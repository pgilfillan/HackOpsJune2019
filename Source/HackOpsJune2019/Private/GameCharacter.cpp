#include "GameCharacter.h"
#include "Room.h"
#include "Engine/World.h"

FGameCharacter::FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom)
{
	this->HeldItem = Other.HeldItem;
	this->IsDead = Other.IsDead;
	this->Name = Other.Name;
	this->CurrRoom = CurrRoom;
}

FGameCharacter::FGameCharacter(FString Name, TSubclassOf<AActor> GameCharacterBP, TSharedPtr<FRoom> Room) :
	CurrRoom(Room),
	Name(Name),
	GameCharacterBP(GameCharacterBP)
{
}

void FGameCharacter::SpawnCharacterBlueprint(AActor* ActorToSpawnWith)
{
	UWorld* world = ActorToSpawnWith->GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParameters{};
		SpawnParameters.Owner = ActorToSpawnWith;
		SpawnParameters.Name = FName(*Name);
		const FVector SpawnLocation = CurrRoom->Location;
		const FRotator SpawnRotation{};
		world->SpawnActor(GameCharacterBP, &SpawnLocation, &SpawnRotation, SpawnParameters);
	}
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