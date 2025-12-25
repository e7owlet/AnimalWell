#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "VineActor.generated.h"

UCLASS()
class ANIMALWELL_API AVineActor : public ABasePropActor
{
	GENERATED_BODY()

public:
	AVineActor();

	//ºËÐÄÂß¼­¸´ÓÃ
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector) override;

	UFUNCTION()
	void StopFlut();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbookComponent* VineFlipbookComp;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UPaperFlipbook* VineSwayAnimation;
};