// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 오브젝트의 충돌을 담당하는 컴포넌트(기능)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	BoxComp->SetGenerateOverlapEvents(true);

	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1);

	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	MeshComp->SetupAttachment(BoxComp);

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	FirePosition->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
		{
			SubSystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = FVector(0.0f, Horizontal, Vertical);

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComp != nullptr)
	{
		EnhancedInputComp->BindAction(IA_Horizontal, ETriggerEvent::Triggered,
			this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComp->BindAction(IA_Horizontal, ETriggerEvent::Completed,
			this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComp->BindAction(IA_Vertical, ETriggerEvent::Triggered,
			this, &APlayerPawn::OnInputVertical);
		EnhancedInputComp->BindAction(IA_Vertical, ETriggerEvent::Completed,
			this, &APlayerPawn::OnInputVertical);
		EnhancedInputComp->BindAction(IA_Fire, ETriggerEvent::Started,
			this, &APlayerPawn::Fire);
	}
}

void APlayerPawn::OnInputHorizontal(const FInputActionValue& Value)
{
	Horizontal = Value.Get<float>();
}

void APlayerPawn::OnInputVertical(const FInputActionValue& Value)
{
	Vertical = Value.Get<float>();
}

void APlayerPawn::Fire()
{
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletFactory, 
		FirePosition->GetComponentLocation(), 
		FirePosition->GetComponentRotation());

	
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

