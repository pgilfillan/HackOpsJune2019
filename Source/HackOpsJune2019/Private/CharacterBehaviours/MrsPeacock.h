#include "CharacterBehaviour.h"

class MrsPeacockBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};