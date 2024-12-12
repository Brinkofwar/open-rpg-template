// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ECharacter.h"
#include "Macro/EMacro.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AECharacter::AECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AECharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AECharacter, Arguments);
	DOREPLIFETIME(AECharacter, GameplayTags);
}

EARBITRARY_REPLICATION(AECharacter)
EARBITRARY_IMPLEMENTATION(AECharacter)
EGAMEPLAYTAG_REPLICATION(AECharacter)