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

FMapState::FMapState(int Seed, TArray<FString>CharacterNames, TArray<TSharedPtr<FRoom>> Rooms) :
	Rooms(Rooms)
{
	auto SRand = FRandomStream(Seed);

	for (int i = 0; i < CharacterNames.Num(); ++i)
	{
		auto SelectedRoomIndex = SRand.RandRange(0, Rooms.Num());
		auto NewCharacter = FGameCharacter(CharacterNames[i], Rooms[SelectedRoomIndex]);
		Characters.Add(MakeShared<FGameCharacter>(NewCharacter));
	}
}