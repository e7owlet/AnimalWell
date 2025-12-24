#pragma once
#include "CoreMinimal.h"

class UTexture2D;
class UCanvas;
class FFallingStars
{
public:
    FFallingStars() = default;

    // Ã¿Ö¡µ÷ÓÃ
    void TickAndDraw(UCanvas* Canvas, float DeltaTime);

    void SetAnchorCount(int32 InCount) { AnchorCount = FMath::Clamp(InCount, 1, 8); }
    void SetStarsPerAnchor(int32 InCount) { StarsPerAnchor = FMath::Clamp(InCount, 1, 30); }

private:
    struct FStar
    {
        FVector2D Pos;     // ÆÁÄ»×ø±ê
        float Speed = 60.f; // px/s
        float XJitter = 5.f; // ÇáÎ¢×óÓÒÆ¯ÒÆ
    };

private:
    bool bInited = false;

    UTexture2D* StarTex = nullptr;

    TArray<FStar> Stars;

    int32 AnchorCount = 5;        // 5´¦
    int32 StarsPerAnchor = 4;     // Ã¿´¦4¿Å
    FVector2D StarSize = FVector2D(16.f, 16.f); // ³ß´ç

    float ScreenW = 0.f;
    float ScreenH = 0.f;

private:
    void InitOnce(UCanvas* Canvas);
    void ResetStar(FStar& S, float AnchorX, bool bRandomY);
};
