// 咖啡与香蕉

/**
*	类作用:当前类完成删除NewBoxActor类生成形状,防止占用资源
*/


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeleteBoxActor.generated.h"

UCLASS()
class JUMP_API ADeleteBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeleteBoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
