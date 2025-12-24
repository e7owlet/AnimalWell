// Fill out your copyright notice in the Description page of Project Settings.
#include "Prop/Actors/CandleActor.h" // Debug«∞÷√
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

ACandleActor::ACandleActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp0"));
	SpriteComp->SetupAttachment(RootComponent);
}

void ACandleActor::BeginPlay()
{
	Super::BeginPlay();
	UPaperSprite * Candle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/Mediavel_Sprite.Mediavel_Sprite'"));
	SpriteComp->SetSprite(Candle);
}

void ACandleActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	OpenFlag = true;
	UPaperSprite * CandleFire = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/MediavelFree_Sprite.MediavelFree_Sprite'"));
	SpriteComp->SetSprite(CandleFire);
}
