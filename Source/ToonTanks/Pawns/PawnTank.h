#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArms = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera = nullptr;

	FVector MoveDirections;
	FQuat RotationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed = 100.0f;

	APlayerController* PlayerControllerRef = nullptr;
	bool bIsPlayerAlive = true;

	void CalculateMoveInput(const float Value);
	void CalculateRotateInput(const float Value);

	void Move();
	void Rotate();

public:


	APawnTank();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDesctruction() override;

	bool GetIsPlayerAlive();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
