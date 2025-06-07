// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterData.generated.h"

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	Humanoid UMETA(DisplayName = "Humanoid"),
	NoneHumanoid   UMETA(DisplayName = "NoneHumanoid")
};

USTRUCT(BlueprintType)
struct FAttackTargetInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rank = 0;
};

USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
	FName MonsterName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
	EMonsterType MonsterType = EMonsterType::Humanoid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	float MaxHealth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	float BaseDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	float MaxSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	TArray<FAttackTargetInfo> TargetBones;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	FAttackTargetInfo LastBone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData")
	TObjectPtr<UStaticMesh> SlicingMesh = nullptr;

	/*----------------------------------------------------------------------------*/

	// 조건부 표시용
	UPROPERTY(EditAnywhere, Category = "MonsterData")
	bool bIsNoneHumanoid = false;

	// 하위 카테고리로 구분
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterData|NoneHumanoid Details", meta = (EditCondition = "bIsNoneHumanoid", EditConditionHides, DisplayName = "Max MP"))
	float MaxMP = 0.0f;
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
