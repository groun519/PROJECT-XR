// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackTargetActor.generated.h"

UCLASS()
class P_XR_API AAttackTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAttackTargetActor();

	virtual void Tick(float DeltaTime) override;

	void SetAttackTargetRank(AActor* TargetMonster, int32 rRank, float WeaponDamage);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Monster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AttackTargetRank = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = .0f;

protected:
	virtual void BeginPlay() override;

};
