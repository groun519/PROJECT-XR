// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTargetActor.h"

AAttackTargetActor::AAttackTargetActor()
{
 	PrimaryActorTick.bCanEverTick = true;

}
void AAttackTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttackTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackTargetActor::SetAttackTargetRank(AActor* TargetMonster, int32 rRank, float WeaponDamage)
{
	Monster = TargetMonster;
	AttackTargetRank = rRank;

	int32 lastDamageCoeff_1 = 1;
	int32 lastDamageCoeff_2 = 1;
	int32 preDamageCoeff	= 0;
	for (int i = 2; i < rRank+3; i++)
	{
		preDamageCoeff = lastDamageCoeff_1 + lastDamageCoeff_2;
		lastDamageCoeff_1 = lastDamageCoeff_2;
		lastDamageCoeff_2 = preDamageCoeff;

		//	//	//	//
		// 
		// Rank별 피해량은 피보나치 수열대로 이루어진다.
		// 
		// Rank 0 : 120%
		// Rank 1 : 130%
		// Rank 2 : 150%
		// Rank 3 : 180%
		// Rank 4 : 230%
		// Rank 5 : 310%
		// Rank 6 : 440%
		// 
		// 그러니 좋은 무기를 사용해야 한다!
		// 
		//	//	//	//
	}

	Damage = WeaponDamage * (1.f + static_cast<float>(preDamageCoeff) / 100.f);
}

