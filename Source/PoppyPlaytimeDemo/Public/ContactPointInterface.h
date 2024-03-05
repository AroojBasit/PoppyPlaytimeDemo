// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ContactReaction.h"
#include "ContactPointInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UContactPointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POPPYPLAYTIMEDEMO_API IContactPointInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ContactPoint")
	void HasContactPoint(FVector& Location, FRotator& Rotation, TEnumAsByte<ContactReaction>& Sticky);
};
