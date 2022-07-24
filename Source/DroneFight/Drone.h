// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"


class UStaticMeshComponent;
class UBoxComponent;
class UPhysicsThrusterComponent;
class USpringArmComponent;
class UCameraComponent;
/**
* @brief  无人机类
*/
UCLASS()
class DRONEFIGHT_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//垂直操纵
	UFUNCTION()
	void Lift(float scale);
	//水平 操控
	UFUNCTION()
	void Forward(float scale);
	//旋转操控
	UFUNCTION()
	void Turn(float scale);
	//摄像机 X轴
	void CameraX(float scale);
	//摄像机 Y轴
	void CameraY(float scale);
	
	
protected:
	virtual void BeginPlay() override;
private:
	//初始网格体
	void InitMesh();
	//初始化 参数
	void InitParam();
	//初始化 摄像机
	void InitCamera();
	//初始化 推进器
	void InitThruster();
	//旋转机翼
	void RoutePaddle(float DeltaTime);
public:	


	//碰撞盒子
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UBoxComponent* OutCollision;
	//无人机
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	//无人机飞翼 x 4

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Paddle3;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Paddle4;

	//向上的推进器
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UPhysicsThrusterComponent* UpThruster;
	//向下的推进器
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UPhysicsThrusterComponent* ForwardThruster;

	//上下灵敏
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float VerticalAcc;
	//水平灵敏
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float HorizonAcc;
	//旋转灵敏
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float TurnAcc;
	//垂直 最大推力
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float VerThrustStrengthAbsMax;
	//水平 最大推力
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float HorThrustStrengthAbsMax;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "ControlSensitivity")
	float PaddleRouteSpeed;
	//摄像机臂
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	//摄像机
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UCameraComponent* CameraComponent;

};
