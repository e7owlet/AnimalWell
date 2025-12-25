// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionPropComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMALWELL_API UInteractionPropComponent : public USceneComponent
{
	GENERATED_BODY()

	class ACharacter* CharacterInstance;
	int32 FirecrackerCount = 0;
	bool bPressA;
	bool bPressD;
	
public:	
	// Sets default values for this component's properties
	UInteractionPropComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere)
	class UFirecrackerUserWidget *FirecrackerWidget;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TracePropForword();
	void TracePropBack();
	void TracePropToggleAndFirecracker();

	void BindKeyDownEvent();

	void  ShowFirecrackerCount();
	
};
