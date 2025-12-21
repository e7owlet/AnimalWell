// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestPropUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class ANIMALWELL_API UTestPropUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere ,meta = (BindWidget))
	UButton *  TestButton;
public:
	
	UFUNCTION()
	void OnClickEvent();
	
	virtual void NativeConstruct() override;
	
};
