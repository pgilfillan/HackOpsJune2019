// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Engine/World.h"

void FItem::SpawnItemBlueprint(AActor* ActorToSpawnWith, FRoom* room)
{
	UWorld* world = ActorToSpawnWith->GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParameters{};
		SpawnParameters.Owner = ActorToSpawnWith;
		SpawnParameters.Name = FName(*Name);

		// Vertical offset stops characters from looking strange when moving through each other
		const FVector SpawnLocation = FVector{ room->Location.X, room->Location.Y, room->Location.Z };
		const FRotator SpawnRotation{};
		world->SpawnActor(ItemBP, &SpawnLocation, &SpawnRotation, SpawnParameters);
	}
}