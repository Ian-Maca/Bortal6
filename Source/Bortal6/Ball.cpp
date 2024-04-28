// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeStatic
#include "Ball.h"
#include "LaserGun.h"
#include "LaserTypes.h"

// Sets default values
ABall::ABall()
	: _slowed(false), _pushCount(0),
	  _popCount(0), _pullCount(0), RopeStart(nullptr), Mesh(nullptr), GunRef(nullptr)
{
	UE_LOG(LogTemp, Warning, TEXT("ABall() Constructed!"))

	static ConstructorHelpers::FObjectFinder<UStaticMesh> _SegMesh(TEXT("/Game/Mine/Meshes/rope_segment"));

	//SetFlags(RF_Transient);
	if (_SegMesh.Succeeded())
	{
		SegMesh = _SegMesh.Object;

		FString SegName;
		SegMesh->GetName(SegName);
	}
}

void ABall::BallInit(UStaticMeshComponent* _BallMesh, UStaticMeshComponent* _RopeStart)
{
	Mesh = _BallMesh;
	RopeStart = _RopeStart;

	/*if (const UWorld* World = GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("WORLD FOUND"))
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			if (ActorItr->GetClass()->IsChildOf(ALaserGun::StaticClass()))
			{
				GunRef = Cast<ALaserGun>(*ActorItr);

				FString result_text;
				GunRef->GetName(result_text);
				UE_LOG(LogTemp, Warning, TEXT("ACTOR FOUND ----- %s"), *result_text)
			}
		}
	}*/
	
	

}

void ABall::Shot(const ELaserType LaserType, const FVector Direction, UStaticMeshComponent* _Mesh)
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
	
	GunMuzzleLocation = GunRef->GetActorLocation();
}

auto ABall::HandleUnslow() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("UNSLOWING, laser counts: %d, %d, %d"), _pushCount, _popCount, _pullCount)

	for (size_t i = 0; i < _popCount; i++)
	{
		Pop(Mesh, 1000.f);
	}

	for (const FVector& Dir : PullDirections)
	{
		Pull(Mesh, Dir);
	}

	for (const FVector& Dir : PushDirections)
	{
		Push(Mesh, Dir);
	}
	
	PushDirections.Empty();
	PullDirections.Empty();
	memset(&_pushCount, 0, sizeof(_pushCount) + sizeof(_popCount) + sizeof(_pullCount));
}
