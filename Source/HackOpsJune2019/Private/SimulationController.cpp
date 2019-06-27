#include "SimulationController.h"
#include "GameCharacter.h"
#include "Action.h"
#include "Room.h"
#include "CharacterBehaviours/CharacterBehaviour.h"
#include "Item.h"

TArray<FMapState> ASimulationController::SimulateFrom(const FMapState& InitState)
{
	TArray<FMapState> StateHistory;
	FMapState CurrState(InitState);

	int ElapsedMoves = 0;
	while (ElapsedMoves < MaxMoves)
	{
		StateHistory.Add(CurrState);

		// Get move actions
		for (auto& Character : CurrState.Characters)
		{
			if (!Character.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("ASimulationController::SimulateFrom: Character null, moves: %d"), ElapsedMoves);
			}

			if (!Character->Behaviour.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("ASimulationController::SimulateFrom: Behaviour null, moves: %d"), ElapsedMoves);
			}

			auto PrioritisedMoveActions = Character->Behaviour->GetPrioritisedMoveActions(CurrState, Character.Get());

			int i = 0;
			for (; i < PrioritisedMoveActions.Num(); ++i)
			{
				auto& DesiredRoom = PrioritisedMoveActions[i];
				//TODO: check in a better way (this depends on order)
				if (DesiredRoom->NumCharactersInside + 1 < DesiredRoom->NumAllowedInside)
				{
					Character->CurrRoom = DesiredRoom;
					DesiredRoom->NumCharactersInside++;
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

				switch (DesiredAction.Type)
				{
				case InteractionActionType::Kill:
					if (Character->CurrRoom == DesiredAction.CharacterToKill->CurrRoom)
					{
						DesiredAction.CharacterToKill->IsDead = true;
						CurrState.IsTerminal = true;
					}
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

		CurrState = FMapState(CurrState);
		ElapsedMoves++;
	}

	return StateHistory;
}

FMapState ASimulationController::DummyInitState()
{
	FMapState State;

	// Create items
	auto NewItem1 = MakeShared<FItem>(FString(TEXT("Item1")));
	auto NewItem2 = MakeShared<FItem>(FString(TEXT("Item2")));

	// Create rooms
	auto NewRoom1 = MakeShared<FRoom>(FString(TEXT("Room1")));
	NewRoom1->Items.Add(NewItem1);
	auto NewRoom2 = MakeShared<FRoom>(FString(TEXT("Room2")));
	NewRoom2->Items.Add(NewItem2);
	NewRoom1->AdjacentRooms.Add(NewRoom2);
	NewRoom2->AdjacentRooms.Add(NewRoom1);

	// Create characters
	auto NewChar1 = MakeShared<FGameCharacter>();
	NewChar1->CurrRoom = NewRoom1;
	auto NewChar2 = MakeShared<FGameCharacter>();
	NewChar2->CurrRoom = NewRoom2;

	State.Characters.Add(NewChar1);
	State.Characters.Add(NewChar2);
	State.Rooms.Emplace(NewRoom1->Name, NewRoom1);
	State.Rooms.Emplace(NewRoom2->Name, NewRoom2);

	return State;
}