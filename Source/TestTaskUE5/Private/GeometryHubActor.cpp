#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	DoActorSpawn3();
}

void AGeometryHubActor::DoActorSpawn1() const
{
	if (const auto World = GetWorld())
	{
		for (int32 i = 0; i < 10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));

			if (ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform))
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2() const
{
	if (const auto World = GetWorld())
	{
		for (int32 i = 0; i < 10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));

			if (ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform))
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	if (const auto World = GetWorld())
	{
		for (const auto [valueGeometryClass, valueData, valueInitialTransform] : GeometryPayloads)
		{
			if (ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(valueGeometryClass, valueInitialTransform))
			{
				Geometry->SetGeometryData(valueData);
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				Geometry->FinishSpawning(valueInitialTransform);
			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	const auto Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude %f"), Geometry->GetGeometryData().Amplitude);
	
	Geometry->SetLifeSpan(2.0f);
}

// Called every frame
void AGeometryHubActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}