// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Item.h"

FRoom::FRoom(const FRoom& Other)
{
	this->Items = Other.Items;
	this->Name = Other.Name;
	this->NumAllowedInside = Other.NumAllowedInside;
	this->NumCharactersInside = Other.NumCharactersInside;

	//Don't add adjacent rooms of the old one, they will be added later
}

bool FRoom::ItemInRoom(const FString& ItemName)
{
	for (auto& Item : Items)
	{
		if (Item->Name == ItemName)
		{
			return true;
		}
	}

	return false;
}