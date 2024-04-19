// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Bortal6PlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class BORTAL6_API ABortal6PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
public:

	virtual void BeginPlay() override;
	
	// End Actor interface
};
