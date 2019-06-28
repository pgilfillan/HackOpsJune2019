#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> MrsPeacockBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<TSharedPtr<FRoom>> Rooms;
	for (auto& RoomWkPtr : Character->CurrRoom->AdjacentRooms)
	{
		if (RoomWkPtr.IsValid())
		{
			Rooms.Add(RoomWkPtr.Pin());
		}
	}
	return Rooms;
}

TArray<FInteractionAction> MrsPeacockBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Nothing;

	auto& OurRoom = Character->CurrRoom;
	for (auto& OtherCharacter : State.Characters)
	{
		// If not ourself and if in the same room
		if (OurRoom->Name == OtherCharacter->CurrRoom->Name)
		{
			switch (CharacterNamesMap[OtherCharacter->Name])
			{
			case Character::ColMust:
				break;
			case Character::DrBlack:
				break;
			case Character::MrsPeac:
				break;
			case Character::MrsWhite:
				Action.FlavourText = FString(TEXT("Mrs White I admire how long you've worked here and never once have you asked for a raise."));
				break;
			case Character::MsScar:
				Action.FlavourText = FString(TEXT("Mr Black told me your little secret, I knew you were a Harlot"));
				break;
			case Character::ProfPlum:
				Action.FlavourText = FString(TEXT("Professor wasn't your Father in the same battalion as Col Mustard?"));
				break;
			case Character::RevGreen:
				break;
			default:
				break;
			}
		}
	}

	Actions.Add(Action);
	return Actions;
}