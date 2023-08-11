// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door_Base.generated.h"

UCLASS()
class LAWLESS_API ADoor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor_Base();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalMesh)
		USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)
	class UStaticMeshComponent* StaticMeshComp;*/
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* SphereCollision;*/
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
