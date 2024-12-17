// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "EInputComponent.generated.h"


UCLASS(Blueprintable, Abstract, Const, DefaultToInstanced, EditInlineNew, CollapseCategories)
class RPGTEMPLATE_API UDataInputTask : public UObject {

	GENERATED_BODY()

public:

	virtual bool Initialize(UEInputComponent* InputComponent, const UInputAction* InputAction, ETriggerEvent TriggerEvent);
	virtual void Handle(const FInputActionInstance& ActionInstance);
	virtual bool Remove(UEInputComponent* InputComponent);

	bool isInitialized = false;

	FInputBindingHandle* InputBindingHandle;

};

UCLASS(Blueprintable)
class RPGTEMPLATE_API UDataInputTaskCustom : public UDataInputTask {

	GENERATED_BODY()

public:

	virtual bool Initialize(UEInputComponent* InputComponent, const UInputAction* InputAction, ETriggerEvent TriggerEvent) override;
	virtual void Handle(const FInputActionInstance& ActionInstance) override;

	UFUNCTION(BlueprintImplementableEvent)
	bool OnInitialize(UEInputComponent* InputComponent, const UInputAction* InputAction, ETriggerEvent TriggerEvent) const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHandle(const FInputActionInstance& ActionInstance) const;
};

UCLASS(Blueprintable)
class RPGTEMPLATE_API UDataInputTaskToggleTag : public UDataInputTask {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer Tags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool autoAdd = false;

	virtual void Handle(const FInputActionInstance& ActionInstance) override;

};

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, CollapseCategories)
class RPGTEMPLATE_API UDataInputAction : public UObject {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETriggerEvent InputTriggerEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta = (ShowOnlyInnerProperties))
	TArray<UDataInputTask*> InputTasks;

	bool Initialize(UEInputComponent* EDDInputComponent);
	bool Remove(UEInputComponent* InputComponent);

};


/**
 * 
 */
UCLASS(Config = Input, DisplayName = "Extended Input Component")
class RPGTEMPLATE_API UEInputComponent : public UEnhancedInputComponent
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Extended Input Component")
	virtual void RegisterDataInputActions(const TArray<UDataInputAction*> Actions);

	UFUNCTION(BlueprintCallable, Category = "Extended Input Component")
	virtual void UnregisterDataInputActions(const TArray<UDataInputAction*> Actions);

};
