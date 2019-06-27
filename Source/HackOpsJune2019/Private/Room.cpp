// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

FRoom::FRoom(const FRoom& Other)
{
	this->Items = Other.Items;
	this->Name = Other.Name;
	this->NumAllowedInside = Other.NumAllowedInside;
	this->NumCharactersInside = Other.NumCharactersInside;

	//Don't add adjacent rooms of the old one, they will have to be added later
}