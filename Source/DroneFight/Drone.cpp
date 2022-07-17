// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true; //设置每一帧都调用tick
	
	/*碰撞体*/
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;//作为Root元素
	OutCollision->SetBoxExtent(FVector(90,90,40));//设置大小
	OutCollision->SetSimulatePhysics(true);//开启物理
	OutCollision->SetCollisionProfileName(TEXT("Pawn"));
	//锁定X Y 旋转，防止发生倾斜
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	/*设置无人机模型*/
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));//无人机主体
	Mesh->SetupAttachment(OutCollision);
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));//飞翼
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));
	//飞翼挂在 到无人机上
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	/*设置推进器*/
	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>("UpThruster");
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorUpVector()));//旋转到向下

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>("ForwardThruster");
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorForwardVector()));//旋转到向下

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

