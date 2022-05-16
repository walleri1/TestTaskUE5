#include "SandBoxPlayerController.h"

#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandBoxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandBoxPlayerController::ChangePawn);
	}
}

void ASandBoxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandBoxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;

	const auto CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();

	if (!CurrentPawn) return;

	UE_LOG(LogSandboxPlayerController, Error, TEXT("Change player pawn"));
	Possess(CurrentPawn);
}
