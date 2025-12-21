// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/UMG/TestPropUserWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Prop/Actors/BasePropActor.h"

void UTestPropUserWidget::OnClickEvent()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this,ABasePropActor::StaticClass(),OutActors);
	for (AActor* Actor : OutActors)
	{
		Cast<ABasePropActor>(Actor)->ActionEvent();
	}
}

void UTestPropUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TestButton->OnClicked.AddDynamic(this, &UTestPropUserWidget::OnClickEvent);
}
