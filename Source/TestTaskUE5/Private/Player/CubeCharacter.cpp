#include "CubeCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACubeCharacter::ACubeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset.Z = 80;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACubeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACubeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACubeCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACubeCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ACubeCharacter::AddControllerYawInput);
}

void ACubeCharacter::MoveForward(const float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ACubeCharacter::MoveRight(const float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

