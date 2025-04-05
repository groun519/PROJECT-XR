// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P_XR/Data/WeaponData.h"
#include "WeaponBase.generated.h"

UCLASS(BlueprintType)
class P_XR_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName WeaponName = FName();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TargetSpawnFrequency = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 WeaponRank = 0;

	UFUNCTION(BlueprintCallable)
	void SetWeaponData(float _Damage, float _TargetSpawnFrequency, int32 _WeaponRank);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWeaponData> WeaponData;
};
