// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "../Pawns/PawnTank.h"
#include "../Pawns/PawnTurrent.h"
#include "../PlayerController/PlayerControllerBase.h"
#include <Kismet/GameplayStatics.h>



void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDesctruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	}
	else if(APawnTurrent* DestroyedTurrent = Cast<APawnTurrent>(DeadActor)){
		DestroyedTurrent->HandleDesctruction();
		if (--TargetTurrent == 0)
		{
			HandleGameOver(true);
		}
	}
}


int32 ATankGameModeBase::GetTargetTurrentCount()
{


	TArray<AActor*> TurrentActors{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurrent::StaticClass(), TurrentActors);
	return TurrentActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{

	TargetTurrent = GetTargetTurrentCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	
	GameStart();
	if (PlayerControllerRef)
	{


		PlayerControllerRef->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}




