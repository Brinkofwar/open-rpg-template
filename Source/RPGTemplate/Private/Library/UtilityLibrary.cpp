// Fill out your copyright notice in the Description page of Project Settings.
#include "Library/UtilityLibrary.h"
#include "DataType/Enum/ELogType.h"
#include "DataType/Enum/EBranchType.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h"

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

int32 UUtilityLibrary::GetLargestInteger(const TArray<int32>& TargetArray)
{
	int32 num = 0;

	for (int32 x : TargetArray)
	{
		if (x > num)
		{
			num = x;
		}
	}

	return num;
}

FName UUtilityLibrary::TextToName(const FText& Text)
{
	return FName(*Text.ToString());
}

UGameInstanceSubsystem* UUtilityLibrary::GetGameInstanceSubsystemOfClass(const UObject* WorldContextObject, TSubclassOf<UGameInstanceSubsystem> SubsystemClass)
{
	if (!WorldContextObject || !SubsystemClass)
	{
		return nullptr;
	}

	const UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance->GetSubsystemBase(SubsystemClass);

}

FGameplayEffectContextHandle UUtilityLibrary::GetContext(const FGameplayEffectSpec& InEffectSpec)
{
	return InEffectSpec.GetContext();
}

FGameplayTag UUtilityLibrary::MakeGameplayTagFromText(FText Text)
{
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(FName(*Text.ToString()));
	if (tag.IsValid()) {
		return tag;
	}
	return FGameplayTag();
}

float UUtilityLibrary::GetActionValueFloat(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<float>();
}

FVector UUtilityLibrary::GetActionValueVector(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<FVector>();
}

bool UUtilityLibrary::HasEnhancedAbilitySystemComponent(AActor* Actor)
{
	if (!Actor) {
		return false;
	}

	UAbilitySystemComponent* abilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!abilitySystem) {
		return false;
	}

	UEAbilitySystemComponent* eAbilitySystem = Cast<UEAbilitySystemComponent>(abilitySystem);
	if (!eAbilitySystem) {
		return false;
	}

	return true;
}

UEAbilitySystemComponent* UUtilityLibrary::GetEnhancedAbilitySystemComponent(AActor* Actor)
{
	if (!Actor) {
		return nullptr;
	}

	UAbilitySystemComponent* abilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!abilitySystem) {
		return nullptr;
	}

	UEAbilitySystemComponent* eAbilitySystem = Cast<UEAbilitySystemComponent>(abilitySystem);
	if (!eAbilitySystem) {
		return nullptr;
	}

	return eAbilitySystem;
}

AController* UUtilityLibrary::GetLocalController(APawn* Pawn, bool& Success)
{
	Success = false;

	if (!Pawn) {
		return nullptr;
	}

	AController* controller = Pawn->GetController();
	if (!controller) {
		return nullptr;
	}

	if (controller->IsLocalPlayerController()) {
		Success = true;
	}

	return controller;
}

bool UUtilityLibrary::GetActionValueBool(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<bool>();
}

bool UUtilityLibrary::IsThisMyPawnInServerWorld(APawn* Pawn)
{
	if (!Pawn) {
		return false;
	}

	AController* controller = Pawn->GetController();
	if (!controller) {
		return false;
	}

	return Pawn->HasAuthority() && controller && !controller->IsLocalPlayerController();
}

bool UUtilityLibrary::IsThisMyPawnInMyWorld(APawn* Pawn)
{
	if (!Pawn) {
		return false;
	}

	AController* controller = Pawn->GetController();
	if (!controller) {
		return false;
	}

	return !Pawn->HasAuthority() && controller && controller->IsLocalPlayerController();
}


bool UUtilityLibrary::IsThisServerPawnInServerWorld(APawn* Pawn)
{
	if (!Pawn) {
		return false;
	}

	AController* controller = Pawn->GetController();
	if (!controller) {
		return false;
	}

	return Pawn->HasAuthority() && controller && controller->IsLocalPlayerController();
}

bool UUtilityLibrary::IsThisServerPawnInMyWorld(APawn* Pawn)
{
	if (!Pawn) {
		return false;
	}

	return !Pawn->HasAuthority() && !Pawn->GetController();
}

void UUtilityLibrary::AuthorityVerifyGate(APawn* Pawn, TEnumAsByte<EAuthorityVerify>& AuthorityVerify)
{
	if (IsThisMyPawnInServerWorld(Pawn) || IsThisMyPawnInMyWorld(Pawn) || IsThisServerPawnInServerWorld(Pawn) || IsThisServerPawnInMyWorld(Pawn)) {
		AuthorityVerify = EAuthorityVerify::Valid;
	}
	else {
		AuthorityVerify = EAuthorityVerify::InValid;
	}
}

void UUtilityLibrary::AuthorityBranchGate(APawn* Pawn, TEnumAsByte<EAuthorityBranch>& AuthorityBranch)
{
	if (IsThisMyPawnInServerWorld(Pawn)) {
		AuthorityBranch = EAuthorityBranch::MyPawnInServerWorld;
	}
	else if (IsThisMyPawnInMyWorld(Pawn)) {
		AuthorityBranch = EAuthorityBranch::MyPawnInMyWorld;
	}
	else if (IsThisServerPawnInServerWorld(Pawn)) {
		AuthorityBranch = EAuthorityBranch::ServerPawnInServerWorld;
	}
	else if (IsThisServerPawnInMyWorld(Pawn)) {
		AuthorityBranch = EAuthorityBranch::ServerPawnInMyWorld;
	}
	else {
		AuthorityBranch = EAuthorityBranch::Undefined;
	}
}
