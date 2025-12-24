// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/DoorActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Prop/Actors/ToggerActor.h"

ADoorActor::ADoorActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp0"));
	DoorSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DoorSpriteComp0"));
	DoorSpriteComp->SetupAttachment(RootComponent);
	DoorSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	TA1 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta1Vector,FRotator(0));
	TA1->SetOwner(this);
	TA2 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta2Vector,FRotator(0));
	TA2->SetOwner(this);
	TA3 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta3Vector,FRotator(0));
	TA3->SetOwner(this);
	DoorSpriteComp->SetSprite(LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_DoorClose.PS_DoorClose'")));
}
void ADoorActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	
	if (TA1->GetOpenFlag() && TA2->GetOpenFlag() && TA3->GetOpenFlag())
	{
		DoorSpriteComp->SetSprite(LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Open.PS_Open'")));
		DoorSpriteComp->SetCollisionProfileName(TEXT("NoCollision"));
	}
	
	
}

