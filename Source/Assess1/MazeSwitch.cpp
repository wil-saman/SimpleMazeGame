// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeSwitch.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"


// Sets default values
AMazeSwitch::AMazeSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;

	MazeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MazeMesh->SetupAttachment(RootComponent);

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMazeSwitch::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMazeSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);

}

void AMazeSwitch::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();
	}
}

