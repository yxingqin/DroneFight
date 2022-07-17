// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

/**
* @brief ���˻���
**/


class UStaticMeshComponent;
class UBoxComponent;
class UPhysicsThrusterComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DRONEFIGHT_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//�ٿ�
	UFUNCTION()
		void Lift(float scale);
	UFUNCTION()
		void Forward(float scale);
	UFUNCTION()
		void Turn(float scale);
protected:
	virtual void BeginPlay() override;
public:	


	/*���Գ�Ա*/

	//��ײ����
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* OutCollision;

	//���˻�
	UPROPERTY(VisibleAnywhere) //�ṩ�������ջ��ơ���������������з��ʡ������ṩ���л�����
		UStaticMeshComponent* Mesh;

	//���˻����� x 4
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle3;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Paddle4;

	//�ƽ���
	UPROPERTY(VisibleAnywhere)
		UPhysicsThrusterComponent* UpThruster;
	UPROPERTY(VisibleAnywhere)
		UPhysicsThrusterComponent* ForwardThruster;

	//�ٿ�������
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Init")
		float LiftAcc;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Init")
		float ForwardAcc;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Init")
		float TurnAcc;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Init")
		float ThrustStrengthMax;

	//��������
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent;//����� ��
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;//�����
};
