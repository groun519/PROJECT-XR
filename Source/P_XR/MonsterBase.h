// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AttackTargetActor.h"
#include "P_XR/Data/MonsterData.h"
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
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MonsterName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMonsterData> MonsterData;

	/** Monster Status **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MonsterRank = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;
	/** end Moster Status **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterWidth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterHeight_Head = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterHeight_Chest = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterHeight_Leg = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAttackTargetActor> AttackTargetClass;

	// 피해적용 함수를 위한 예?시
	UFUNCTION(BlueprintCallable)
	AActor* SpawnAttackTargetByRank(FVector SpawnLoc, FRotator SpawnRot, int32 WeaponRank, float WeaponDamage, bool bIsBackAttack, FName AttachSocketName);

protected:
	virtual void BeginPlay() override;

};
