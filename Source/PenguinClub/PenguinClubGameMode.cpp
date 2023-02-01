// Copyright Epic Games, Inc. All Rights Reserved.

#include "PenguinClubGameMode.h"
#include "PengFu_PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APenguinClubGameMode::APenguinClubGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PengFu_PlayerCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
