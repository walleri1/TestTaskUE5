#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChange, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float TimerRate = 3.0f;
};

UCLASS()
class TESTTASKUE5_API ABaseGeometryActor final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	void SetGeometryData(const FGeometryData& Data);

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const
	{
		return GeometryData;
	}

	UPROPERTY(BlueprintAssignable)
	FOnColorChange OnColorChange;
	
	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNumber = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillNumber = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 34.45648789f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitLocation;
	FTimerHandle TimerHandle;

	const int32 MaxTimerCount {5};
	int32 TimerCount {0};
	
	void PrintTypes() const;
	void PrintStringTypes() const;
	void PrintTransform() const;

	void SetColor(const FLinearColor& Color);

	void OnTimerFired();
};
