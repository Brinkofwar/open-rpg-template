// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EAbilitySystemComponent.h"
#include "GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h"

void UEAbilitySystemComponent::HandleAbilityInput(const FInputActionInstance& ActionInstance)
{

	FString id = UEnum::GetValueAsString(ActionInstance.GetTriggerEvent()) + ActionInstance.GetSourceAction()->GetName();

	FAbilityInputAction identifier{};
	identifier.InputAction = ActionInstance.GetSourceAction();
	identifier.InputTriggerEvent = ActionInstance.GetTriggerEvent();

	FAbilityInputContext* context = InputContexts.Find(FName(id));
	if (!context) {
		return;
	}
	
	int32& index = context->AbilityTagCurrent;
	TArray<FGameplayTagContainer>& tags = context->AbilityTags;

	if (index > context->AbilityTagLimit || !tags.IsValidIndex(index)) {
		index = 0;
	}

	if (this->TryActivateAbilitiesByTag(tags[index])) {
		context->AbilityTagCurrent++;
	}

}

void UEAbilitySystemComponent::CreateAbilityInput(TArray<FAbilityInputMapping> AbilityInputMappings)
{

	AActor* owner = GetOwner();
	if (!IsValid(owner) || !owner->InputComponent) {
		return;
	}
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(owner->InputComponent);

	for (int i = 0, len = AbilityInputMappings.Num(); i < len; i++) {

		FAbilityInputMapping mapping = AbilityInputMappings[i];
		FAbilityInputAction action = mapping.AbilityInputAction;

		FName id = FName(FString(UEnum::GetValueAsString(action.InputTriggerEvent) + action.InputAction->GetName()));

		if (InputBindingHandlers.Contains(id) || InputContexts.Contains(id)) {
			continue;
		}
		
		FAbilityInputContext inputHandle{};
		inputHandle.AbilityTagCurrent = 0;
		inputHandle.AbilityTagLimit = mapping.AbilityTags.Num() - 1;
		inputHandle.AbilityTags = mapping.AbilityTags;

		InputBindingHandlers.Add(id, &EnhancedInputComponent->BindAction(action.InputAction, action.InputTriggerEvent, this, &UEAbilitySystemComponent::HandleAbilityInput));
		InputContexts.Add(id, inputHandle);

	}

}

void UEAbilitySystemComponent::RemoveAbilityInput(TArray<FAbilityInputMapping> AbilityInputMappings)
{

	AActor* owner = GetOwner();
	if (!IsValid(owner) || !owner->InputComponent) {
		return;
	}
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(owner->InputComponent);

	for (int i = 0, len = AbilityInputMappings.Num(); i < len; i++) {

		FAbilityInputMapping mapping = AbilityInputMappings[i];
		FAbilityInputAction action = mapping.AbilityInputAction;

		FName id = FName(FString(UEnum::GetValueAsString(action.InputTriggerEvent) + action.InputAction->GetName()));

		if (!InputBindingHandlers.Contains(id) || !InputContexts.Contains(id)) {
			continue;
		}

		FInputBindingHandle** handle = InputBindingHandlers.Find(id);

		if (!handle) {
			continue;
		}

		EnhancedInputComponent->RemoveBinding(**handle);
		InputBindingHandlers.Remove(id);
		InputContexts.Remove(id);

	}

}

void UEAbilitySystemComponent::SAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	CAddLooseGameplayTags(Tags);
}
bool UEAbilitySystemComponent::SAddLooseGameplayTags_Validate(FGameplayTagContainer Tags)
{
	return Tags.IsValid();
}
void UEAbilitySystemComponent::CAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(this->GetOwnerActor(), Tags, true);
}


void UEAbilitySystemComponent::SRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	CRemoveLooseGameplayTags(Tags);
}
bool UEAbilitySystemComponent::SRemoveLooseGameplayTags_Validate(FGameplayTagContainer Tags)
{
	return Tags.IsValid();
}
void UEAbilitySystemComponent::CRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(this->GetOwnerActor(), Tags, true);
}


void UEAbilitySystemComponent::SSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload)
{
	CSendGameplayEvent(EventTag, Payload);
}
bool UEAbilitySystemComponent::SSendGameplayEvent_Validate(FGameplayTag EventTag, FGameplayEventData Payload)
{
	return EventTag.IsValid() && this->GetOwnerActor();
}
void UEAbilitySystemComponent::CSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this->GetOwnerActor(), EventTag, Payload);
}
