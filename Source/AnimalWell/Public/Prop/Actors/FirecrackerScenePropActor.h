// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "FirecrackerScenePropActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AFirecrackerScenePropActor : public ABasePropActor
{
	GENERATED_BODY()
	public:
	AFirecrackerScenePropActor();
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* FirecrackerSpriteComp;
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	virtual  void OnConstruction(const FTransform& Transform);
	UPROPERTY(EditAnywhere)
	class UPaperSprite* FirecrackerSprite;
};
