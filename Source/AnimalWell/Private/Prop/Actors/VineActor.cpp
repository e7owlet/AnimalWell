#include "Prop/Actors/VineActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"

AVineActor::AVineActor()
{
	VineFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("VineFlipbookComp"));

	//挂载到基类的碰撞盒上
	if (CollisionBox) {
		VineFlipbookComp->SetupAttachment(CollisionBox);
	}

	//基础设置
	VineFlipbookComp->SetComponentTickEnabled(true);
	VineFlipbookComp->bAutoActivate = false;
	VineFlipbookComp->Stop();
}

void AVineActor::BeginPlay()
{
	Super::BeginPlay();

	if (VineFlipbookComp)
	{
		VineFlipbookComp->Stop();
		VineFlipbookComp->SetPlaybackPositionInFrames(0, false);
	}
}

void AVineActor::ActionEvent(FVector BeginLoaction)
{
	//调试
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Vine Triggered!"));
	//触发藤蔓动画
	if (VineSwayAnimation && VineFlipbookComp) {
		VineFlipbookComp->Activate(true);
		VineFlipbookComp->SetFlipbook(VineSwayAnimation); 
		VineFlipbookComp->SetLooping(true);
		VineFlipbookComp->PlayFromStart();

		//0.5秒后停止
		FTimerHandle VineHandle;
		GetWorld()->GetTimerManager().SetTimer(VineHandle, this, &AVineActor::StopFlut, 0.5f, false);
	}
}

void AVineActor::StopFlut()
{
	if (VineFlipbookComp) {
		VineFlipbookComp->Stop();
		VineFlipbookComp->SetPlaybackPositionInFrames(0, false);
	}
}