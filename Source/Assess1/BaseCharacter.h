// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Countdown.h"
#include "Components/CapsuleComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ASSESS1_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Finish Line")
	class UCapsuleComponent* TriggerCapsule;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	//UPROPERTY()
	//	ACountdown* Countdown;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Val);
	void MoveRight(float Val);

	//1st person view
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* MeshSkeleton;

	//Spring arm component to hold the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	//Camera view
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
