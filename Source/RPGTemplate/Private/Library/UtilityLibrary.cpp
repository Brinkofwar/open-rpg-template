// Fill out your copyright notice in the Description page of Project Settings.
#include "RPGTemplate/Public/Library/UtilityLibrary.h"
#include "RPGTemplate/Public/DataType/Enum/ELogType.h"

void UUtilityLibrary::PrintLog(FString Text, ELogType logType, UObject* Object, float Time)
{
	if (GEngine) {

		FString name = " ";
		if (IsValid(Object) && Object->GetClass()) {
			name = "[" + Object->GetClass()->GetName() + "] ";
		}

		FColor color = FColor::Blue;

		FString prefix;
		switch (logType) {
			case ELogType::Message:
				color = FColor::Blue;
				prefix = "[MESSAGE]";
				break;
			case ELogType::Warning:
				color = FColor::Yellow;
				prefix = "[WARNING]";
				break;
			case ELogType::Success:
				color = FColor::Green;
				prefix = "[SUCCESS]";
				break;
			case ELogType::Error:
				color = FColor::Red;
				prefix = "[ERROR]";
				break;
		}

		FString content = prefix + name + Text;

		GEngine->AddOnScreenDebugMessage(-1, Time, color, content);

	}
}
