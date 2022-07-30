// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VorbisAudioInfo.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class UStaticMeshComponent;
UCLASS()
class DRONEFIGHT_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void OnDestroy(AActor* DestroyedActor);
};
