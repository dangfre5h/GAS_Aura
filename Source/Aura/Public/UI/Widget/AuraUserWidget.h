// Copyright Yang Yu

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 小部件的基类
 * 小部件中需要保存WidgetController，对Controller的广播进行反应。
 * Controller不需要知道自己绑定的是哪个UserWidget
 *
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//用来设置WidgetController，在蓝图中调用
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//保存对应的WidgetController
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	//用于设置WidgetController时的其他补充操作，在蓝图中完成
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
