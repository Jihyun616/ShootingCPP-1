// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// 전방 선언
	// 이 뒤에 타입이 클래스 타입이란 걸 알려줬기 때문에
	// 컴파일러는 class라고 인지하고 통과시켜준다.
	// 그래서 왜 전방 선언을 하느냐, 의존성이 끊어진다.
	// 의존성이 끊어진다는건 PlayerPawn 클래스와 UBoxComponent 클래스가
	// 관계가 없어진다라고 표현할 수 있다.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	// 메시 컴포넌트
	// 오브젝트에 그래픽 렌더링을 할 수 있게하는 기능
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_PlayerInput;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Horizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Vertical;

private:
	void OnInputHorizontal(const struct FInputActionValue& Value);
	void OnInputVertical(const struct FInputActionValue& Value);
};
