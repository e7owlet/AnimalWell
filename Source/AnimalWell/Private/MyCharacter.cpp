// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values


AMyCharacter::AMyCharacter()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建组件并挂载到根组件（Capsule）上
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MySprite"));
	MySprite->SetupAttachment(RootComponent);

	//只能在x、z轴上移动（梯子及其相关碰撞逻辑待商榷）
	GetCharacterMovement()->bConstrainToPlane = true; 
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f)); //锁定y轴

	GetCharacterMovement()->JumpZVelocity = 700.f;       //跳跃力度
	GetCharacterMovement()->AirControl = 0.35f;          //空中控制灵活性（二段跳）
	GetCharacterMovement()->GravityScale = 2.0f;         //增加重力感，下落快

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定跳跃动作
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		//移动向量应该是x轴
		//1.0f代表右，-1.0f 代表左
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
}



void AMyCharacter::StartJump()
{
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

