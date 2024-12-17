// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/EInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Library/UtilityLibrary.h"

bool UDataInputTask::Initialize(UEInputComponent* InputComponent, const UInputAction* InputAction, ETriggerEvent TriggerEvent)
{
	if (InputComponent) {
		InputBindingHandle = &InputComponent->BindAction(InputAction, TriggerEvent, this, &UDataInputTask::Handle);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "binded");
		return true;
	}
	return false;
}
void UDataInputTask::Handle(const FInputActionInstance& ActionInstance)
{
}
bool UDataInputTask::Remove(UEInputComponent* InputComponent)
{
	if (InputComponent && InputBindingHandle) {
		InputComponent->RemoveBinding(*InputBindingHandle);
		return true;
	}
	return false;
}

bool UDataInputAction::Initialize(UEInputComponent* InputComponent)
{

	for (int i = 0, ilen = InputTasks.Num(); i < ilen; i++) {

		UDataInputTask* task = InputTasks[i];
		if (!task) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "task init failed");
			continue;
		}

		if (task->Initialize(InputComponent, InputAction, InputTriggerEvent)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "task init success");
		}

	}

	return false;

}
bool UDataInputAction::Remove(UEInputComponent* InputComponent)
{

	for (int i = 0, ilen = InputTasks.Num(); i < ilen; i++) {

		UDataInputTask* task = InputTasks[i];
		if (!task) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "task remove failed");
			continue;
		}

		if (task->Remove(InputComponent)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "task remove success");
		}

	}

	return false;

}

void UDataInputTaskToggleTag::Handle(const FInputActionInstance& ActionInstance)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, this->GetOuter()->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "invalid parent");
}

bool UDataInputTaskCustom::Initialize(UEInputComponent* InputComponent, const UInputAction* InputAction, ETriggerEvent TriggerEvent)
{
	if (Super::Initialize(InputComponent, InputAction, TriggerEvent))
	{
		return OnInitialize(InputComponent, InputAction, TriggerEvent);
	}
	return false;
}
void UDataInputTaskCustom::Handle(const FInputActionInstance& ActionInstance)
{
	OnHandle(ActionInstance);
}

void UEInputComponent::RegisterDataInputActions(const TArray<UDataInputAction*> Actions)
{
	
	UUtilityLibrary::PrintLog("Action register started", ELogType::Warning, this, 5.0f);

	for (int i = 0, ilen = Actions.Num(); i < ilen; i++) {

		UDataInputAction* action = Actions[i];

		if (action) {

			if (action->Initialize(this)) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "full init");
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "init failed");
			}

		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "invalid action");
		}

	}

}
void UEInputComponent::UnregisterDataInputActions(const TArray<UDataInputAction*> Actions)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "start");

	for (int i = 0, ilen = Actions.Num(); i < ilen; i++) {

		UDataInputAction* action = Actions[i];

		if (action) {
			action->Remove(this);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "invalid action");
		}

	}

}
