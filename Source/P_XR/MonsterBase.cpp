// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh")); // BP_MonsterBase에 쓰기위해 썼다
	WeaponMesh->SetupAttachment(GetMesh(), FName("HandSocket")); // 웨폰을 손 소켓에 넣는다
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

