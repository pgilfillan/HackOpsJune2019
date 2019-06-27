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
		FRoom NewRoom{};
		NewRoom.Name = RoomNames[i];
		NewRoom.Location = RoomLocations[i];
		Rooms.Emplace(NewRoom.Name, MakeShared<FRoom>(NewRoom));
	}

	for (int i = 0; i < CharacterNames.Num(); ++i)
	{
		auto SRand = FRandomStream(Seed);
		auto SelectedRoomIndex = SRand.RandRange(0, Rooms.Num());
		int CurrIndex = 0;
		for (auto& RoomPair : Rooms)
		{
			if (CurrIndex == SelectedRoomIndex)
			{
				FGameCharacter NewCharacter;

				switch (CharacterNamesMap[CharacterNames[i]])
				{
				case Character::ColMust:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<ColMustardBehaviour>());
					break;
				case Character::DrBlack:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<DrBlackBehaviour>());
					break;
				case Character::MrsPeac:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<MrsPeacockBehaviour>());
					break;
				case Character::MrsWhite:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<MrsWhiteBehaviour>());
					break;
				case Character::MsScar:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<MissScarletBehaviour>());
					break;
				case Character::ProfPlum:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<ProfPlumBehaviour>());
					break;
				case Character::RevGreen:
					NewCharacter = FGameCharacter(CharacterNames[i], CharacterBPs[i], RoomPair.Value, MakeShared<RevGreenBehaviour>());
					break;
				default:
					UE_LOG(LogTemp, Error, TEXT("FMapState::GenerateMapState: Unable to recognise character name"));
					break;
				}

				Characters.Add(MakeShared<FGameCharacter>(NewCharacter));
			}
		}
	}
}

void FMapState::SpawnAllCharacterBlueprint(AActor* ActorToSpawnWith)
{
	for (int i = 0; i < Characters.Num(); ++i)
	{
		Characters[i]->SpawnCharacterBlueprint(ActorToSpawnWith);
	}
}