#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"

// Do a deep copy to keep separation between simulation runs
FMapState::FMapState(const FMapState& other)
{
	for (const auto& OtherCharacter : other.Characters)
	{
		auto CharacterCopy = MakeShared<FGameCharacter>(OtherCharacter.ToSharedRef().Get());
		this->Characters.Emplace(CharacterCopy);
	}

	for (const auto& OtherRoom : other.Rooms)
	{
		auto RoomCopy = MakeShared<FRoom>(OtherRoom.ToSharedRef().Get());
		this->Characters.Emplace(RoomCopy);
	}
}