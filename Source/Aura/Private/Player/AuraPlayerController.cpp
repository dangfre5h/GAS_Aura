// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	//会被复制到服务器
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//查看Context是否被设置，如果false，会崩溃
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	//有多个mapping文件时，优先级数字越大，越先加载
	Subsystem->AddMappingContext(AuraContext, 0);

	//是否显示鼠标
	bShowMouseCursor = true;
	//鼠标类型
	DefaultMouseCursor = EMouseCursor::Default;
	//鼠标不锁定窗口
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}
