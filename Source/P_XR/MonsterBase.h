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
	TObjectPtr<UAnimMontage > AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

};

UCLASS()
class P_XR_API AMonsterBase : public ACharacter
{
	GENERATED_BODY() // 병신


public:
	// Sets default values for this character's properties
	AMonsterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FAttackMontageInfo> AttackMontages; // TArray가 언리얼에서 쓰는 배열 특화?, TMap은 언리얼에서 쓰는 자료구조 맵

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
