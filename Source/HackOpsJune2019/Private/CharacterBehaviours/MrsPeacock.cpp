#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> MrsPeacockBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> MrsPeacockBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Nothing;

	for (auto& OtherCharacter : State.Characters)
	{
		// If not ourself and if in the same room
		if (Character->CurrRoom->Name == Character->CurrRoom->Name)
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
				break;
			case Character::MsScar:
				break;
			case Character::ProfPlum:
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