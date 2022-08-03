// Copyright Epic Games, Inc. All Rights Reserved.

#include "TempProject01GameMode.h"
#include "TempProject01Character.h"
#include "UObject/ConstructorHelpers.h"

ATempProject01GameMode::ATempProject01GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
