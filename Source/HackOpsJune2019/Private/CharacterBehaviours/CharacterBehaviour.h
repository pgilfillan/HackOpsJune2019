#include "Room.h"
#include "MapState.h"
#include "Action.h"
#include "GameCharacter.h"

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

// TODO: better place for this, not good to be global

class CharacterBehaviour
{
public:
	// Should be called somewhere before use, not the best design
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

	TMap<FString, Character> CharacterNamesMap;

	bool CharacterPresent(const FString& Character, const FString& RoomName, const FMapState& State)
	{
		for (auto& OtherCharacter : State.Characters)
		{
			if (Character == OtherCharacter->Name && RoomName == OtherCharacter->CurrRoom->Name)
			{
				return true;
			}
		}

		return false;
	}

	bool WeaponPresent(const TSharedPtr<FRoom> Room)
	{
		return Room->ItemInRoom("Dagger") || Room->ItemInRoom("Candlestick") ||
			Room->ItemInRoom("Revolver") || Room->ItemInRoom("Rope") ||
			Room->ItemInRoom("Lead Pipe") || Room->ItemInRoom("Spanner");
	}
};

class RevGreenBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class ProfPlumBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class MrsWhiteBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class MrsPeacockBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class MissScarletBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class DrBlackBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};

class ColMustardBehaviour : public CharacterBehaviour
{
	TArray<TSharedPtr<FRoom>> GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character) override;
	TArray<FInteractionAction> GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character) override;
};