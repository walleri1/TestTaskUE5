// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestTaskUE5GameModeBase.h"

#include "CubeCharacter.h"
#include "CubePlayerController.h"

ATestTaskUE5GameModeBase::ATestTaskUE5GameModeBase()
{
	DefaultPawnClass = ACubeCharacter::StaticClass();
	PlayerControllerClass = ACubePlayerController::StaticClass();
}
