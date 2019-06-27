#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"

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