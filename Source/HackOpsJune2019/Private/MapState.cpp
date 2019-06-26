#include "MapState.h"

TArray<TSharedPtr<TArray<FMotivationAction>>> FMapState::GetMotivationActions()
{
	TArray<TSharedPtr<TArray<FMotivationAction>>> Actions;
	for (auto& Character : Characters)
	{
		Actions.Add(Character.GetPrioritisedMotivationActions(this));
	}
	return Actions;
}