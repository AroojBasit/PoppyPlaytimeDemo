// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PoppyPlaytimeCharacter.generated.h"

UCLASS()
class POPPYPLAYTIMEDEMO_API APoppyPlaytimeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Hand Movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands", meta = (AllowPrivateAccess = "true"))
	float HandMaxSpeed = 3000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands", meta = (AllowPrivateAccess = "true"))
	float HandCurrentSpeed = 3000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands", meta = (AllowPrivateAccess = "true"))
	float HandMaxDistance = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands", meta = (AllowPrivateAccess = "true"))
	float HandMoveOverTime = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands", meta = (AllowPrivateAccess = "true"))
	float SphereTraceRadius = 10;

public:
	// Sets default values for this character's properties
	APoppyPlaytimeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FCollisionQueryParams GetIgnoreCharacterParams() const;
	
	UFUNCTION(BlueprintCallable, Category="HandMovement")
	void BeginHandMove(
		USceneComponent* HandTransform,
		UPrimitiveComponent* Trigger, bool& OutHit,
		FVector& OutLocation, FRotator& OutRotation,
		float& OutTime, UPrimitiveComponent*& OutHitComponent);

	/*void ReturnHandMove(
		USceneComponent* HandTransform, USceneComponent* HandParent, class UCableComponent* Cable,
		UPrimitiveComponent* Trigger);*/
};
