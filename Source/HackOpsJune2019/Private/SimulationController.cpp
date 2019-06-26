#include "SimulationController.h"

bool ASimulationController::SimulateFrom(FMapState* InitState)
{
	bool TerminalState = false;

	int ElapsedMoves = 0;
	while (!TerminalState && ElapsedMoves < MaxMoves)
	{
		auto& Actions = InitState->GetMotivationActions();
		for (auto& Action : Actions)
		{
			//To something
		}
		ElapsedMoves++;
	}
	return false;
}