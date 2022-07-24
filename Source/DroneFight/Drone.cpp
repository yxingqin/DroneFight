// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "KismetCastingUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ToolLib.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true; //设置每一帧都调用tick
	InitMesh();
	InitCamera();
	InitParam();
	InitThruster();
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
	//旋转机翼
	RoutePaddle(DeltaTime);
	
	// 在操控时 还原推进器强度
	if (GetInputAxisValue(TEXT("Lift")) == 0.0f)
		UpThruster->ThrustStrength = 980.0f * OutCollision->GetMass();//
	if (GetInputAxisValue(TEXT("Forward")) == 0.0f)
	{
		ForwardThruster->ThrustStrength = 0.0f;
		//还原机身体 倾斜
		auto Pitch = Mesh->GetRelativeRotation().Pitch;
		if(Pitch!=0)
		{
			Mesh->AddRelativeRotation(FRotator(-Pitch*DeltaTime,.0f,.0f));
			if(FMath::Abs(Mesh->GetRelativeRotation().Pitch)<=KINDA_SMALL_NUMBER)
				Mesh->SetRelativeRotation(FRotator(.0f,.0f,.0f));
		}
	}
	
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定输入
	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAxis(TEXT("CameraX"), this, &ADrone::CameraX);
	PlayerInputComponent->BindAxis(TEXT("CameraY"), this, &ADrone::CameraY);
}

void ADrone::InitMesh()
{
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
}

void ADrone::InitParam()
{	
 	this->VerticalAcc = 2000.0f;
 	this->HorizonAcc = 2000.0f;
	this->TurnAcc = 100000000.0f;
 	
 	this->VerThrustStrengthAbsMax = 3000.0f;
 	this->HorThrustStrengthAbsMax = 3000.0f;

	this->PaddleRouteSpeed=2000.0f;
}

void ADrone::InitCamera()
{	
 	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
 	SpringArmComponent->SetupAttachment(RootComponent);
 	SpringArmComponent->TargetArmLength = 300.0f;
 
 	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
 	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->AddRelativeRotation(FRotator(-25.0f,.0f,.0f));
}

void ADrone::InitThruster()
{
    	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
    	UpThruster->SetupAttachment(RootComponent);
    	UpThruster->ThrustStrength = 980.0f;
    	UpThruster->SetAutoActivate(true);
    	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorUpVector()));//旋转到向下
    	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));
    	ForwardThruster->SetupAttachment(RootComponent);
    	ForwardThruster->ThrustStrength = 0.0f;
    	ForwardThruster->SetAutoActivate(true);
    	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-GetActorForwardVector()));//旋转到向下
}

void ADrone::RoutePaddle(float DeltaTime)
{
	Paddle1->AddRelativeRotation(FRotator(0.0f,PaddleRouteSpeed*DeltaTime,0.0f));
	Paddle2->AddRelativeRotation(FRotator(0.0f,PaddleRouteSpeed*DeltaTime,0.0f));
	Paddle3->AddRelativeRotation(FRotator(0.0f,PaddleRouteSpeed*DeltaTime,0.0f));
	Paddle4->AddRelativeRotation(FRotator(0.0f,PaddleRouteSpeed*DeltaTime,0.0f));
}

void ADrone::CameraX(float scale)
{
	SpringArmComponent->AddRelativeRotation(FRotator(0,scale,0));
}

void ADrone::CameraY(float scale)
{
	auto  temp =SpringArmComponent->GetRelativeRotation();
	if(temp.Pitch<=45.0f&&scale>0||temp.Pitch>=-45.0f&&scale<0)
		SpringArmComponent->AddRelativeRotation(FRotator(scale,0,0));
}


void ADrone::Lift(float scale)
{
	//上下移动   注意涉及到每一帧都需要累计的操作，需要乘以一个系数
	UpThruster->ThrustStrength += scale * VerticalAcc * GetWorld()->DeltaRealTimeSeconds;//需要结合帧率的时间
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -VerThrustStrengthAbsMax, VerThrustStrengthAbsMax);
}
void ADrone::Forward(float scale)
{
	auto delta =  GetWorld()->DeltaRealTimeSeconds;
	ForwardThruster->ThrustStrength += delta*scale*HorizonAcc;
	ForwardThruster->ThrustStrength = FMath::Clamp(ForwardThruster->ThrustStrength, -HorThrustStrengthAbsMax, HorThrustStrengthAbsMax);
	if(FMath::Abs(Mesh->GetRelativeRotation().Pitch)<30.0f)
		Mesh->AddRelativeRotation(FRotator(-scale*delta*100.0f,.0f,.0f));
}
void ADrone::Turn(float scale)
{
	OutCollision->AddTorqueInDegrees(GetActorUpVector() * scale * TurnAcc * GetWorld()->DeltaRealTimeSeconds);
}
