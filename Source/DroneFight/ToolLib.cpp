// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolLib.h"

namespace ToolLib 
{
	void  LogMessage(const FString& m, bool isToScreen)
	{
		if (isToScreen)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, *m);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *m);
		}
	}
}

