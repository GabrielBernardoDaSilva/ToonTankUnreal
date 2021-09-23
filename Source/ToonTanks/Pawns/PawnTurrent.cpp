// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurrent.h"
#include "PawnTank.h"
#include <Kismet/GameplayStatics.h>


void APawnTurrent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimeHandle, this, &APawnTurrent::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TEST();
}

void APawnTurrent::HandleDesctruction()
{
	Super::HandleDesctruction();
	Destroy();
}

void APawnTurrent::TEST()
{
	Super::TEST();
	UE_LOG(LogTemp, Warning, TEXT("Turrent Class"))
}


void APawnTurrent::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlay() > FireRange)	
		return;
	RotateTurret(PlayerPawn->GetActorLocation());
} 


void APawnTurrent::CheckFireCondition() {
	if (!PlayerPawn	|| !PlayerPawn->GetIsPlayerAlive()) return;
	if (ReturnDistanceToPlay() <= FireRange)
	{
		Fire();
	}
	
}

float APawnTurrent::ReturnDistanceToPlay()
{
	if (!PlayerPawn) return 0.0f;
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
