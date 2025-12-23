// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "MyCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class ANIMALWELL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PawnClientRestart() override;

#pragma region INPUT

	UPROPERTY(EditAnywhere, Category = "Controls|Input Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Controls|Input Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Controls|Input Actions")
	UInputAction* ClimbAction;

	UPROPERTY(EditAnywhere, Category = "Controls|Input Mapping")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Controls|Input Mapping")
	int32 InputMappingPriority = 0;

#pragma endregion INPUT

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Landed(const FHitResult& Hit) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnhanceMove(const FInputActionValue& Value);
	void EnhanceJump(const FInputActionValue& Value);
	void EnhanceClimb(const FInputActionValue& Value);

private:
	//纸娃娃组件
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Actor Component")
	class USpringArmComponent* SpringArmComponent;

	//相机组件视角跟随
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Actor Component")
	class UCameraComponent* CameraComponent;

	//场景组件
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Actor Component")
	USceneComponent* SceneComponent;

	//角色游戏组件
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Actor Component")
	class UCharacterGameComponent* CharacterGameComponent;
};
