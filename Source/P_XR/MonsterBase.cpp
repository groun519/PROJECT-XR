// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComp->SetupAttachment(GetMesh(), FName("HandSocket"));
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	MonsterAIController = Cast<AMonsterAIController>(NewController);
	if (MonsterAIController && BehaviorTree)
	{
		MonsterAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		MonsterAIController->RunBehaviorTree(BehaviorTree);
	}
}

AActor* AMonsterBase::SpawnAttackTargetByRank(FVector SpawnLoc, FRotator SpawnRot, int32 AttackTargetRank, FName AttachSocketName)
{
	int32 rRank = AttackTargetRank;
	rRank = FMath::Clamp(rRank, 0, 6);

	if (AttackTargetClass && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AAttackTargetActor* SpawnedAttackTarget = GetWorld()
			->SpawnActor<AAttackTargetActor>(AttackTargetClass, SpawnLoc, SpawnRot, SpawnParams);

		if (SpawnedAttackTarget)
		{
			SpawnedAttackTarget->SetActorScale3D(FVector(0.2f));
			SpawnedAttackTarget->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, AttachSocketName);
			SpawnedAttackTarget->SetAttackTargetRank(this, rRank);
			SpawnedAttackTarget->Monster = this;

			AttackTargetList.Add(SpawnedAttackTarget);
			HavingTargetNum++;

			return SpawnedAttackTarget;
		}
	}
	return nullptr;
}

void AMonsterBase::SliceByBone(FName BoneName)
{
	if (!GetMesh()) return;

	// 1. 숨김 처리
	GetMesh()->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);

	// 2. 절단 위치
	const FVector BoneLocation = GetMesh()->GetBoneLocation(BoneName);
	const FRotator BoneRotation = GetMesh()->GetBoneQuaternion(BoneName).Rotator();

	// 3. 조각 메시 스폰 (위쪽 절단 파츠)
	if (SlicedPartActorClass && GetWorld())
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* UpperPart = GetWorld()->SpawnActor<AActor>(SlicedPartActorClass, BoneLocation, BoneRotation, Params);
		if (UpperPart)
		{
			UpperPart->SetActorScale3D(GetActorScale3D());

			// FVector AdjustedLoc = BoneLocation + GetActorForwardVector() * 10.f;
			// UpperPart->SetActorLocation(AdjustedLoc);
		}
	}
}

void AMonsterBase::SetMonsterData(float _BaseDamage, float _MaxHealth)
{
	BaseDamage = _BaseDamage;
	MaxHealth = _MaxHealth;
	Health = MaxHealth;
}

