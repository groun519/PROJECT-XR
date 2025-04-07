// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterData.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
	FName MonsterName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	float MaxHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	float MaxSpeed = 0.0f;
};

/**
 * 
 */
UCLASS()
class P_XR_API UMonsterData : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "MonsterData")
	TArray<FMonsterInfo> MonsterData;

public:
	UFUNCTION(BlueprintCallable)
	FMonsterInfo FindMonsterDataForMonsterDataName(FName MonsterName);
};
