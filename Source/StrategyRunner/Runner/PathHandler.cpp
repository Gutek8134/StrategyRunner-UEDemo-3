// Fill out your copyright notice in the Description page of Project Settings.


#include "PathHandler.h"

// Sets default values
APathHandler::APathHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APathHandler::BeginPlay()
{
	Super::BeginPlay();
	Chunks.Add(GetWorld()->SpawnActor<AActor>(ChunkClass.Get(), GetActorLocation() + FVector(ChunkSize.X / 2, 0, 0), GetActorRotation()));
	Chunks.Add(GetWorld()->SpawnActor<AActor>(ChunkClass.Get(), GetActorLocation() - FVector(ChunkSize.X / 2, 0, 0), GetActorRotation()));

}

// Called every frame
void APathHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (const auto& el : Chunks) {
		el->SetActorLocation(el->GetActorLocation() - Step * DeltaTime);
	}

	if (Chunks.Num() == 1) {
		SpawnChunk();
	}
}


void APathHandler::SpawnChunk() {
	Chunks.Add(GetWorld()->SpawnActor<AActor>(ChunkClass.Get(), GetActorLocation() + FVector(ChunkSize.X, 0, 0), GetActorRotation()));
}

void APathHandler::RemoveChunk(AActor* Chunk) {
	Chunks.Remove(Chunk);
}