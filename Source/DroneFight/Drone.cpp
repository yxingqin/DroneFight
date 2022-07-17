// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true; //����ÿһ֡������tick
	
	/*��ײ��*/
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;//��ΪRootԪ��
	OutCollision->SetBoxExtent(FVector(90,90,40));//���ô�С
	OutCollision->SetSimulatePhysics(true);//��������
	OutCollision->SetCollisionProfileName(TEXT("Pawn"));
	//����X Y ��ת����ֹ������б
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	/*�������˻�ģ��*/
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));//���˻�����
	Mesh->SetupAttachment(OutCollision);
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));//����
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));
	//������� �����˻���
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	/*�����ƽ���*/
	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>("UpThruster");
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorUpVector()));//��ת������

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>("ForwardThruster");
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorForwardVector()));//��ת������

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

