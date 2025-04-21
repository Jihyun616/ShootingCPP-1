// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "ShootingGameModeBase.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	int32 DrawResult = FMath::RandRange(1, 100);

	if (DrawResult <= TraceRate)
	{
		// 플레이어 방향으로 바라보게 한다
		// APlayerPawn 타입의 액터만 반복 대상이 된다
		// GetWorld() 범위에 해당한다
		// GetWorld() 안에 있는 APlayerPawn 타입을 순차적으로 순회한다
		for (TActorIterator<APlayerPawn> Player(GetWorld()); Player; ++Player)
		{
			if (Player->GetName().Contains(TEXT("BP_PlayerPawn")))
			{
				Direction = Player->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
			}
		}

		if (Direction == FVector::ZeroVector)
			Direction = GetActorForwardVector();
	}
	else
	{
		Direction = GetActorForwardVector();
	}

	BoxComp->OnComponentBeginOverlap.AddDynamic
		(this, &AEnemyActor::OnEnemyOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);

	SetActorLocation(NewLocation);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

	if (Player != nullptr)
	{
		Player->Destroy();

		AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
		AShootingGameModeBase* ShootingGameMode =
			Cast<AShootingGameModeBase>(CurrentGameMode);
		if (ShootingGameMode != nullptr)
		{
			ShootingGameMode->ShowMenu();

			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ShootingGameMode is nullptr"));
		}
	}

	Destroy();
}

