#include "Room.h"
#include "MapState.h"
#include "Action.h"

enum class Character
{
	ColMust,
	MsScar,
	ProfPlum,
	RevGreen,
	MrsWhite,
	MrsPeac,
	DrBlack
};

class CharacterBehaviour
{
public:
	CharacterBehaviour()
	{
		CharacterNamesMap.Emplace(FString(TEXT("Colonel Mustard")), Character::ColMust);
		CharacterNamesMap.Emplace(FString(TEXT("Miss Scarlet")), Character::MsScar);
		CharacterNamesMap.Emplace(FString(TEXT("Professor Plum")), Character::ProfPlum);
		CharacterNamesMap.Emplace(FString(TEXT("Reverend Green")), Character::RevGreen);
		CharacterNamesMap.Emplace(FString(TEXT("Mrs White")), Character::MrsWhite);
		CharacterNamesMap.Emplace(FString(TEXT("Mrs Peacock")), Character::MrsPeac);
		CharacterNamesMap.Emplace(FString(TEXT("Dr Black")), Character::DrBlack);
	}

    virtual ~CharacterBehaviour() {}
	virtual TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) = 0;
	virtual TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) = 0;

	// Should be static/somewhere else but don't want to waste time
	TMap<FString, Character> CharacterNamesMap;
};