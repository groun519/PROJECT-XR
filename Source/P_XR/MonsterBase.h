// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

USTRUCT(BlueprintType)
struct FAttackMontageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage = nullptr; // ! 포인터는 nullptr로 초기화

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = .0f; // ! 변수를 선언할 때는 웬만해서 초기화
};

UCLASS()
class P_XR_API AMonsterBase : public ACharacter
{
	GENERATED_BODY() // 병신

public:
	AMonsterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAttackMontageInfo> AttackMontages; // TArray가 언리얼에서 쓰는 배열 특화?, TMap은 언리얼에서 쓰는 자료구조 맵

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

protected:
	virtual void BeginPlay() override;

};
