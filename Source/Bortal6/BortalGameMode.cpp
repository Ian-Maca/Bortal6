// Fill out your copyright notice in the Description page of Project Settings.


#include "BortalGameMode.h"
#include "Bortal6Character.h"
#include "Bortal6PlayerController.h"

ABortalGameMode::ABortalGameMode()
	: Super(), _MatLerp(0.f), _GravMatLerp(0.f), _PopMatLerp(0.f), _PullMatLerp(0.f)
	, SpawnLocation(0), GravLaserEnergy(0), PushLaserEnergy(0), PopLaserEnergy(0)
	, PullLaserEnergy(0), bIsHoldingLaser(false)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

float ABortalGameMode::MatLerpIncrement(const float inc)
{
	if (_MatLerp + inc > 1.0f)	{ return 1.f; }
	_MatLerp += inc;
	return _MatLerp;
}

float ABortalGameMode::GravityMatLerpIncrement(float inc)
{
	if (_GravMatLerp + inc > 1.0f)  { return 1.f; }
	_GravMatLerp += inc;
	return _GravMatLerp;
}

float ABortalGameMode::PopMatLerpIncrement(float inc)
{
	if (_PopMatLerp + inc > 1.0f) { return 1.f; }
	_PopMatLerp += inc;
	return _PopMatLerp;
}

float ABortalGameMode::PullMatLerpIncrement(float inc)
{
	if (_PullMatLerp + inc > 1.0f) { return 1.f; }
	_PullMatLerp += inc;
	return _PullMatLerp;
}


void ABortalGameMode::BortalInit(ABortal6PlayerController* PlayerController)
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing SpawnLocation at x: %f, y: %f"), SpawnLocation.X, SpawnLocation.Y)
	SpawnLocation = PlayerController->GetSpawnLocation();
}


void ABortalGameMode::RespawnPlayer(ABortal6Character* Character, ABortal6PlayerController* Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Respawning at x: %f, y: %f"), SpawnLocation.X, SpawnLocation.Y)
	Character->SetActorLocation(SpawnLocation);
	Controller->RestartLevel();
}


void ABortalGameMode::RoundH(int32& num)
{
	if (num > 100)
	{
		num = 100;
	}
}


/*    Gives lasers ammo amount of energy, according to ammoType,
 *    will return the new changed energy amount  */
int32 ABortalGameMode::GiveLaserAmmo(FString ammoType, uint8 ammo)
{
	int32 returnEnergy = 0;
	
	if (ammoType == "Push")
	{
		PushLaserEnergy += ammo;
		RoundH(PushLaserEnergy);
		returnEnergy = PushLaserEnergy;
	}
	else if (ammoType == "Pop")
	{
		PopLaserEnergy += ammo;
		RoundH(PopLaserEnergy);
		returnEnergy = PopLaserEnergy;
	}
	else if (ammoType == "Gravity")
	{
		GravLaserEnergy += ammo;
		RoundH(GravLaserEnergy);
		returnEnergy = GravLaserEnergy;
	}
	else if (ammoType == "Pull")
	{
		PullLaserEnergy += ammo;
		RoundH(PullLaserEnergy);
		return returnEnergy = PullLaserEnergy;
	}

	return returnEnergy;
}


int32 ABortalGameMode::GravUseAmmo(uint8 usage)
{
	if (GravLaserEnergy - usage >= 0)
	{
		GravLaserEnergy -= usage;
	}
	else
	{
		GravLaserEnergy = 0;
	}

	return GravLaserEnergy;
}


int32 ABortalGameMode::PushUseAmmo(uint8 usage)
{
	if (PushLaserEnergy - usage >= 0)
	{
		PushLaserEnergy -= usage;
	}
	else
	{
		PushLaserEnergy = 0;
	}

	return PushLaserEnergy;
}


int32 ABortalGameMode::PullUseAmmo(uint8 usage)
{
	if (PullLaserEnergy - usage > 0)
	{
		PullLaserEnergy -= usage;
	}
	else
	{
		PullLaserEnergy = 0;
	}

	return PullLaserEnergy;
}


int32 ABortalGameMode::PopUseAmmo(uint8 usage)
{
	if (PopLaserEnergy - usage > 0)
	{
		PopLaserEnergy -= usage;
	}
	else
	{
		PopLaserEnergy = 0;
	}

	return PopLaserEnergy;
}
