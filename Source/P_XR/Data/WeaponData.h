// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/*
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Common		UMETA(DisplayName = "Common"),
	UnCommon	UMETA(DisplayName = "UnCommon"),
	Rare		UMETA(DisplayName = "Rare"),
	Epic		UMETA(DisplayName = "Epic"),
	Legendary	UMETA(DisplayName = "Legendary"),
	Unique		UMETA(DisplayName = "Unique")
};
*/

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	FName WeaponName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float TargetSpawnFrequency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int32 WeaponRank = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	FTransform WeaponOffset = FTransform();
};

/**
 * 
 */
UCLASS()
class P_XR_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	TArray<FWeaponInfo> WeaponData;
	
public:
	UFUNCTION(BlueprintCallable)
	FWeaponInfo FindWeaponForWeaponName(FName WeaponName);
	
};
