// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/InteractionPropComponent.h"

#include <filesystem>

#include "GameFramework/Character.h"
#include "Prop/Actors/BasePropActor.h"
#include "Prop/Actors/FirecrackerActor.h"
#include "Prop/Actors/LightActor.h"
#include "Prop/Actors/ToggerActor.h"

// Sets default values for this component's properties
UInteractionPropComponent::UInteractionPropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionPropComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterInstance = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UInteractionPropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TracePropForword();
	TracePropBack();
	BindKeyDownEvent();
	TracePropToggle();
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

void UInteractionPropComponent::TracePropToggle()
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
		
			//FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			Togger->ActionEvent();
		}
	}
}





void UInteractionPropComponent::BindKeyDownEvent()
{
	APlayerController * PC =  Cast<APlayerController>(CharacterInstance->GetController());
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&PC->WasInputKeyJustPressed(EKeys::D))
	{
		AFirecrackerActor * Firecracker =  
			GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(30,0,0));
		Firecracker->ActionEvent(FRotator(30,0,0).Vector());
	}
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&PC->WasInputKeyJustPressed(EKeys::A))
	{
		AFirecrackerActor * Firecracker =  
			GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(150,0,0));
		Firecracker->ActionEvent(FRotator(150,0,0).Vector());
	}
}

