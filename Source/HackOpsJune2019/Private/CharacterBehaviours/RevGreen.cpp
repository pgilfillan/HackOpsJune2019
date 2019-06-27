#include "RevGreen.h"
#include "GameCharacter.h"

TArray<TSharedPtr<FRoom>> RevGreenBehaviour::GetPrioritisedMoveActions(const FMapState& State, FGameCharacter* Character)
{
	return Character->CurrRoom->AdjacentRooms;
}

// Not worrying about conflicts for now, only selecting one move
TArray<FInteractionAction> RevGreenBehaviour::GetPrioritisedInteractionActions(const FMapState& State, FGameCharacter* Character)
{
	TArray<FInteractionAction> Actions;
	FInteractionAction Action;
	Action.Type = InteractionActionType::Nothing;

	for (auto& OtherCharacter : State.Characters)
	{
		auto& OurRoom = Character->CurrRoom;
		// If in the same room
		if (OurRoom->Name == Character->CurrRoom->Name)
		{
			switch (CharacterNamesMap[OtherCharacter->Name])
			{
			case Character::ColMust:
				Action.FlavourText = FString(TEXT("You look troubled Col Mustard, still dwelling on africa?"));
			case Character::DrBlack:
				break;
			case Character::MrsPeac:
				if (Character->CurrRoom->NumCharactersInside == 2 && (OurRoom->ItemInRoom("Dagger") ||
					OurRoom->ItemInRoom("Revolver") || OurRoom->ItemInRoom("Rope")))
				{
					Action.FlavourText = FString(TEXT("Confession is only for the holy Miss Peacock.  God punishes those who break that trust"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
				else
				{
					Action.FlavourText = FString(TEXT("One should be careful of what one says about others Mrs Peacock"));
				}
			case Character::MrsWhite:
				if (Character->CurrRoom->NumCharactersInside == 2 && OurRoom->ItemInRoom("Candlestick"))
				{
					Action.FlavourText = FString(TEXT("Miss white I think you dropped this. Wait a moment isn't this the missing candlesti..."));
				}
			case Character::MsScar:
				break;
			case Character::ProfPlum:
				if (Character->CurrRoom->NumCharactersInside == 2 && (OurRoom->ItemInRoom("Lead pipe") ||
					OurRoom->ItemInRoom("Spanner") || OurRoom->ItemInRoom("Candlestick")))
				{
					Action.FlavourText = FString(TEXT("I can't in good conscience let you leave with what you just told me.  God punishes the wicked Professor"));
					Action.Type = InteractionActionType::Kill;
					Action.CharacterToKill = OtherCharacter;
				}
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