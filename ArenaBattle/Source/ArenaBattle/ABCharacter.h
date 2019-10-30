// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	FVector DirectionToMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ISComboInputOn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanNextCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UABAnimInstance* ABAnim;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpDown(float delta);
	void LeftRight(float delta);
	void Attack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);


	void AttackStartComboState();
	void AttackEndComboState();
};
