#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"

// Do a deep copy to keep separation between states
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