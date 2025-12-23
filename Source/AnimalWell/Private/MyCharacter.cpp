// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterGameComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values


AMyCharacter::AMyCharacter()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建组件并挂载到根组件（Capsule）上
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(RootComponent);

	CharacterGameComponent = CreateDefaultSubobject<UCharacterGameComponent>(TEXT("Character"));

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

	//增强输入绑定
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MoveAction) {
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::EnhanceMove);
		}

		if (ClimbAction) {
			PlayerEnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Triggered, this, &AMyCharacter::EnhanceClimb);
		}

		if (JumpAction) {
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::EnhanceJump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
	}
}

void AMyCharacter::EnhanceMove(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->MoveLeftRight(Value);
	}
}

void AMyCharacter::EnhanceJump(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		Super::Jump();
		CharacterGameComponent->Jump();
	}
}

void AMyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (CharacterGameComponent) {
		CharacterGameComponent->SetJumping(false);
	}
}

void AMyCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (APlayerController* LocalPlayer = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetLocalPlayer())) {
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, InputMappingPriority);
		}
	}
}

void AMyCharacter::EnhanceClimb(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->MoveUpAndDown(Value);
	}
}