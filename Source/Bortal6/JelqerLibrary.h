// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JelqerLibrary.generated.h"

class AStaticMeshActor;
/**
 * 
 */
UCLASS()
class BORTAL6_API UJelqerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:

public:
	
	/**	
	 * Changes settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	static void SettingsChanger();
};
