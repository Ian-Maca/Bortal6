// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserGun.h"

// Sets default values
ALaserGun::ALaserGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALaserGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

