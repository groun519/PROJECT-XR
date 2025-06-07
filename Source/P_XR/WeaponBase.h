#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P_XR/Data/WeaponData.h"
#include "Components/SphereComponent.h"
#include "WeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FMonsterToAttackTargets
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Monster = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> AttackTargets;
};

UCLASS(BlueprintType)
class P_XR_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	FName WeaponName = FName();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponData")
	float Damage = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponData")
	float TargetSpawnFrequency = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponData")
	int32 WeaponRank = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponData")
	TObjectPtr<UWeaponData> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	TArray<FMonsterToAttackTargets> MonsterToAttackTargetsList;

	UFUNCTION(BlueprintCallable)
	void SetWeaponData(float _Damage, float _TargetSpawnFrequency, int32 _WeaponRank, UStaticMesh* _WeaponMesh, FTransform Offset);

	// ✅ [추가됨] 절단 대상에 충돌 시 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void TrySliceTarget(AActor* TargetActor);

	// ✅ [추가됨] 오버랩 이벤트 핸들러
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
