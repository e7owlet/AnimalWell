#include "FallingStars.h"

#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "UObject/UObjectGlobals.h" // LoadObject

static UTexture2D* LoadStarTexture()
{
    return LoadObject<UTexture2D>(
        nullptr,
        TEXT("/Game/Content/Assets/AnimalWell/Tools___Monsters/Star/star.star")
    );
}

void FFallingStars::InitOnce(UCanvas* Canvas)
{
    if (bInited || !Canvas) return;

    ScreenW = Canvas->SizeX;
    ScreenH = Canvas->SizeY;

    StarTex = LoadStarTexture();
    if (!StarTex)
    {
        UE_LOG(LogTemp, Warning, TEXT("[FallingStars] Failed to load texture: /Game/.../Star/star.star"));
        return;
    }

    Stars.Reset();
    Stars.Reserve(AnchorCount * StarsPerAnchor);

    for (int32 a = 0; a < AnchorCount; ++a)
    {
        const float AnchorX = ScreenW * (a + 1) / (AnchorCount + 1);

        for (int32 i = 0; i < StarsPerAnchor; ++i)
        {
            FStar S;
            ResetStar(S, AnchorX, true);
            Stars.Add(S);
        }
    }

    bInited = true;
    UE_LOG(LogTemp, Warning, TEXT("[FallingStars] Initialized. anchors=%d, perAnchor=%d, total=%d"),
        AnchorCount, StarsPerAnchor, Stars.Num());
}

void FFallingStars::ResetStar(FStar& S, float AnchorX, bool bRandomY)
{
    // x在anchor附近抖动一点，让它看起来不是一条直线
    const float X = AnchorX + FMath::FRandRange(-24.f, 24.f);

    // y：初始化时随机分布到屏幕各处；重生时放到顶部外一点
    const float Y = bRandomY ? FMath::FRandRange(0.f, ScreenH) : (-StarSize.Y - FMath::FRandRange(0.f, 80.f));

    S.Pos = FVector2D(X, Y);
    S.Speed = FMath::FRandRange(35.f, 90.f);

    // 轻微左右漂移
    S.XJitter = FMath::FRandRange(-20.f, 20.f);
}

void FFallingStars::TickAndDraw(UCanvas* Canvas, float DeltaTime)
{
    if (!Canvas) return;
    if (!bInited) InitOnce(Canvas);
    if (!bInited || !StarTex) return;

    // 如果窗口尺寸变化（比如PIE调整），更新一下屏幕尺寸
    ScreenW = Canvas->SizeX;
    ScreenH = Canvas->SizeY;

    // 更新
    for (int32 idx = 0; idx < Stars.Num(); ++idx)
    {
        FStar& S = Stars[idx];

        S.Pos.Y += S.Speed * DeltaTime;
        S.Pos.X += S.XJitter * DeltaTime * 0.25f;

        if (S.Pos.Y > ScreenH + StarSize.Y)
        {
            // 计算它属于哪个anchor，回到对应列
            const int32 a = idx / StarsPerAnchor;
            const float AnchorX = ScreenW * (a + 1) / (AnchorCount + 1);
            ResetStar(S, AnchorX, false);
        }
    }

    // 绘制
    for (const FStar& S : Stars)
    {
        FCanvasTileItem Tile(S.Pos, StarTex->GetResource(), StarSize, FLinearColor::White);
        Tile.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(Tile);
    }
}
