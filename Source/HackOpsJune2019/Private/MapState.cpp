#include "MapState.h"
#include "GameCharacter.h"
#include "Room.h"
#include "CharacterBehaviours/CharacterBehaviour.h"
#include "RandomStream.h"

FMapState::FMapState(const FMapState& Other)
{
	// Copy rooms
	for (const auto& OtherRoomPair : Other.Rooms)
	{
		auto RoomCopy = MakeShared<FRoom>(OtherRoomPair.Value.ToSharedRef().Get());
		this->Rooms.Emplace(RoomCopy->Name, RoomCopy);
	}

	// Add adjaceny list
	for (const auto& OtherRoomPair : Other.Rooms)
	{
		for (const auto& Room : OtherRoomPair.Value->AdjacentRooms)
		{
			Rooms[OtherRoomPair.Key]->AdjacentRooms.Add(Rooms[Room->Name]);
		}
	}

	// Copy characters
	for (const auto& OtherCharacter : Other.Characters)
	{
		auto& OtherCurrRoomName = OtherCharacter->CurrRoom->Name;
		auto& CurrRoom = Rooms[OtherCurrRoomName];

		auto CharacterCopy = MakeShared<FGameCharacter>(OtherCharacter.ToSharedRef().Get(), CurrRoom);
		this->Characters.Emplace(CharacterCopy);
	}
}

void FMapState::GenerateMapState(int Seed, TArray<FString> CharacterNames, TArray<TSubclassOf<AActor>> CharacterBPs, TArray<FString> RoomNames, TArray<FVector> RoomLocations)
{
	// TODO: this is a duplicate of the one in CharacterBehaviour.h, need to put in a common place
	TMap<FString, Character> CharacterNamesMap;
	CharacterNamesMap.Emplace(FString(TEXT("Colonel Mustard")), Character::ColMust);
	CharacterNamesMap.Emplace(FString(TEXT("Miss Scarlet")), Character::MsScar);
	CharacterNamesMap.Emplace(FString(TEXT("Professor Plum")), Character::ProfPlum);
	CharacterNamesMap.Emplace(FString(TEXT("Reverend Green")), Character::RevGreen);
	CharacterNamesMap.Emplace(FString(TEXT("Mrs White")), Character::MrsWhite);
	CharacterNamesMap.Emplace(FString(TEXT("Mrs Peacock")), Character::MrsPeac);
	CharacterNamesMap.Emplace(FString(TEXT("Dr Black")), Character::DrBlack);

	for (int i = 0; i < RoomNames.Num(); ++i)
	{
		TSharedPtr<FRoom> NewRoom = MakeShared<FRoom>();
		NewRoom->Name = RoomNames[i];
		NewRoom->Location = RoomLocations[i];
		Rooms.Emplace(NewRoom->Name, NewRoom);
	}

	auto SRand = FRandomStream(Seed);
	for (int i = 0; i < CharacterNames.Num(); ++i)
	{
		auto SelectedRoomIndex = SRand.RandRange(0, Rooms.Num() - 1);
		auto SelectedRoom = Rooms[RoomNames[SelectedRoomIndex]];

		TSharedPtr<FGameCharacter> NewCharacter;
		switch (CharacterNamesMap[CharacterNames[i]])
		{
		case Character::ColMust:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<ColMustardBehaviour>());
			break;
		case Character::DrBlack:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<DrBlackBehaviour>());
			break;
		case Character::MrsPeac:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<MrsPeacockBehaviour>());
			break;
		case Character::MrsWhite:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<MrsWhiteBehaviour>());
			break;
		case Character::MsScar:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<MissScarletBehaviour>());
			break;
		case Character::ProfPlum:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<ProfPlumBehaviour>());
			break;
		case Character::RevGreen:
			NewCharacter = MakeShared<FGameCharacter>(CharacterNames[i], CharacterBPs[i], SelectedRoom, MakeShared<RevGreenBehaviour>());
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("FMapState::GenerateMapState: Unable to recognise character name"));
			break;
		}

		Characters.Add((NewCharacter));
	}
}

void FMapState::SpawnAllCharacterBlueprint(AActor* ActorToSpawnWith)
{
	for (int i = 0; i < Characters.Num(); ++i)
	{
		Characters[i]->SpawnCharacterBlueprint(ActorToSpawnWith, i );
	}
}