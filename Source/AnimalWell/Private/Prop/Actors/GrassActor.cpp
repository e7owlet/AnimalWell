// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/GrassActor.h"

#include "PaperSprite.h"
#include "Prop/Components/AnimalWellPaperSpriteComponent.h"

AGrassActor::AGrassActor()
{
	RootComponent  = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp0"));
	GrassSpriteComp = CreateDefaultSubobject<UAnimalWellPaperSpriteComponent>(TEXT("GrassSpriteComp0"));
	GrassSpriteComp->SetupAttachment(RootComponent);
}

void AGrassActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UPaperSprite* GrassSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Grass.PS_Grass'"));
	if (GrassSprite)
		GrassSpriteComp->SetSprite(GrassSprite);
}

void AGrassActor::ActionEvent(FVector BeginLoaction)
{
	GrassSpriteComp->SetScaleParameterValueOnMaterials(TEXT("FlutValue"),5);
	FTimerHandle GrassHandle;
	GetWorld()->GetTimerManager().SetTimer(GrassHandle,this,&AGrassActor::StopFlut,1.5f,false);
}

void AGrassActor::StopFlut()
{
	GrassSpriteComp->SetScaleParameterValueOnMaterials(TEXT("FlutValue"),0);
}
