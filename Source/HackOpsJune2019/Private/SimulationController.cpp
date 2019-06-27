#include "SimulationController.h"
#include "GameCharacter.h"
#include "Action.h"
#include "Room.h"

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
			auto PrioritisedMoveActions = Character->GetPrioritisedMoveActions(CurrState);

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
			auto PlayerPrioritisedActions = Character->GetPrioritisedInteractionActions(CurrState);

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