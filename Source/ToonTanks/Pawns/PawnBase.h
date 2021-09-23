// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UMatineeCameraShake;


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurrentMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint = nullptr;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent = nullptr;
	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle= nullptr;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UCameraShakeBase> DeathShake;
public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDesctruction();

protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();
	virtual void TEST();



};
