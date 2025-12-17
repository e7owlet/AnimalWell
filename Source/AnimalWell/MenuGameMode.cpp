// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuHUD.h"
#include "MenuPlayerController.h"

AMenuGameMode::AMenuGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = APlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}
