// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGTemplate/Public/DataType/Enum/ELogType.h"
#include "UtilityLibrary.generated.h"


/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "EUtility", meta=(DefaultToSelf = "Object", DevelopmentOnly, AdvancedDisplay="Time, Object"))
	static void PrintLog(FString Text, ELogType logType, UObject* Object, float Time = 2.0f);

};
