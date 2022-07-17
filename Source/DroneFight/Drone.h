// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

/**
* @brief 无人机类
**/


class UStaticMeshComponent;
class UBoxComponent;
class UPhysicsThrusterComponent;
UCLASS()
class DRONEFIGHT_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/*属性成员*/


	//碰撞盒子
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* OutCollision;

	//无人机
	UPROPERTY(VisibleAnywhere) //提供垃圾回收机制、可以在虚幻引擎中访问、而且提供序列化能力
		UStaticMeshComponent* Mesh;

	//无人机飞翼 x 4
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle3;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle4;

	//推进器
	UPROPERTY(VisibleAnywhere)
		UPhysicsThrusterComponent* UpThruster;
	UPROPERTY(VisibleAnywhere)
		UPhysicsThrusterComponent* ForwardThruster;

};
