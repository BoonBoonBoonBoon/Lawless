// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponContent/Base_RangedWeapon.h"

// Sets default values
ABase_RangedWeapon::ABase_RangedWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_RangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_RangedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

