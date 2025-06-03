// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh")); // BP_MonsterBase에 쓰기위해 썼다
	WeaponMeshComp->SetupAttachment(GetMesh(), FName("HandSocket")); // 웨폰을 손 소켓에 넣는다
}

AActor* AMonsterBase::SpawnAttackTargetByRank(FVector SpawnLoc, FRotator SpawnRot, int32 WeaponRank, float WeaponDamage, bool bIsBackAttack, FName AttachSocketName)
{
	int32 rRank = WeaponRank - MonsterRank;
	rRank = FMath::Max(0, rRank);
	rRank = FMath::Min(rRank, 5);

	if (bIsBackAttack)
	{
		rRank = 6;
	}

	if (AttackTargetClass && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AAttackTargetActor* SpawnedAttackTarget = GetWorld()
			->SpawnActor<AAttackTargetActor>(AttackTargetClass, SpawnLoc, SpawnRot, SpawnParams);

		if (SpawnedAttackTarget)
		{
			SpawnedAttackTarget->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
			SpawnedAttackTarget->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, AttachSocketName);
			SpawnedAttackTarget->SetAttackTargetRank(this, rRank, WeaponDamage);
			SpawnedAttackTarget->Monster = this;
			return SpawnedAttackTarget;
		}
	}
	return nullptr;
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
	MonsterAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MonsterAIController->RunBehaviorTree(BehaviorTree);
}

void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

