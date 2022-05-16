// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskUE5GameModeBase.h"

#include "SandboxPawn.h"
#include "SandBoxPlayerController.h"

ATestTaskUE5GameModeBase::ATestTaskUE5GameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandBoxPlayerController::StaticClass();
}
