// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "GrassActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AGrassActor : public ABasePropActor
{
	GENERATED_BODY()
	class UAnimalWellPaperSpriteComponent* GrassSpriteComp;
	

public:
	AGrassActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector) override;
	UFUNCTION()
	void StopFlut();
};
