// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AttackTargetActor.h"
#include "P_XR/Data/MonsterData.h"
#include "MonsterBase.generated.h"

class UBehaviorTree;
class AMonsterAIController;

USTRUCT(BlueprintType)
struct FAttackMontageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage = nullptr; // ! 포인터는 nullptr로 초기화

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> Projectile = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageCoeff = .0f; // ! 변수를 선언할 때는 웬만해서x "꼭" 초기화

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooltime = .0f;
};

USTRUCT(BlueprintType)
struct FSkillMontageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> SkillMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> Projectile = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageCoeff = .0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CooldownCount = 0;
};

UCLASS()
class P_XR_API AMonsterBase : public ACharacter
{
	GENERATED_BODY() // 병신

public:
	AMonsterBase();

	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAttackMontageInfo> AttackMontages; // TArray가 언리얼에서 쓰는 배열 특화?, TMap은 언리얼에서 쓰는 자료구조 맵

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillMontageInfo> SkillMontages;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> WeaponMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MonsterName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMonsterData> MonsterData;

	/** Monster Status **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MonsterRank = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentDamage = 0.f;

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

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMonsterAIController> MonsterAIController;

};
