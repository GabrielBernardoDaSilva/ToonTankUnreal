// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>



APawnTank::APawnTank()
{
	SpringArms = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArms->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArms);


}
// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

}

void APawnTank::HandleDesctruction()
{
	Super::HandleDesctruction();
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Rotate();
	Move();

	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult{};
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);

}

void APawnTank::CalculateMoveInput(const float Value)
{
	MoveDirections = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(const float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(std::move(Rotation));
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirections, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}


