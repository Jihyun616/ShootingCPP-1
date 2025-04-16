// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 오브젝트의 충돌을 담당하는 컴포넌트(기능)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

