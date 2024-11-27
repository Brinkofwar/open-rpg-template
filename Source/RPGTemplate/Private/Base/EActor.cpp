// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EActor.h"

// Sets default values
AEActor::AEActor()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEActor::BeginPlay()
{
	
	Super::BeginPlay();
	
}

// Called every frame
void AEActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

