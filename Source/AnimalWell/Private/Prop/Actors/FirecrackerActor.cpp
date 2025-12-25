// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/FirecrackerActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Particles/ParticleSystem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleEmitter.h"
#include "Prop/Actors/GhostActor.h"

// Sets default values
AFirecrackerActor::AFirecrackerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//根组件、渲染组件初始化
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FirecrackerSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("FirecrackerSpriteComp");
	FirecrackerSpriteComp->SetupAttachment(this->RootComponent);
	FirecrackerSpriteComp->SetRelativeScale3D(FVector(0.2f));
	FirecrackerSpriteComp->SetCollisionProfileName(TEXT("NoCollision"));

	//碰撞检测初始化、碰撞预设
	FirecrackerCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("FirecrackerCollisionComponent");
	FirecrackerCollisionComponent->SetupAttachment(this->FirecrackerSpriteComp);
	FirecrackerCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//胶囊体尺寸（可以自己调）
	FirecrackerCollisionComponent->SetCapsuleRadius(32.f);
	FirecrackerCollisionComponent->SetCapsuleHalfHeight(64.f);
	FirecrackerCollisionComponent->bHiddenInGame = true;

	//空中翻转组件初始化，抛出时激活
	MyRotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
	MyRotatingMovementComp->RotationRate = FRotator(500.f,0,0);
	MyRotatingMovementComp->bAutoActivate = false;

	//抛物线运动组件初始化,抛出时激活
	MyProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MyProjectileMovementComp->InitialSpeed = 500.f;
	MyProjectileMovementComp->MaxSpeed = 500.f;
	MyProjectileMovementComp->ProjectileGravityScale = 1.f;
	MyProjectileMovementComp->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AFirecrackerActor::BeginPlay()
{
	Super::BeginPlay();

}

//爆炸销毁
void AFirecrackerActor::DestroyFirecracker()
{
	MyRotatingMovementComp->Deactivate();
	MyProjectileMovementComp->Deactivate();
	UParticleSystem * Boom = LoadObject<UParticleSystem>(this,TEXT("/Script/Engine.ParticleSystem'/Game/Prop/Particles/PS_Explosion_Air_Big_03.PS_Explosion_Air_Big_03'"));
	UGameplayStatics::SpawnEmitterAtLocation(this,Boom,GetActorLocation());
	
	AGhostActor* Ghost = Cast<AGhostActor>( UGameplayStatics::GetActorOfClass(this,AGhostActor::StaticClass()));
	if (Ghost&&(GetActorLocation() - Ghost->GetActorLocation()).Length() < 150.f)
	{
		Ghost->Destroy();
	}
	Destroy();
}	

// Called every frame
void AFirecrackerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFirecrackerActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!FirecrackerSprite)
	{
		FirecrackerSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Cracker.PS_Cracker'"));
	}
	if (FirecrackerSprite)
	{
		FirecrackerSpriteComp->SetSprite(FirecrackerSprite);
	}
}


void AFirecrackerActor::ActionEvent(FVector BeginLoaction)
{
	SetActorRotation(BeginLoaction.Rotation());
	

	MyRotatingMovementComp->Activate();
	
	MyProjectileMovementComp->Activate();

	GetWorld()->GetTimerManager().SetTimer(CrackerHandle,this,&AFirecrackerActor::DestroyFirecracker,0.5f,false);
	
}

