// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Hoop.generated.h"


UCLASS()
class BORTAL6_API AHoop : public AActor
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent* Mesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	AHoop();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Hoop")
	void HoopInit(UStaticMeshComponent* _mesh);

	UFUNCTION(BlueprintCallable, Category = "Hoop")
	void HoopUp();

	UFUNCTION(BlueprintCallable, Category = "Hoop")
	void HoopDown();
	
};
