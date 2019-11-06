// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
	: CurrentPawnSpeed(0.f)
	, IsInAir(false)
	, IsDead(false)
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Book/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage'"));
	
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UABAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage);
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn =  TryGetPawnOwner();
	if (IsValid(pawn))
	{
		CurrentPawnSpeed = pawn->GetVelocity().Size();
		IsInAir = pawn->GetMovementComponent()->IsFalling();
	}
}

void UABAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(newSection), AttackMontage);
}

void UABAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	ABLOG_S(Warning);
	OnAttackHitDelegate.Broadcast();
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheckDelegate.Broadcast();
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), section));
}
