// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "CableComponent.h"
#include "BortalGameMode.generated.h"
/**
 * 
 */
UCLASS(minimalapi)

class ABortalGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	static void RoundH(int32& num);
	float _MatLerp, _GravMatLerp, _PopMatLerp, _PullMatLerp;
	
public:
	ABortalGameMode();

	// # Mat Lerps !
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	float MatLerpIncrement(float inc);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	float GravityMatLerpIncrement(float inc);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	float PopMatLerpIncrement(float inc);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	float PullMatLerpIncrement(float inc);

	// # Initializes internal spawn location using PlayerController's spawn location!
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	void BortalInit(ABortal6PlayerController* PlayerController);


	// # Respawn
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	void RespawnPlayer(ABortal6Character* Character, ABortal6PlayerController* Controller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	FVector SpawnLocation;

	// # Laser stuff 
	
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	int32 GiveLaserAmmo(FString ammoType, uint8 ammo);
	
	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	int32 GravUseAmmo(uint8 usage);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	int32 PopUseAmmo(uint8 usage);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	int32 PushUseAmmo(uint8 usage);

	UFUNCTION(BlueprintCallable, Category = "Jelqers")
	int32 PullUseAmmo(uint8 usage);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	int32 GravLaserEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	int32 PushLaserEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	int32 PopLaserEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	int32 PullLaserEnergy;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jelqers")
	bool bIsHoldingLaser;
	
};
