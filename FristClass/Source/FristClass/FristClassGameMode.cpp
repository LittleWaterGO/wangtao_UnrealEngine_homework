// Copyright Epic Games, Inc. All Rights Reserved.

#include "FristClassGameMode.h"
#include "FristClassCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFristClassGameMode::AFristClassGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
