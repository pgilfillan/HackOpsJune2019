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

FMapState& ASimulationController::ResetSimulationState(
	int Seed,
	TArray<FString> CharacterNames,
	TArray<TSubclassOf<AActor>> CharacterBPs,
	TArray<FString> RoomNames,
	TArray<FVector> RoomLocations,
	TArray<FString> ItemNames,
	TArray<TSubclassOf<AActor>> ItemBPs
)
{
	RootMapState->GenerateMapState(Seed, CharacterNames, CharacterBPs, RoomNames, RoomLocations, ItemNames, ItemBPs);
	RootMapState->SpawnAllCharacterBlueprint(this);
	RootMapState->SpawnAllItemBlueprint(this);
	return RootMapState.ToSharedRef().Get();
}

FMapState& ASimulationController::JumpSteps(UPARAM(ref) FMapState& Current, int32 NumSteps)
{
	if (NumSteps < 0)
	{
		if (!Current.ParentState.IsValid())
		{
			return Current;
		}

		auto& CurrStatePtr = Current.ParentState;
		NumSteps++;
		while (NumSteps < 0 && CurrStatePtr->ParentState.IsValid())
		{
			CurrStatePtr = Current.ParentState;
			NumSteps++;
		}
		return CurrStatePtr.ToSharedRef().Get();
	} else
	{
		if (!Current.ParentState.IsValid())
		{
			return Current;
		}

		auto& CurrStatePtr = Current.NextState;
		NumSteps--;
		while (NumSteps > 0 && CurrStatePtr->NextState.IsValid())
		{
			CurrStatePtr = Current.NextState;
			NumSteps--;
		}
		return CurrStatePtr.ToSharedRef().Get();
	}

	return Current;
}

void ASimulationController::ChangeDoorOpen(UPARAM(ref) FMapState& Current, FString RoomName1, FString RoomName2, bool IsOpen)
{
	if (IsOpen)
	{
		Current.Rooms[RoomName1]->AdjacentRooms.Add(Current.Rooms[RoomName2]);
		Current.Rooms[RoomName2]->AdjacentRooms.Add(Current.Rooms[RoomName1]);
	} else
	{
		const bool bAllowShrinking = false;
		auto& Adj1 = Current.Rooms[RoomName1]->AdjacentRooms;
		for (int32 Index = Adj1.Num() - 1; Index >= 0; --Index)
		{
			if (auto Room = Adj1[Index].Pin())
			{
				if (Room->Name == RoomName2)
				{
					Adj1.RemoveAt(Index, 1, bAllowShrinking);
				}
			}
		}
		auto& Adj2 = Current.Rooms[RoomName2]->AdjacentRooms;
		for (int32 Index = Adj2.Num() - 1; Index >= 0; --Index)
		{
			if (auto Room = Adj2[Index].Pin())
			{
				if (Room->Name == RoomName1)
				{
					Adj2.RemoveAt(Index, 1, bAllowShrinking);
				}
			}
		}
	}
}

FString ASimulationController::GetRoomNameForCharacter(UPARAM(ref) FMapState& State, FString CharacterName)
{
	for (int i = 0; i < State.Characters.Num(); ++i)
	{
		if (State.Characters[i]->Name == CharacterName)
		{
			return State.Characters[i]->CurrRoom->Name;
		}
	}
	return "";
}