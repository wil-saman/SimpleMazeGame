// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "EngineUtils.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create camera component
	Camera = CreateDefaultSubobject<UCameraComponent>("camera");
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	Camera->bUsePawnControlRotation = true;

	//Create mesh component
	MeshSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseCharacter"));
	MeshSkeleton->SetOnlyOwnerSee(true);
	MeshSkeleton->SetupAttachment(Camera);
	MeshSkeleton->bCastDynamicShadow = false;
	MeshSkeleton->CastShadow = false;

	//Declare trigger capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	//Declare overlap events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//for (TObjectIterator<ACountdown> Itr; Itr; ++Itr) 
	//{
	//	if (myCountdown->GetName().Equals(TEXT("Countdown1"))) 
	//	{
	//		Countdown = myCountdown;
	//		UE_LOG(LogTemp, Warning, TEXT("Found the countdown!"));
	//	}
	//}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ABaseCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABaseCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Countdown->CountdownHasFinished();
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, TEXT("CONGRATULATION! YOU WON!"));
	}
}

void ABaseCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		
	}
}

