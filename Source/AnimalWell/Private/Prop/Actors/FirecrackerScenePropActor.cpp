// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/FirecrackerScenePropActor.h"

#include "PaperSpriteComponent.h"

AFirecrackerScenePropActor::AFirecrackerScenePropActor()
{
	//根组件、渲染组件初始化
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FirecrackerSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("FirecrackerSpriteComp");
	FirecrackerSpriteComp->SetupAttachment(this->RootComponent);
	FirecrackerSpriteComp->SetRelativeScale3D(FVector(0.12f));
	FirecrackerSpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

void AFirecrackerScenePropActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	Destroy();
}
void AFirecrackerScenePropActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!FirecrackerSprite)
	{
		FirecrackerSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Cracker.PS_Cracker'"));
	}
	if (FirecrackerSprite)
	{
		FirecrackerSpriteComp->SetSprite(FirecrackerSprite);
	}
}