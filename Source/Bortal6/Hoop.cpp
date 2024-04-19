// Fill out your copyright notice in the Description page of Project Settings.
#include "Hoop.h"

// Sets default values
AHoop::AHoop()
	: Mesh(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHoop::HoopInit(UStaticMeshComponent* _mesh)
{
	Mesh = _mesh;
}

void AHoop::HoopUp()
{
	Mesh->AddImpulse(FVector(0.f, 0.f, 20000.f), NAME_None, false);
	//UE_LOG(LogTemp, Warning, TEXT("Hoop.h WARNING -- HOOP UP!"))
}

void AHoop::HoopDown()
{
	Mesh->AddImpulse(FVector(0.f, 0.f, -20000.f), NAME_None, false);
	//UE_LOG(LogTemp, Warning, TEXT("Hoop.h WARNING -- HOOP DOWN!"))
}

// Called when the game starts or when spawned
void AHoop::BeginPlay()
{ 
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Hoop.h Spawned"))
}

// Called every frame
void AHoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
