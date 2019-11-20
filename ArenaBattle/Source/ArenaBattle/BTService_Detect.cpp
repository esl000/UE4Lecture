// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "ABCharacter.h"

UBTService_Detect::UBTService_Detect()
{

}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto Center = ControllingPawn->GetActorLocation();
	auto World = ControllingPawn->GetWorld();

	float detachRadius = 600.f;
	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(detachRadius),
		CollisionQueryParam);

	if (bResult)
	{
		for(auto const& overlapResult : OverlapResults)
		{
			auto ABCharacter = Cast<AABCharacter>(overlapResult.GetActor());
			if (ABCharacter && ABCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(
					FName(TEXT("Target")), ABCharacter);
				DrawDebugSphere(World, Center, 500.f, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(
		FName(TEXT("Target")), nullptr);

	DrawDebugSphere(World, Center, 500.f, 16, FColor::Red, false, 0.2f);
}
