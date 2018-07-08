// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Weapons/Gun.h"
#include "Components/InputComponent.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FPCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);


}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (!GunBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("no GunBlueprint found"))
			return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint); //no Transforms because it will be attached in a second
	if (!ensure(Gun))return;

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	//"GripPoint" is a socket in the skeleton

	Gun->AnimInstance = Mesh1P->GetAnimInstance();  //our gun animates the mesh


	
	//SetupPlayerInputComponent happens BEFORE BeginPlay in which we spawn the Gun.
	//So we move the fire binding from SetupPlayerInputComponent to here because we can now be sure that we already have a gun. 
	// Bind fire event
	if (InputComponent)  //we don't have an InputComponent if we are possessed by an AIController
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}

}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input    
//(If I am being possessed by a Player then connect my input component to the relevant bindings on this Character)
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMannequin::PullTrigger()
{
		Gun->OnFire();
}

