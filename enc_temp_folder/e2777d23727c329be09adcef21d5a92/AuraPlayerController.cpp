// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	//会被复制到服务器
	bReplicates = true;
}

//绑定MappingContext,设置鼠标
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

//绑定InputAction和对应的输入函数
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent(基类变量)
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//增强输入绑定InputAction和输入逻辑函数
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

//输入逻辑函数
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//因为IA_Move输入是二维
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//获取当前方向
	const FRotator Rotation = GetControlRotation();
	//只需要Y的方向
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//获取归一化后的X、Y方向
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//获取被操作的角色
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}
