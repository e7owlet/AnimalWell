// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestPropHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ATestPropHUD : public AHUD
{
	GENERATED_BODY()
	UPROPERTY()
	class UTestPropUserWidget* TPWidget;
public:
	virtual void BeginPlay() override;

	void ShowTestPropWidget();
};
