#include "Room.h"
#include "MapState.h"
#include "Action.h"

class CharacterBehaviour
{
public:
    virtual ~CharacterBehaviour() {}
	virtual TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) = 0;
	virtual TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) = 0;
};