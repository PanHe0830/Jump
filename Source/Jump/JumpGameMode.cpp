// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpGameMode.h"
#include "JumpCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJumpGameMode::AJumpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
