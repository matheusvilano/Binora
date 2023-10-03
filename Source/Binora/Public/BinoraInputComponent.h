// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include <functional>

#include "Components/InputComponent.h"

#include "BinoraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class BINORA_API UBinoraInputComponent : public UInputComponent
{
	GENERATED_BODY()
	
	public:

		template<class UserClass>
		FInputActionBinding& BindAction( const FName ActionName, const EInputEvent KeyEvent, UserClass* Object, std::function<void(void)> Function)
		{
			FInputActionBinding InputActionBinding(ActionName, KeyEvent);
			InputActionBinding.ActionDelegate.GetDelegateForManualSet().BindLambda(Function);
			
			return this->UInputComponent::AddActionBinding(InputActionBinding);
		};
};
