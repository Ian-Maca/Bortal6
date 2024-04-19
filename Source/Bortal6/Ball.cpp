// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeStatic
#include "Ball.h"
#include "LaserTypes.h"

// Sets default values
ABall::ABall()
	: _slowed(false), _pushCount(0), _popCount(0), _pullCount(0), Mesh(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _SegMesh(TEXT("/Game/Mine/Meshes/rope_segment"));

	if (_SegMesh.Succeeded())
	{
		SegMesh = _SegMesh.Object;

		FString SegName;
		
		SegMesh->GetName(SegName);
		UE_LOG(LogTemp, Warning, TEXT("SegMesh Success! -- %s"), *SegName)
	}
	
}


void ABall::BallInit(UStaticMeshComponent* _BallMesh)
{
	Mesh = _BallMesh;
	
	Mesh->AttachToComponent()
	
}

void ABall::Shot(const ELaserType LaserType, FVector Direction, UStaticMeshComponent* _Mesh)
{
	if (Mesh == nullptr) { return; } 
	
	CurrentDirection = Direction;
	UE_LOG(LogTemp, Warning, TEXT("ABall::Shot() -- Slowed: %d"), LaserType)
	switch (LaserType)
	 {
	    case  ELaserType::Push :
	 		if (_slowed)  {
	 			_pushCount++;
	 			PushDirections.Add(Direction);
	 			_Mesh->SetVectorParameterValueOnMaterials("EmissionHue", BLUE);
	 		}
		    else  {
			    Push(Mesh, Direction);
		    }
		break;
		case  ELaserType::Slow :
			Slow(Mesh);
			if(!_slowed)  {
				HandleUnslow();
			}
		break;
		case  ELaserType::Pop :
			if (_slowed)  {
				_popCount++;
				_Mesh->SetVectorParameterValueOnMaterials("EmissionHue", GREEN);
			}
			else  {
				Pop(Mesh);
			}
		break;
		case  ELaserType::Pull :
			if (_slowed)  {
				_pullCount++;
				PullDirections.Add(Direction);
				_Mesh->SetVectorParameterValueOnMaterials("EmissionHue", PINK);

			}
			else  {
				Pull(Mesh, Direction);
			}
		break;
	 }
}


auto ABall::Push(UStaticMeshComponent* _Mesh, const FVector& Direction) -> void
{
	UE_LOG(LogTemp, Warning, TEXT("Pushing in Direction: %f, %f, %f"), Direction.X, Direction.Y, Direction.Z)
	_Mesh->AddImpulse(Direction * FVector(1000.f, 1000.f, 1000.f), NAME_None, true);
}


bool ABall::Slow(UStaticMeshComponent* _Mesh)
{
	UE_LOG(LogTemp, Warning, TEXT("ABall::Slow"))
	if (_slowed)
	{
		_Mesh->SetLinearDamping(0.1f);
		_Mesh->SetAngularDamping(0.0f);
		_Mesh->SetVectorParameterValueOnMaterials("EmissionHue", BLACK);
		_slowed = false;
	}
	else
	{
		_Mesh->SetLinearDamping(50.0f);
		_Mesh->SetAngularDamping(30.0f);														
		_Mesh->SetVectorParameterValueOnMaterials("EmissionHue", RED);
		_slowed = true;
	}

	return _slowed;
}

auto ABall::Pop(UStaticMeshComponent* _Mesh, double Amount) -> void
{
	UE_LOG(LogTemp, Warning, TEXT("ABall::_Pop"))
	const FVector _direction = FVector(0.0f, 0.0f, Amount);
	
	_Mesh->AddImpulse(_direction, NAME_None, true);
}


auto ABall::Pull(UStaticMeshComponent* _Mesh, const FVector& Direction) -> void
{
	UE_LOG(LogTemp, Warning, TEXT("ABall::Pull"))
	_Mesh->AddImpulse(Direction * FVector(-1000.f, -1000.f, -1000.f), NAME_None, true);
}


void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

auto ABall::HandleUnslow() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("UNSLOWING, laser counts: %d, %d, %d"), _pushCount, _popCount, _pullCount)

	for (size_t i = 0; i < _popCount; i++)
	{
		Pop(Mesh, 1000.f);
	}

	for (const auto& Dir : PullDirections)
	{
		Pull(Mesh, Dir);
	}

	for (const auto& Dir : PushDirections)
	{
		Push(Mesh, Dir);
	}
	
	PushDirections.Empty();
	PullDirections.Empty();
	memset(&_pushCount, 0, sizeof(_pushCount) + sizeof(_popCount) + sizeof(_pullCount));
}
