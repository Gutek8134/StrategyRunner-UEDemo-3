// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathHandler.generated.h"

UCLASS()
class STRATEGYRUNNER_API APathHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SpawnChunk();

	UFUNCTION(BlueprintCallable)
		void RemoveChunk(AActor* Chunk);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Chunk|Chunk")
		TSubclassOf<AActor> ChunkClass;

	UPROPERTY(EditAnywhere, Category = "Chunk|Chunk")
		FVector ChunkSize = FVector(100, 50, 0);

	UPROPERTY(EditAnywhere, Category = "Chunk|Chunk Movement")
		FVector Step = FVector(10, 0, 0);

private:
	TArray<AActor*> Chunks;
};
