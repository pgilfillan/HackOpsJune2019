#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> ProfPlumBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
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

TArray<FInteractionAction> ProfPlumBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
				if (OurRoom->NumCharactersInside == 2 && OurRoom->ItemInRoom("Revolver"))
				{
					Action.FlavourText = FString(TEXT("This is for my Father who you Murdered in Africa with this very gun!"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				break;
			case Character::DrBlack:
				break;
			case Character::MrsPeac:
				break;
			case Character::MrsWhite:
				Action.FlavourText = FString(TEXT("Miss white have you seen the candle stick?  This is the second to go missing this week"));
				break;
			case Character::MsScar:
				Action.FlavourText = FString(TEXT("Why Miss Scarlet you look ravishing this evening!"));
				break;
			case Character::ProfPlum:
				break;
			case Character::RevGreen:
				if (OurRoom->NumCharactersInside != 2 || !(OurRoom->ItemInRoom("Lead pipe") ||
					OurRoom->ItemInRoom("Spanner") || OurRoom->ItemInRoom("Candlestick")))
				{
					Action.FlavourText = FString(TEXT("Reverend I hear you've been preaching Fire and Brimstone, very old testament"));
				}
				break;
			default:
				break;
			}
		}
	}

	Actions.Add(Action);
	return Actions;
}