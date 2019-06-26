#include "SimulationController.h"

bool ASimulationController::SimulateFrom(const FMapState& InitState)
{
	auto CurrState = MakeShared<FMapState>(InitState);
	bool TerminalState = false;
	
	int ElapsedMoves = 0;
	while (!TerminalState && ElapsedMoves < MaxMoves)
	{
		// Get move actions
		for (auto& Player : CurrState->Characters)
		{
			/*
			auto& PrioritisedMoveActions = Player->GetPrioritisedMoveActions(CurrState);

			int i = 0;
			for (; i < PrioritisedMoveActions.Num; ++i)
			{
				// TODO: Update room

				// TODO: check for conflicts
				break;
			}

			// If no suitable move found (because of conflicts)
			if (i == PrioritisedMoveActions.Num)
			{
				UE_LOG(LogTemp, Warning, TEXT("No move was able to be taken, defaulting to do nothing"));
			}*/
		}

		// Get interaction actions
		for (auto& Player : CurrState->Characters)
		{
			auto& PlayerPrioritisedActions = Player->GetPrioritisedInteractionActions(CurrState.Get());

			int i = 0;
			for (; i < PlayerPrioritisedActions.Num; ++i)
			{
				switch (PlayerPrioritisedActions[i].Type)
				{
				case InteractionActionType::Kill:
					TerminalState = true;
				}

				// TODO: check for conflicts
				break;
			}

			// If no suitable move found (because of conflicts)
			if (i == PlayerPrioritisedActions.Num)
			{
				UE_LOG(LogTemp, Warning, TEXT("No move was able to be taken, defaulting to do nothing"));
			}
		}

		ElapsedMoves++;
	}
	return false;
}