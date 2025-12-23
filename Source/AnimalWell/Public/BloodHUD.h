#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture2D.h"
#include "BloodHUD.generated.h"


UCLASS()
class ANIMALWELL_API ABloodHUD : public AHUD
{
	GENERATED_BODY()

public:
    ABloodHUD();
    virtual void DrawHUD() override;

protected:
    UPROPERTY()
    TObjectPtr<class UTexture2D> HeartTexture;

    UPROPERTY(EditAnywhere, Category = "UI")
    int32 HeartCount = 4;

    UPROPERTY(EditAnywhere, Category = "UI")
    float HeartSize = 48.f;

    UPROPERTY(EditAnywhere, Category = "UI")
    float Spacing = 6.f;

    UPROPERTY(EditAnywhere, Category = "UI")
    FVector2D Margin = FVector2D(30.f, 30.f);

};

