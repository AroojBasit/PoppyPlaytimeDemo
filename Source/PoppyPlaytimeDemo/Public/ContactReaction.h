// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ContactReaction.generated.h"

UENUM(BlueprintType)
enum ContactReaction
{
	InstantRetrieve		UMETA(DisplayName = "InstantRetrieve"),
	Delay				UMETA(DisplayName = "Delay"),
	Sticky				UMETA(DisplayName = "Sticky")
};
