// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopGameGameMode.h"
#include "CoopGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoopGameGameMode::ACoopGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
