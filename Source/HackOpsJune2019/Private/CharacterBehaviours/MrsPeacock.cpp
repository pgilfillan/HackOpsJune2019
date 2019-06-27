#include "MrsPeacock.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> MrsPeacockBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

TArray<FInteractionAction> MrsPeacockBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Eat;
	Actions.Add(Action);
	return Actions;
}