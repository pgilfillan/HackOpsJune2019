#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"

// Do a deep copy to keep separation between simulation runs
FMapState::FMapState(const FMapState& Other)
{
	for (const auto& OtherRoom : Other.Rooms)
	{
		auto RoomCopy = MakeShared<FRoom>(OtherRoom.ToSharedRef().Get());
		this->Rooms.Emplace(RoomCopy);
	}

	for (const auto& OtherCharacter : Other.Characters)
	{
		TSharedPtr<FRoom> CurrRoom;
		auto& OtherCurrRoomName = OtherCharacter->CurrRoom->Name;
		for (auto& Room : Rooms)
		{
			if (Room->Name == OtherCurrRoomName)
			{
				CurrRoom = Room;
			}
		}

		auto CharacterCopy = MakeShared<FGameCharacter>(OtherCharacter.ToSharedRef().Get(), CurrRoom);
		this->Characters.Emplace(CharacterCopy);
	}
}