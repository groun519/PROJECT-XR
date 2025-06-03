// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//WeaponMesh->SetupAttachment(TargetFinder);
	RootComponent = WeaponMesh;

	TargetFinder = CreateDefaultSubobject<USphereComponent>(TEXT("TargetFinder"));
	TargetFinder->SetSphereRadius(1000.0f);
	TargetFinder->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::SetWeaponData(float _Damage, float _TargetSpawnFrequency, int32 _WeaponRank, UStaticMesh* _WeaponMesh, FTransform Offset)
{
	Damage = _Damage;
	TargetSpawnFrequency = _TargetSpawnFrequency;
	WeaponRank = _WeaponRank;

	if (WeaponMesh)
	{
		WeaponMesh->SetStaticMesh(_WeaponMesh);
		WeaponMesh->AddLocalOffset(Offset.GetLocation());
		WeaponMesh->SetRelativeRotation(Offset.GetRotation());
		WeaponMesh->SetWorldScale3D(Offset.GetScale3D());
	}
}

