// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskUE5GameModeBase.h"

#include "STUBaseCharacter.h"
#include "STUPlayerController.h"

ATestTaskUE5GameModeBase::ATestTaskUE5GameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
}
