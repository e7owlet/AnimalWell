
#include "GameGameMode.h"
#include "BloodHUD.h"

AGameGameMode::AGameGameMode()
{
    HUDClass = ABloodHUD::StaticClass();
}