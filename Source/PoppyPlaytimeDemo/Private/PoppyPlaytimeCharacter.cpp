// Fill out your copyright notice in the Description page of Project Settings.


#include "PoppyPlaytimeCharacter.h"

#include "..\Public\ContactPointInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CableComponent.h"

// Sets default values
APoppyPlaytimeCharacter::APoppyPlaytimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APoppyPlaytimeCharacter::BeginPlay()
{
	Super::BeginPlay();
	HandCurrentSpeed = HandMaxSpeed;
	HandMoveOverTime = HandMaxDistance/HandMaxSpeed;
}

// Called every frame
void APoppyPlaytimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APoppyPlaytimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FCollisionQueryParams APoppyPlaytimeCharacter::GetIgnoreCharacterParams() const
{
	FCollisionQueryParams Params;

	TArray<AActor*> CharacterChildren;
	GetAllChildActors(CharacterChildren);
	Params.AddIgnoredActors(CharacterChildren);
	Params.AddIgnoredActor(this);

	return Params;
}

void APoppyPlaytimeCharacter::BeginHandMove(USceneComponent* HandTransform,
	UPrimitiveComponent* Trigger, bool& OutHit, FVector& OutLocation, FRotator& OutRotation, float& OutTime,
	UPrimitiveComponent*& OutHitComponent)
{
	FVector EndLocation = (CameraComponent->GetForwardVector() * HandMaxDistance) + CameraComponent->GetComponentLocation();
	OutLocation = EndLocation;
	OutRotation = HandTransform->GetComponentRotation();
	OutTime = HandMoveOverTime;
	
	Trigger->SetGenerateOverlapEvents(true);
	HandTransform->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(SphereTraceRadius);
	FHitResult HitResult;
	OutHit = GetWorld()->SweepSingleByChannel(
					HitResult,
					CameraComponent->GetComponentLocation(),
					EndLocation,
					FQuat::Identity,
					ECC_Visibility,
					Shape, GetIgnoreCharacterParams());
	
	if(OutHit)
	{
		OutLocation = HitResult.ImpactPoint;
		OutTime = (OutLocation - HandTransform->GetComponentLocation()).Length() / HandCurrentSpeed;
		OutHitComponent = HitResult.GetComponent();
		
		IContactPointInterface* HasContactPoint = Cast<IContactPointInterface>(HitResult.GetActor());
		if(HasContactPoint != nullptr)
		{
			FRotator TempRotator;
			TEnumAsByte<ContactReaction> TempContactReaction;
			HasContactPoint->HasContactPoint(OutLocation, TempRotator,TempContactReaction);
		}
	}
}

/*void APoppyPlaytimeCharacter::ReturnHandMove(USceneComponent* HandTransform, USceneComponent* HandParent,
	UCableComponent* Cable, UPrimitiveComponent* Trigger)
{
	TArray<FVector> Locations;
	Cable->GetCableParticleLocations(Locations);
	for (FVector Location : Locations)
	{
		UKismetSystemLibrary::MoveComponentTo(HandTransform, Location, )
	}
	
}*/

