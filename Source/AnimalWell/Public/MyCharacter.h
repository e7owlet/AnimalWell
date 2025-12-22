// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

#pragma region INPUT
#pragma endregion INPUT

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
