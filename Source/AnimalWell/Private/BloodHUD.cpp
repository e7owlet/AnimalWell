#include "BloodHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"

ABloodHUD::ABloodHUD()
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> HeartTexObj(
        TEXT("/Script/Engine.Texture2D'/Game/Content/Assets/AnimalWell/Tools___Monsters/Heart/heart_sprite_1.heart_sprite_1'")
    );

    if (HeartTexObj.Succeeded())
    {
        HeartTexture = HeartTexObj.Object;
    }
}

void ABloodHUD::DrawHUD()
{
    Super::DrawHUD();
    if (!Canvas || !HeartTexture)
    {
        return;
    }

    const float ScreenW = Canvas->SizeX;
    const float ScreenH = Canvas->SizeY;

    // 总宽度，用来右对齐
    const float TotalWidth =
        HeartCount * HeartSize +
        (HeartCount - 1) * Spacing;

    // 右下角起点
    const float StartX = ScreenW - Margin.X - TotalWidth;
    const float Y = ScreenH - Margin.Y - HeartSize;

    for (int32 i = 0; i < HeartCount; ++i)
    {
        const float X = StartX + i * (HeartSize + Spacing);

        DrawTexture(
            HeartTexture,
            X, Y,
            HeartSize, HeartSize,
            0.f, 0.f, 1.f, 1.f,
            FLinearColor::White,
            BLEND_Translucent
        );
    }
}
