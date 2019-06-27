#include "GameCharacter.h"
#include "Room.h"
#include "CharacterBehaviours/CharacterBehaviour.h"
#include "Engine/World.h"

FGameCharacter::FGameCharacter(const FGameCharacter& Other, TSharedPtr<FRoom> CurrRoom)
{
	this->HeldItem = Other.HeldItem;
	this->IsDead = Other.IsDead;
	this->Name = Other.Name;
	this->Behaviour = Other.Behaviour;
	this->CurrRoom = CurrRoom;
}

FGameCharacter::FGameCharacter(FString Name, TSubclassOf<AActor> GameCharacterBP, TSharedPtr<FRoom> Room, TSharedPtr<CharacterBehaviour> GivenBehaviour) :
	CurrRoom(Room),
	Name(Name),
	GameCharacterBP(GameCharacterBP),
	Behaviour(GivenBehaviour)
{
}

void FGameCharacter::SpawnCharacterBlueprint(AActor* ActorToSpawnWith, int verticalOffset)
{
	UWorld* world = ActorToSpawnWith->GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParameters{};
		SpawnParameters.Owner = ActorToSpawnWith;
		SpawnParameters.Name = FName(*Name);

		// Vertical offset stops characters from looking strange when moving through each other
		const FVector SpawnLocation = FVector{ CurrRoom->Location.X, CurrRoom->Location.Y, CurrRoom->Location.Z + verticalOffset };
		const FRotator SpawnRotation{};
		world->SpawnActor(GameCharacterBP, &SpawnLocation, &SpawnRotation, SpawnParameters);
	}
}