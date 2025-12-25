// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/InteractionPropComponent.h"


#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Prop/Actors/FirecrackerActor.h"
#include "Prop/Actors/FirecrackerScenePropActor.h"
#include "Prop/Actors/LightActor.h"
#include "Prop/Actors/ToggerActor.h"
#include "Prop/UMG/FirecrackerUserWidget.h"

// Sets default values for this component's properties
UInteractionPropComponent::UInteractionPropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInteractionPropComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterInstance = Cast<ACharacter>(GetOwner());
	ShowFirecrackerCount();
}


// Called every frame
void UInteractionPropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TracePropForword();
	TracePropBack();
	BindKeyDownEvent();
	TracePropToggleAndFirecracker();
}

void UInteractionPropComponent::TracePropForword()
{
	
	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CharacterInstance);
	FVector StartLocation = 
		CharacterInstance->GetActorLocation()+CharacterInstance->GetActorUpVector()*10;
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorForwardVector()*13.f+CharacterInstance->GetActorUpVector()*10;
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	
	for (FHitResult &HitResult : OutHits)
	{
		if (!HitResult.bBlockingHit) 
			return;
		ALightActor* Light = Cast<ALightActor>(HitResult.GetActor());
		if (Light)
		{
			FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			Light->ActionEvent(Location);
		}
	}
}

void UInteractionPropComponent::TracePropBack()
{
	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CharacterInstance);
	FVector StartLocation = 
		CharacterInstance->GetActorLocation()+CharacterInstance->GetActorUpVector()*10;
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorForwardVector()*-13.f+CharacterInstance->GetActorUpVector()*10;
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	
	for (FHitResult &HitResult : OutHits)
	{
		if (!HitResult.bBlockingHit) 
			return;
		ALightActor* Light = Cast<ALightActor>(HitResult.GetActor());
		if (Light)
		{
			FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			Light->ActionEvent(Location);
		}
	}
}

void UInteractionPropComponent::TracePropToggleAndFirecracker()
{
	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CharacterInstance);
	FVector StartLocation = 
		CharacterInstance->GetActorLocation();
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorUpVector()*-100.f;
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	
	for (FHitResult &HitResult : OutHits)
	{
		if (!HitResult.bBlockingHit) 
			return;
		
		AToggerActor* Togger = Cast<AToggerActor>(HitResult.GetActor());
		if (Togger)
		{
			Togger->ActionEvent();
		}
		AFirecrackerScenePropActor* Firecracker = Cast<AFirecrackerScenePropActor>(HitResult.GetActor());
		if (Firecracker)
		{
			FirecrackerCount ++ ;
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
			Firecracker->ActionEvent();
		}
	}
}





void UInteractionPropComponent::BindKeyDownEvent()
{
	APlayerController * PC =  Cast<APlayerController>(CharacterInstance->GetController());
	if (PC&&PC->WasInputKeyJustPressed(EKeys::D))
	{
		bPressD = true;
	}
	if (PC&&PC->WasInputKeyJustReleased(EKeys::D))
	{
		bPressD = false;
	}
	if (PC&&PC->WasInputKeyJustPressed(EKeys::A))
	{
		bPressA = true;
	}
	if (PC&&PC->WasInputKeyJustReleased(EKeys::A))
	{
		bPressA = false;
	}
	
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&bPressD)
	{
		if (FirecrackerCount == 0)
		{
			FirecrackerWidget->Play0Animation();
		}
		if (FirecrackerCount !=0)
		{
			FirecrackerCount--;
			AFirecrackerActor * Firecracker =  
			GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(30,0,0));
			Firecracker->ActionEvent(FRotator(30,0,0).Vector());
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
		}
		
	}
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&bPressA)
	{
		if (FirecrackerCount == 0)
		{
			FirecrackerWidget->Play0Animation();
		}
		if (FirecrackerCount > 0)
		{
			FirecrackerCount--;
			AFirecrackerActor * Firecracker =  
				GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(150,0,0));
			Firecracker->ActionEvent(FRotator(150,0,0).Vector());
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
		}
		
	}
}

void UInteractionPropComponent::ShowFirecrackerCount()
{

	UClass* Widget = LoadClass<UFirecrackerUserWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Prop/UMG/UI_Firecracker.UI_Firecracker_C'"));
	
	FirecrackerWidget = CreateWidget<UFirecrackerUserWidget>(Cast<APlayerController>(CharacterInstance->GetController()),Widget);
	FirecrackerWidget->AddToViewport();
}

