// 咖啡与香蕉


#include "SpawnActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(SphereMesh);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnActor::SetActorMesh()
{
	int index = FMath::RandRange(0, SpawnActorArray.Num() - 1);
	UStaticMesh* StaticMesh = SpawnActorArray[index];
	if (StaticMesh && SphereMesh)
	{
		SphereMesh->SetStaticMesh(StaticMesh);
	}
}
