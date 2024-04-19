// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
	
UENUM(BlueprintType, Category = "MyEnums")  
enum class ELaserType : uint8
{
	Push        UMETA(DisplayName = "Push"), //0
	Slow        UMETA(DisplayName = "Slow"), //1
	Pop			UMETA(DisplayName = "Pop"),  //2
	Pull		UMETA(DisplayName = "Pull")  //3
};
