// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataType/Enum/ELogType.h"
#include "DataType/Enum/EBranchType.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "InputActionValue.h"
#include "Component/ReplicatedAction.h"
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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication", meta = (DefaultToSelf = "Character"))
	static bool HasReplicatedActionComponent(ACharacter* Character);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EUtility|Replication", meta = (DefaultToSelf = "Character"))
	static UReplicatedAction* GetReplicatedActionComponent(ACharacter* Character);


};
