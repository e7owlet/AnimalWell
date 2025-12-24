// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/ToggerActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Prop/Actors/DoorActor.h"

AToggerActor::AToggerActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp0"));
	SpriteComp->SetupAttachment(RootComponent);
	SpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

void AToggerActor::BeginPlay()
{
	Super::BeginPlay();

	UPaperSprite * CloseToggle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_ToggleClose.PS_ToggleClose'"));
	SpriteComp->SetSprite(CloseToggle);
}

void AToggerActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	OpenFlag = true;
	UPaperSprite * OpenToggle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_ToggleOpen.PS_ToggleOpen'"));
    SpriteComp->SetSprite(OpenToggle);
	Cast<ADoorActor>(GetOwner())->ActionEvent(BeginLoaction);
}
