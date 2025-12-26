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
	//绑定测试按钮
	UPROPERTY(EditAnywhere ,meta = (BindWidget))
	UButton *  TestButton;
public:
	//添加按钮点击事件
	UFUNCTION()
	void OnClickEvent();
	//添加构造脚本函数
	virtual void NativeConstruct() override;
	
};
