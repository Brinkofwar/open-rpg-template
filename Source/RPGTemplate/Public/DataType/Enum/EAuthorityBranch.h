// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAuthorityBranch.generated.h"

UENUM(BlueprintType)
enum EAuthorityBranch {
	MyPawnInServerWorld UMETA(DisplayName = "MyPawnInServerWorld"),
	MyPawnInMyWorld UMETA(DisplayName = "MyPawnInMyWorld"),
	ServerPawnInServerWorld UMETA(DisplayName = "ServerPawnInServerWorld"),
	ServerPawnInMyWorld UMETA(DisplayName = "ServerPawnInMyWorld"),
	Undefined UMETA(DisplayName = "Undefined")
};

UENUM(BlueprintType)
enum EAuthorityVerify {
	Valid UMETA(DisplayName = "Valid"),
	InValid UMETA(DisplayName = "InValid")
};