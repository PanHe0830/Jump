// 咖啡与香蕉

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class JUMP_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "ShowMesh")
	UStaticMeshComponent* SphereMesh; // 当前AActor的静态网格体

public:
	void SetActorMesh();

public:
	UPROPERTY(EditAnywhere, Category = "BoxType")
	TArray<UStaticMesh*> SpawnActorArray;
};
