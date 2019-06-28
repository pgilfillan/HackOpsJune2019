#include "CharacterBehaviour.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> ColMustardBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<TSharedPtr<FRoom>> Rooms;
	auto RoomSharedPtr = Character->CurrRoom->AdjacentRooms[1].Pin();
	Rooms.Add(RoomSharedPtr);
	return Rooms;
}

TArray<FInteractionAction> ColMustardBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
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
				if (WeaponPresent(OurRoom)
					&& CharacterPresent(FString(TEXT("Miss Scarlet")), OurRoom->Name, State))
				{
					Action.FlavourText = FString(TEXT("How dare you rake this fine Girl across the coals.  Sir it is unforgivable!"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				break;
			case Character::MrsPeac:
				Action.FlavourText = FString(TEXT("Its hard to find a woman of such a vintage of yours madame"));
				break;
			case Character::MrsWhite:
				break;
			case Character::MsScar:
				Action.FlavourText = FString(TEXT("You remind me of my daughter Miss Scarlet, Blood red lips and a razor sharp tongue"));
				break;
			case Character::ProfPlum:
				if (OurRoom->NumCharactersInside != 2 || !OurRoom->ItemInRoom("Revolver"))
				{
					Action.FlavourText = FString(TEXT("You have your Fathers eyes Professor"));
				}
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