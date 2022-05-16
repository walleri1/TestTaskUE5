// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT()
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};

UCLASS()
class TESTTASKUE5_API AGeometryHubActor final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();
	void DoActorSpawn1() const;
	void DoActorSpawn2() const;
	void DoActorSpawn3();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
