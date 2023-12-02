// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/AI/MainAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"



AMainAIController::AMainAIController(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void AMainAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->ClearValue(TEXT("DetectedActor"));
	}
	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMainAIController::OnSensed);
		// AIPerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AMainAIController::OnInfoChanged);vara
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppPassValueParameterByConstReference
void AMainAIController::OnSensed(AActor* SourceActor, FAIStimulus Stimulus)
{
	if (SourceActor == GetPawn())
		return;
	UE_LOG(LogClass, Warning, TEXT("Sight Triggered"));
	const auto KeyName = TEXT("DetectedActor");
	if (const auto GameCharacter = Cast<AGameCharacter>(SourceActor))
		if (const auto Health = GameCharacter->Health; !Health->IsDead() && Stimulus.WasSuccessfullySensed())
			GetBlackboardComponent()->SetValueAsObject(KeyName, SourceActor);
		else
			GetBlackboardComponent()->ClearValue(KeyName);
}

void AMainAIController::OnInfoChanged(const FActorPerceptionUpdateInfo& Info)
{
	if (const auto SourceActor = Info.Target; SourceActor.IsValid())
	{
		UE_LOG(LogClass, Warning, TEXT("Sight Triggered"));
		const auto BlackboardComponent = GetBlackboardComponent();
		const auto KeyName = TEXT("DetectedActor");
		if (const auto GameCharacter = Cast<AGameCharacter>(SourceActor))
			if (const auto Health = GameCharacter->Health; !Health->IsDead() && Info.Stimulus.WasSuccessfullySensed())
				BlackboardComponent->SetValueAsObject(KeyName, SourceActor.Get());
		// else
		// 	BlackboardComponent->ClearValue(KeyName);
	}
}

void AMainAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// void AMainAIController::UpdateControlRotation(const float DeltaTime, const bool bUpdatePawn)
// {
// 	if (const auto MyPawn = GetPawn())
// 	{
// 		auto NewControlRotation = GetControlRotation();
//
// 		// Look toward focus
// 		if (const FVector FocalPoint = GetFocalPoint(); FAISystem::IsValidLocation(FocalPoint))
// 			NewControlRotation = (FocalPoint - MyPawn->GetPawnViewLocation()).Rotation();
// 		else if (bSetControlRotationFromPawnOrientation)
// 			NewControlRotation = MyPawn->GetActorRotation();
//
// 		// We override this so flying units can go up and down
// 		//// Don't pitch view unless looking at another pawn
// 		//if (NewControlRotation.Pitch != 0 && Cast<APawn>(GetFocusActor()) == nullptr)
// 		//{
// 		//  NewControlRotation.Pitch = 0.f;
// 		//}
//
// 		SetControlRotation(NewControlRotation);
//
// 		// if (bUpdatePawn)
// 		// 	if (const FRotator CurrentPawnRotation = MyPawn->GetActorRotation();
// 		// 		CurrentPawnRotation.Equals(NewControlRotation, 1e-3f) == false)
// 		// 		MyPawn->FaceRotation(NewControlRotation, DeltaTime);
// 		if (bUpdatePawn)
// 		{
// 			SmoothTargetRotation = UKismetMathLibrary::RInterpTo_Constant(
// 				MyPawn->GetActorRotation(), ControlRotation, DeltaTime, SmoothFocusInterpSpeed);
// 			//if (CurrentPawnRotation.Equals(SmoothTargetRotation, 1e-3f) == false)
// 			MyPawn->FaceRotation(SmoothTargetRotation, DeltaTime);
// 		}
// 	}
// }
