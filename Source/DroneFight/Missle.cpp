// Fill out your copyright notice in the Description page of Project Settings.


#include "Missle.h"
#include "Components/StaticMeshComponent.h"
#include"Enemy.h"
#include"ToolLib.h"

// Sets default values
AMissle::AMissle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missle"));
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AMissle::OnBeginOverlap);
	
	MovementComp =CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MovementComp->InitialSpeed = 3000.0f;

}

// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissle::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AEnemy>())
	{
		OtherActor->Destroy();
		this->Destroy();
	}
	
}



