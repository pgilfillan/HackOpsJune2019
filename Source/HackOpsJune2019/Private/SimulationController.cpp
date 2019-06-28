#include "SimulationController.h"
#include "GameCharacter.h"
#include "Action.h"
#include "Room.h"
#include "CharacterBehaviours/CharacterBehaviour.h"
#include "Item.h"

TArray<FMapState> ASimulationController::SimulateFrom(FMapState& InitState)
{
	TArray<FMapState> StateHistory;
	FMapState CurrState(InitState);
	TSharedPtr<FMapState> CurrStatePtr = MakeShareable(&CurrState);
	InitState.NextState = CurrStatePtr;
	CurrState.ParentState = MakeShareable(&InitState);
	
	int ElapsedMoves = 0;
	while (ElapsedMoves < MaxMoves)
	{
		auto test = CurrState;
		StateHistory.Add(CurrState);

		// Get move actions
		for (auto& Character : CurrState.Characters)
		{
			auto PrioritisedMoveActions = Character->Behaviour->GetPrioritisedMoveActions(CurrState, Character.Get());

			int i = 0;
			for (; i < PrioritisedMoveActions.Num(); ++i)
			{
				auto& DesiredRoom = PrioritisedMoveActions[i];
				//TODO: check in a better way (this depends on order)
				if (DesiredRoom->NumCharactersInside + 1 < DesiredRoom->NumAllowedInside)
				{
					Character->CurrRoom->NumCharactersInside--;
					DesiredRoom->NumCharactersInside++;
					Character->CurrRoom = DesiredRoom;
				}
			}

			// If no suitable move found (because of conflicts)
			if (i == PrioritisedMoveActions.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("No move was able to be taken, defaulting to do nothing"));
			}
		}

		// Get interaction actions
		for (auto& Character : CurrState.Characters)
		{
			auto PlayerPrioritisedActions = Character->Behaviour->GetPrioritisedInteractionActions(CurrState, Character.Get());

			int i = 0;
			for (; i < PlayerPrioritisedActions.Num(); ++i)
			{
				auto& DesiredAction = PlayerPrioritisedActions[i];
				Character->FlavourText = DesiredAction.FlavourText;

				switch (DesiredAction.Type)
				{
				case InteractionActionType::Kill:
					if (Character->CurrRoom == DesiredAction.CharacterToKill->CurrRoom)
					{
						DesiredAction.CharacterToKill->IsDead = true;
						CurrState.IsTerminal = true;
					}
					break;
				default:
					break;
				}

				// TODO: check for conflicts
				break;
			}

			// If no suitable move found (because of conflicts)
			if (i == PlayerPrioritisedActions.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("No move was able to be taken, defaulting to do nothing"));
			}
		}

		if (CurrState.IsTerminal)
		{
			break;
		}

		auto& PrevStatePtr = CurrStatePtr;
		CurrState = FMapState(CurrState);
		CurrStatePtr = MakeShareable(&CurrState);
		PrevStatePtr->NextState = CurrStatePtr;
		CurrState.ParentState = PrevStatePtr;

		ElapsedMoves++;
	}

	return StateHistory;
}

void ASimulationController::ResetSimulationState(
	int Seed,
	TArray<FString> CharacterNames,
	TArray<TSubclassOf<AActor>> CharacterBPs,
	TArray<FString> RoomNames,
	TArray<FVector> RoomLocations,
	TArray<FString> ItemNames
)
{
	RootMapState->GenerateMapState(Seed, CharacterNames, CharacterBPs, RoomNames, RoomLocations, ItemNames);
	RootMapState->SpawnAllCharacterBlueprint(this);
}