#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"

#include "RandomStream.h"

// Do a deep copy to keep separation between simulation runs
FMapState::FMapState(const FMapState& other)
{
	for (const auto& OtherCharacter : other.Characters)
	{
		//auto CharacterCopy = MakeShared<UGameCharacter>(OtherCharacter);
		//this->Characters.Emplace(CharacterCopy);
	}

	for (const auto& OtherRoom : other.Rooms)
	{
		//this->Rooms.Emplace(MakeShared<FRoom>(OtherRoom));
	}
}

void FMapState::GenerateMapState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations)
{
	for (int i = 0; i < RoomNames.Num(); ++i)
	{
		FRoom NewRoom{};
		NewRoom.Name = RoomNames[i];
		NewRoom.Location = RoomLocations[i];
		Rooms.Add(MakeShared<FRoom>(NewRoom));
	}

	for (int i = 0; i < CharacterNames.Num(); ++i)
	{
		auto SRand = FRandomStream(Seed);
		auto SelectedRoomIndex = SRand.RandRange(0, Rooms.Num());
		auto NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], Rooms[SelectedRoomIndex]);
		Characters.Add(MakeShared<FGameCharacter>(NewCharacter));
	}
}

void FMapState::SpawnAllCharacterBlueprint(AActor* ActorToSpawnWith)
{
	for (int i = 0; i < Characters.Num(); ++i)
	{
		Characters[i]->SpawnCharacterBlueprint(ActorToSpawnWith);
	}
}