#include "WeaponBase.h"
#include "MonsterBase.h" // ✅ 몬스터 클래스 포함
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	TargetFinder = CreateDefaultSubobject<USphereComponent>(TEXT("TargetFinder"));
	TargetFinder->SetSphereRadius(1000.0f);
	TargetFinder->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ✅ 오버랩 이벤트 바인딩
	if (TargetFinder)
	{
		TargetFinder->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
	}
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::SetWeaponData(float _Damage, float _TargetSpawnFrequency, int32 _WeaponRank, UStaticMesh* _WeaponMesh, FTransform Offset)
{
	Damage = _Damage;
	TargetSpawnFrequency = _TargetSpawnFrequency;
	WeaponRank = _WeaponRank;

	if (WeaponMesh)
	{
		WeaponMesh->SetStaticMesh(_WeaponMesh);
		WeaponMesh->AddLocalOffset(Offset.GetLocation());
		WeaponMesh->SetRelativeRotation(Offset.GetRotation());
		WeaponMesh->SetWorldScale3D(Offset.GetScale3D());
	}
}

// ✅ 충돌 시 호출되는 절단 함수
void AWeaponBase::TrySliceTarget(AActor* TargetActor)
{
	AMonsterBase* Monster = Cast<AMonsterBase>(TargetActor);
	if (Monster && Monster->Health <= 0.f)
	{
		// 잘릴 Bone 이름은 상황에 맞게 조정 가능
		Monster->SliceByBone(FName("spine_03"));
	}
}

// ✅ 오버랩 이벤트 핸들러
void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	TrySliceTarget(OtherActor);
}
