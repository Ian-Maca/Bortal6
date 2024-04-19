// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// Ball colors
#define RED FVector(1, 0, 0)
#define BLACK FVector(0, 0, 0)
#define BLUE FVector(0, 0, 1)
#define GREEN FVector(0, 1, 0)
#define PINK FVector(1, 0.1, 0.4)

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class BORTAL6_API ABall : public AActor
{
	GENERATED_BODY()

private:
	TArray<FVector> PushDirections;
	TArray<FVector> PullDirections;
	
	FVector CurrentDirection;
	
	float IMP_MOD = 680.f;
	bool _slowed;
	int _pushCount, _popCount, _pullCount;
	
	UStaticMeshComponent* Mesh;
	UStaticMesh* SegMesh;
	
	FTimerHandle ImpulseTimerHandle;
	size_t _currentImpulseIndex = 0;
	float _impulseDelay = 0.1f;

	virtual void Tick(float DeltaTime) override;
	
	auto HandleUnslow() -> void;
	auto Push(UStaticMeshComponent* _Mesh, const FVector& Direction) -> void;
	auto Slow(UStaticMeshComponent* _Mesh) -> bool;
	auto Pop(UStaticMeshComponent* _Mesh, double Amount = 1000.f) -> void;
	auto Pull(UStaticMeshComponent* _Mesh, const FVector& Direction) -> void;
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UFUNCTION(BlueprintCallable, Category = "Balls")
	void BallInit(UStaticMeshComponent* _BallMesh); 
	
	UFUNCTION(BlueprintCallable, Category = "Balls")
	void Shot(const ELaserType LaserType, FVector Direction, UStaticMeshComponent* _Mesh);
};  
