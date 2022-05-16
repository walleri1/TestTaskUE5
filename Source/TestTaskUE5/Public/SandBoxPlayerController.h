// Vitaliy Turov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandBoxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASKUE5_API ASandBoxPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AActor*> Pawns;

	int32 CurrentPawnIndex { 0 };
	
	void ChangePawn();
};
