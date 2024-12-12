// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataType/Enum/ELogType.h"
#include "DataType/Enum/EBranchType.h"
#include "DataType/Enum/EAuthorityBranch.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "InputActionValue.h"
#include "Base/EAbilitySystemComponent.h"
#include "UtilityLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "EUtility|Development", meta=(DefaultToSelf = "Object", DevelopmentOnly, AdvancedDisplay="Time, Object"))
	static void PrintLog(FString Text, ELogType logType, UObject* Object, float Time = 2.0f);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|String")
	static FString GetRandomAlphaDigit(int Length = 5);

	UFUNCTION(BlueprintCallable, Category = "EUtility|Flow", Meta = (ExpandEnumAsExecs = "Branches"))
	static void NBranch(bool Condition, TEnumAsByte<EBranchType>& Branches);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Array")
	static int32 GetLargestInteger(const TArray<int32>& TargetArray);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|String")
	static FName TextToName(const FText& Text);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Subsystem", meta = (WorldContext = "WorldContextObject"))
	static UGameInstanceSubsystem* GetGameInstanceSubsystemOfClass(const UObject* WorldContextObject, TSubclassOf<UGameInstanceSubsystem> SubsystemClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Gameplay Effect")
	static FGameplayEffectContextHandle GetContext(const FGameplayEffectSpec& InEffectSpec);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Gameplay Tags")
	static FGameplayTag MakeGameplayTagFromText(FText Text);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Input Action")
	static bool GetActionValueBool(const FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Input Action")
	static float GetActionValueFloat(const FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Input Action")
	static FVector GetActionValueVector(const FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication", meta = (DefaultToSelf = "Actor"))
	static bool HasEnhancedAbilitySystemComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication", meta = (DefaultToSelf = "Actor"))
	static UEAbilitySystemComponent* GetEnhancedAbilitySystemComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "EUtility|Replication")
	static AController* GetLocalController(APawn* Pawn, bool& Success);

	// my pawn has authority && my pawn have controller && my pawn controller is not local
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication")
	static bool IsThisMyPawnInServerWorld(APawn* Pawn);

	// my pawn has no authority && my pawn have controller && my pawn have local controller
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication")
	static bool IsThisMyPawnInMyWorld(APawn* Pawn);

	// server pawn has authority && server pawn have controller && server pawn is local
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication")
	static bool IsThisServerPawnInServerWorld(APawn* Pawn);

	// server pawn has no authority && server pawn have no controller
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication")
	static bool IsThisServerPawnInMyWorld(APawn* Pawn);


	UFUNCTION(BlueprintCallable, Category = "EUtility|Replication", Meta = (ExpandEnumAsExecs = "AuthorityVerify"))
	static void AuthorityVerifyGate(APawn* Pawn, TEnumAsByte<EAuthorityVerify>& AuthorityVerify);

	UFUNCTION(BlueprintCallable, Category = "EUtility|Replication", Meta = (ExpandEnumAsExecs = "AuthorityBranch"))
	static void AuthorityBranchGate(APawn* Pawn, TEnumAsByte<EAuthorityBranch>& AuthorityBranch);

};
