// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"

void AShootingGameModeBase::PrintScore()
{
	if (MainWidget != nullptr)
	{
		MainWidget->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass != nullptr)
	{
		// MainWidgetClass: BP_MainWidget_C
		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
		if (MainWidget != nullptr)
		{
			//언리얼 Widget의 특징
			// AddToViewport를 해야 화면에 출력을 해준다 너무나도 귀찮다 왜째서냐
			MainWidget->AddToViewport();
		}
	}
}

void AShootingGameModeBase::AddScore(int32 Point)
{
	CurrentScore += Point;
	UE_LOG(LogTemp, Warning, TEXT("Current Score: %d"), CurrentScore);
	PrintScore();
}
