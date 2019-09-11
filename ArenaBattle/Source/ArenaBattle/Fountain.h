// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Water;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Splash;

	UPROPERTY(VisibleAnywhere)
	class URotatingMovementComponent* Movement;

	UPROPERTY(EditAnywhere, Category = ID)
	int32 ID;

private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;

};
