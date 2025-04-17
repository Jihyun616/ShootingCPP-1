// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "EnemyActor.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
	DelayTime = FMath::RandRange(1.0f, 3.0f);
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTime > DelayTime)
	{
		AEnemyActor* Enemy = GetWorld()->SpawnActor<AEnemyActor>(EnemyClass, GetActorLocation(), GetActorRotation());
		CurrentTime = 0;
	}
	else
	{
		CurrentTime += DeltaTime;
	}
}

