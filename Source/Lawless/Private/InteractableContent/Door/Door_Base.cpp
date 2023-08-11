// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableContent/Door/Door_Base.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/ShapeElem.h"

// Sets default values
ADoor_Base::ADoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*// SkeletalMesh
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	SkeletalMeshComp->SetupAttachment(RootComponent);
	// StaticMesh
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(SkeletalMeshComp);*/
	
	/*// Collision 
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(SkeletalMeshComp);*/

	

	
}

// Called when the game starts or when spawned
void ADoor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

