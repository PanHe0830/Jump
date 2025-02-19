// 咖啡与香蕉


#include "NewBoxActor.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Jump/SpawnActor/SpawnActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ANewBoxActor::ANewBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANewBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 获得地图中Cube_Back的宽度

	AStaticMeshActor* BackStaticMeshActor = GetReferenceXYZ();
	
	FVector Location = GetActorLocation();
	FVector ActualExtent;
	DrawGenerateBox(BackStaticMeshActor , Location , ActualExtent);
	
	SetGenerateBoxTimer(ActualExtent);
}

// Called every frame
void ANewBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStaticMeshActor* ANewBoxActor::GetReferenceXYZ()
{
	for (TActorIterator<AStaticMeshActor> It(GetWorld()); It; ++It)
	{
		AStaticMeshActor* Actor = *It;
		if (Actor)
		{
			FString LocalActorLabel = Actor->GetActorLabel();
			FString LocalActorType = Actor->GetClass()->GetName();

			if (LocalActorLabel == "Cube_Back")
			{
				return Actor;
			}
			//UE_LOG(LogTemp, Warning, TEXT("Actor: %s, Type: %s"), *LocalActorLabel, *LocalActorType);
		}
	}

	return nullptr;
}

void ANewBoxActor::DrawGenerateBox(AStaticMeshActor* BackStaticMeshActor , FVector& Location, FVector& ActualExtent)
{
	if (BackStaticMeshActor)
	{
		FVector BoxExtent = BackStaticMeshActor->GetComponentsBoundingBox().GetExtent();

		UStaticMeshComponent* MeshComponent = BackStaticMeshActor->GetStaticMeshComponent();
		if (MeshComponent != nullptr)
		{
			FBoxSphereBounds Bounds = MeshComponent->GetStaticMesh()->GetBounds();
			FVector Center = Bounds.Origin; // 中心位置
			FVector Extent = Bounds.BoxExtent; // 半宽度、半深度、半高度
			//Extent.Z = 0;
			FVector Scale = BackStaticMeshActor->GetActorScale();
			Scale.Z = 0;
			ActualExtent = Extent * Scale; // 获得世界的大小

			//当前绘制的中心位置是这个类的蓝图放在的位置
			DrawDebugBox(GetWorld(), Location, ActualExtent, FQuat::Identity, FColor::Green, true, 0.0f, 0, 2.0f);
		}
	}
}

void ANewBoxActor::SetGenerateBoxTimer(FVector Extent)
{
	FActorSpawnParameters parama;
	parama.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UWorld* world = GetWorld();
	
	FRotator Rotator = FRotator(0, 0, 0);

	FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, world, Extent, Rotator, parama]()
		{
			FVector extent = Extent;
			extent.X = 0;
			FVector min = GetActorLocation() - extent;
			FVector max = GetActorLocation() + extent;
			FVector RandomLocation = GetRandomLocationInBox(min , max);
			UE_LOG(LogTemp, Warning, TEXT("RandomLocation %s"), *RandomLocation.ToString());
			CreateBox(world, RandomLocation, Rotator, parama);
		}
	);

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, TimerDel, 5.0f, true);
}

FVector ANewBoxActor::GetRandomLocationInBox(FVector Min, FVector Max)
{
	float RandX = FMath::RandRange(Min.X, Max.X);
	float RandY = FMath::RandRange(Min.Y, Max.Y);
	float RandZ = FMath::RandRange(Min.Z, Max.Z);

	return FVector(RandX , RandY , RandZ);
}

void ANewBoxActor::CreateBox(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation, struct FActorSpawnParameters SpawnParams, EBoxType Type)
{
	// 生成下落的方块
	if (ActorToSpawn && World)
	{
		ASpawnActor* SpawnActor = World->SpawnActor<ASpawnActor>(ActorToSpawn, SpawnLocation, SpawnRotation , SpawnParams);
		if (SpawnActor)
		{
			SpawnActor->SetActorMesh();
			UE_LOG(LogTemp, Warning, TEXT("successful spawn"));
		}
	}
}

