// Fill out your copyright notice in the Description page of Project Settings.


#include "ABWeapon.h"


AABWeapon::AABWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));
	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}

	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

