// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirecrackerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API UFirecrackerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	class UTextBlock * CrackerCount;

	UPROPERTY(EditAnywhere,meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation * ImageAnim;

	void SetCrackerCount(int32 CrackerCount);

	void Play0Animation();
};
	