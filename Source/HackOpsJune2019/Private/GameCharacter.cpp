#include "GameCharacter.h"
#include "Room.h"
#include "CharacterBehaviours/CharacterBehaviour.h"
#include "Engine/World.h"

FGameCharacter::FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom)
{
	this->HeldItem = Other.HeldItem;
	this->IsDead = Other.IsDead;
	this->Name = Other.Name;
	this->CurrRoom = CurrRoom;
}

FGameCharacter::FGameCharacter(FString Name, TSubclassOf<AActor> GameCharacterBP, TSharedPtr<FRoom> Room, CharacterBehaviour* GivenBehaviour) :
	CurrRoom(Room),
	Name(Name),
	GameCharacterBP(GameCharacterBP),
	Behaviour(GivenBehaviour)
{
}

FGameCharacter::~FGameCharacter()
{
	delete Behaviour;
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