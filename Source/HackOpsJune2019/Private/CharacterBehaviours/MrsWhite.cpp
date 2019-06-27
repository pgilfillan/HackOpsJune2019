#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> MrsWhiteBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> MrsWhiteBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
				Action.FlavourText = FString(TEXT("You must have done some desperate things in the War"));
				break;
			case Character::DrBlack:
				break;
			case Character::MrsPeac:
				break;
			case Character::MrsWhite:
				break;
			case Character::MsScar:
				if (OurRoom->NumCharactersInside == 2 && WeaponPresent(OurRoom))
				{
					Action.FlavourText = FString(TEXT("How dare you seduce the good Dr, you are gold digging trash"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				break;
			case Character::ProfPlum:
				break;
			case Character::RevGreen:
				if (OurRoom->NumCharactersInside == 2 && OurRoom->ItemInRoom("Candlestick"))
				{
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				else
				{
					Action.FlavourText = FString(TEXT("What is your sermon about this Sunday Reverend?"));
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