// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogTestActor, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

void ABaseGeometryActor::SetGeometryData(const FGeometryData& Data)
{
	GeometryData = Data;
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

// Called every frame
void ABaseGeometryActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			auto CurrentLocation = GetActorLocation();
			if (const auto World = GetWorld())
			{
				const auto Time = World->GetTimeSeconds();
				CurrentLocation.Z = InitLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
			}
			SetActorLocation(CurrentLocation);
		}
		break;

	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::PrintTypes() const
{
	UE_LOG(LogTestActor, Display, TEXT("Actor name %s"), *GetName());
	const auto WeaponsString = "Weapons number = " + FString::FromInt(WeaponsNumber);
	const auto HealthString = "Health = " + FString::SanitizeFloat(Health);
	const auto IsDeadString = "Is dead = " + FString(IsDead ? "true" : "false");
	const auto Stats = FString::Printf(
		TEXT(" \n == ALL STATS == \n %s \n %s \n %s"), *WeaponsString, *HealthString, *IsDeadString);
	UE_LOG(LogTestActor, Warning, TEXT("%s"), *Stats);
}

void ABaseGeometryActor::PrintStringTypes() const
{
	const auto Name = "Vitaliy Turov";
	UE_LOG(LogTestActor, Display, TEXT("Name is %s"), *Name);

	const auto WeaponsString = "Weapons number = " + FString::FromInt(WeaponsNumber);
	const auto HealthString = "Health = " + FString::SanitizeFloat(Health);
	const auto IsDeadString = "Is dead = " + FString(IsDead ? "true" : "false");

	const auto Stats = FString::Printf(
		TEXT(" \n == ALL STATS == \n %s \n %s \n %s"), *WeaponsString, *HealthString, *IsDeadString);
	UE_LOG(LogTestActor, Warning, TEXT("%s"), *Stats);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stats, true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::PrintTransform() const
{
	const auto Transform = GetActorTransform();
	const auto Location = Transform.GetLocation();
	const auto Rotation = Transform.Rotator();
	const auto Scale = Transform.GetScale3D();

	UE_LOG(LogTestActor, Display, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTestActor, Display, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogTestActor, Display, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogTestActor, Display, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogTestActor, Display, TEXT("Scale %s"), *Scale.ToString());

	UE_LOG(LogTestActor, Error, TEXT("Human transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	InitLocation = GetActorLocation();
	if (const auto DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const auto NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogTestActor, Display, TEXT("Timer count %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);
		OnColorChange.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogTestActor, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}