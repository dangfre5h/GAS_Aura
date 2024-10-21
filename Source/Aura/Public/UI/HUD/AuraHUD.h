// Copyright Yang Yu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;

/**
 * ����HUD����ʾOverlay
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

protected:

	virtual void BeginPlay() override;

private:
	//��������WBP_Overlay
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
};
