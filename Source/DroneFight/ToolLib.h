// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * @brief  常用函数 在这里单独作为一个模块封装一下
 */

// 打印在屏幕上
#define DEBUG_ON_SCREEN(FMT,...)  GEngine->AddOnScreenDebugMessage( -1,1.0f,FColor::Blue,*FString::Printf(TEXT(FMT),__VA_ARGS__))

//打印在日志里面
#define DEBUG_ON_LOG(FMT,...)  UE_LOG(LogTemp,Log,TEXT(FMT),__VA_ARGS__)




namespace ToolLib
{
};
