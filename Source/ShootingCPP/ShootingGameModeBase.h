// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	int32 CurrentScore = 0;
	// class로 찍어낸 객체가 들어간다 (만들어진 붕어빵)
	class UMainWidget* MainWidget;

public:
	// UMainWidget 클래스와 UMainWidget을 상속받은 자식 클래스가 들어갈 수 있다
	// class 형식이 들어간다 (붕어빵 틀)
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetClass;

private:
	void PrintScore();

protected:
	virtual void BeginPlay() override;

public:
	void AddScore(int32 Point);
	
};
