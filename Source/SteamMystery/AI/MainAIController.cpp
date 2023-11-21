// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Prediction.h"

AMainAIController::AMainAIController()
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
	}
	if (AIPerceptionComponent)
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMainAIController::OnSensed);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppPassValueParameterByConstReference
void AMainAIController::OnSensed(AActor* SourceActor, FAIStimulus Stimulus)
{
	UE_LOG(LogClass, Warning, TEXT("Sight Triggered"));
	const auto BlackboardComponent = GetBlackboardComponent();
	const auto KeyName = TEXT("DetectedActor");
	if (Stimulus.WasSuccessfullySensed())
		BlackboardComponent->SetValueAsObject(KeyName, SourceActor);
	else
	{
		BlackboardComponent->ClearValue(KeyName);
	}
}

void AMainAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
