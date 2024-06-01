// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameSaveSubsystem.h"

#include "EngineUtils.h"
#include "Game/Saveable.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "SteamMystery/Public/Game/GameSave.h"

void UGameSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UGameplayStatics::DoesSaveGameExist("Save", 0))
		LoadGame("Save");
	else
		CurrentSaveGame = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
}

UGameSave* UGameSaveSubsystem::GetSave() const
{
	return CurrentSaveGame;
}

void UGameSaveSubsystem::SaveActors() const
{
	// ... < playerstate saving code ommitted >

	// Clear all actors from any previously loaded save to avoid duplicates
	CurrentSaveGame->SavedActors.Empty();

	// Iterate the entire world of actors
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (IsValid(Actor) || !Actor->Implements<USaveable>())
			continue;

		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();

		// Pass the array to fill with data from Actor
		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}
}

void UGameSaveSubsystem::LoadActors() const
{
	if (CurrentSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));

	// Iterate the entire world of actors
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		// Only interested in our 'gameplay actors'
		if (!Actor->Implements<USaveable>()) continue;

		for (auto [ActorName, Transform, ByteData] : CurrentSaveGame->SavedActors)
		{
			if (ActorName == Actor->GetFName())
			{
				Actor->SetActorTransform(Transform);

				FMemoryReader MemReader(ByteData);

				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				// Convert binary array back into actor's variables
				Actor->Serialize(Ar);

				ISaveable::Execute_OnActorLoaded(Actor);

				break;
			}
		}
	}
}

void UGameSaveSubsystem::LoadGame(const FString InSlotName)
{
	if (const auto SaveGame = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(InSlotName, 0)))
	{
		CurrentSaveGame = SaveGame;
		OnSaveLoaded.Broadcast(CurrentSaveGame);
	}
}

void UGameSaveSubsystem::SaveGame(const FString InSlotName) const
{
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, InSlotName, 0);
}

void UGameSaveSubsystem::StartNewGame() const
{
	UGameplayStatics::OpenLevel(GetWorld(), CurrentSaveGame->CurrentLevel);
}

void UGameSaveSubsystem::ClearSaves()
{
	UGameplayStatics::DeleteGameInSlot("Saves", 0);
	UGameplayStatics::DeleteGameInSlot("QuestData", 0);
}
