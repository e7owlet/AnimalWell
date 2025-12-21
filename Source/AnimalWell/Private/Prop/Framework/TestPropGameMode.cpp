// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Framework/TestPropGameMode.h"

#include "Prop/Framework/TestPropHUD.h"
#include "Prop/Framework/TestPropPlayerController.h"

ATestPropGameMode::ATestPropGameMode()
{
	PlayerControllerClass = ATestPropPlayerController::StaticClass();
	HUDClass = ATestPropHUD::StaticClass();
}
