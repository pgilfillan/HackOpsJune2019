#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> MissScarletBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> MissScarletBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
				if (OurRoom->NumCharactersInside == 2 && WeaponPresent(OurRoom))
				{
					Action.FlavourText = FString(TEXT("You've been lying about me! You've ruined my marriage. I would never be with you"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				break;
			case Character::MrsPeac:
				break;
			case Character::MrsWhite:
				if (OurRoom->NumCharactersInside != 2 || !WeaponPresent(OurRoom))
				{
					Action.FlavourText = FString(TEXT("Why are you lurking around here Miss White?"));
				}
				break;
			case Character::MsScar:
				break;
			case Character::ProfPlum:
				break;
			case Character::RevGreen:
				Action.FlavourText = FString(TEXT("The lord forgives anything with enough faith do they not father?"));
				break;
			default:
				break;
			}
		}
	}

	Actions.Add(Action);
	return Actions;
}