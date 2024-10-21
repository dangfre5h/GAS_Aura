// Copyright Yang Yu

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * С�����Ļ���
 * С��������Ҫ����WidgetController����Controller�Ĺ㲥���з�Ӧ��
 * Controller����Ҫ֪���Լ��󶨵����ĸ�UserWidget
 *
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//��������WidgetController������ͼ�е���
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//�����Ӧ��WidgetController
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	//��������WidgetControllerʱ�������������������ͼ�����
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
