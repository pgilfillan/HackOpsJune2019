#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"
#include "RandomStream.h"

FMapState::FMapState(const FMapState& Other)
{
	// Copy rooms
	for (const auto& OtherRoomPair : Other.Rooms)
	{
		auto RoomCopy = MakeShared<FRoom>(OtherRoomPair.Value.ToSharedRef().Get());
		this->Rooms.Emplace(RoomCopy->Name, RoomCopy);
	}

	// Add adjaceny list
	for (const auto& OtherRoomPair : Other.Rooms)
	{
		for (const auto& Room : OtherRoomPair.Value->AdjacentRooms)
		{
			Rooms[OtherRoomPair.Key]->AdjacentRooms.Add(Rooms[Room->Name]);
		}
	}

	// Copy characters
	for (const auto& OtherCharacter : Other.Characters)
	{
		auto& OtherCurrRoomName = OtherCharacter->CurrRoom->Name;
		auto& CurrRoom = Rooms[OtherCurrRoomName];

		auto CharacterCopy = MakeShared<FGameCharacter>(OtherCharacter.ToSharedRef().Get(), CurrRoom);
		this->Characters.Emplace(CharacterCopy);
	}
}

void FMapState::GenerateMapState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations)
{
	for (int i = 0; i < RoomNames.Num(); ++i)
	{
		FRoom NewRoom{};
		NewRoom.Name = RoomNames[i];
		NewRoom.Location = RoomLocations[i];
		Rooms.Emplace(NewRoom.Name, MakeShared<FRoom>(NewRoom));
	}

	for (int i = 0; i < CharacterNames.Num(); ++i)
	{
		auto SRand = FRandomStream(Seed);
		auto SelectedRoomIndex = SRand.RandRange(0, Rooms.Num());
		int CurrIndex = 0;
		for (auto& RoomPair : Rooms)
		{
			if (CurrIndex == SelectedRoomIndex)
			{
				auto NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value);
				Characters.Add(MakeShared<FGameCharacter>(NewCharacter));
			}
		}
	}
}

void FMapState::SpawnAllCharacterBlueprint(AActor* ActorToSpawnWith)
{
	for (int i = 0; i < Characters.Num(); ++i)
	{
		Characters[i]->SpawnCharacterBlueprint(ActorToSpawnWith);
	}
}