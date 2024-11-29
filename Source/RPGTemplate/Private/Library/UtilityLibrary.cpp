// Fill out your copyright notice in the Description page of Project Settings.
#include "Library/UtilityLibrary.h"
#include "DataType/Enum/ELogType.h"
#include "DataType/Enum/EBranchType.h"

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

FString UUtilityLibrary::GetRandomAlphaDigit(int Length)
{
	const char letters[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	const int lettersSize = 62;

	FString randomString;

	for (int i = 0; i < Length; i++) {
		randomString += letters[FMath::RandRange(0, lettersSize - 1)];
	}

	return randomString;

}

void UUtilityLibrary::NBranch(bool Condition, TEnumAsByte<EBranchType>& Branches)
{
	if(!Condition)
	{
		Branches = EBranchType::OnTrue;
	}
	else
	{
		Branches = EBranchType::OnFalse;
	}
}