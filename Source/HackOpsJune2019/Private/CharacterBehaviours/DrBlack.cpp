#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> DrBlackBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
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

TArray<FInteractionAction> DrBlackBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
				if (!WeaponPresent(OurRoom)
					|| !CharacterPresent(FString(TEXT("Miss Scarlet")), OurRoom->Name, State))
				{
					Action.FlavourText = FString(TEXT("Colonel, how goes that leg of yours?  Did they ever get the shrapnel out?"));
				}
				break;
			case Character::DrBlack:
				break;
			case Character::MrsPeac:
				Action.FlavourText = FString(TEXT("I have been entertaining Miss Scarlet every Sunday, we visit the opera together then... retire"));
				break;
			case Character::MrsWhite:
				if (OurRoom->NumCharactersInside == 2 && OurRoom->ItemInRoom("Candlestick"))
				{
					Action.FlavourText = FString(TEXT("The silver candle stick?  You've been Stealing from me?  No one makes a fool of Dr Black!"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				else
				{
					Action.FlavourText = FString(TEXT("Lock all the doors tight Mrs White, I don't want another burglar to get away with the other candlestick"));
				}
				break;
			case Character::MsScar:
				if (OurRoom->NumCharactersInside != 2 || !WeaponPresent(OurRoom))
				{
					Action.FlavourText = FString(TEXT("Miss Scarlet is one of the finest young ladies I have the pleasure of Knowing"));
				}
				break;
			case Character::ProfPlum:
				Action.FlavourText = FString(TEXT("I know I said stay as long as you like Professor but it is coming onto a month now."));
				break;
			case Character::RevGreen:
				Action.FlavourText = FString(TEXT("Father I have been unfaithful to my wife, with a woman in this very house tonight"));
				break;
			default:
				break;
			}
		}
	}

	Actions.Add(Action);
	return Actions;
}