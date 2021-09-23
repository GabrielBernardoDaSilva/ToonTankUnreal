// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurrent.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurrent : public APawnBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRate = 2.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRange = 500.0f;


	FTimerHandle FireRateTimeHandle;

	APawnTank* PlayerPawn = nullptr;

	void CheckFireCondition();

	float ReturnDistanceToPlay();


public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDesctruction() override;
protected:
	virtual void BeginPlay() override;
	virtual void TEST() override;
};
