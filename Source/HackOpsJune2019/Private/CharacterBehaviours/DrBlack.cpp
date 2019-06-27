#include "DrBlack.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> DrBlackBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> DrBlackBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
			case Character::DrBlack:
			case Character::MrsPeac:
			case Character::MrsWhite:
			case Character::MsScar:
			case Character::ProfPlum:
			case Character::RevGreen:
			default:
				break;
			}
		}
	}

	Actions.Add(Action);
	return Actions;
}