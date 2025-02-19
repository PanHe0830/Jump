// 咖啡与香蕉

/**
*	类作用:当前类完成随机生成形状,生成的形状应具备向某个方向的速度，类似于子弹可以运动
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jump/Enum/EBoxType.h"
#include "NewBoxActor.generated.h"

class ASpawnActor;

UCLASS()
class JUMP_API ANewBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANewBoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 获得生成区域的位置缩放的参考
	AStaticMeshActor* GetReferenceXYZ();

	// 绘制生成下落形状的区域
	void DrawGenerateBox(AStaticMeshActor* BackStaticMeshActor , FVector& Location, FVector& ActualExtent);

	// 设置一个持续生成Box的定时器
	void SetGenerateBoxTimer(FVector Extent);

	// 获得随机位置
	FVector GetRandomLocationInBox(FVector Min , FVector Max);

	//UFUNCTION()
	void CreateBox(UWorld* World , FVector SpawnLocation , FRotator SpawnRotation , struct FActorSpawnParameters SpawnParams , EBoxType Type = EBoxType::EDefault);

	UPROPERTY(VisibleAnywhere, Category = "BoxType")
	EBoxType BoxType = EBoxType::EDefault;

	UPROPERTY(EditAnywhere, Category = "BoxType")
	TSubclassOf<ASpawnActor> ActorToSpawn;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
};
