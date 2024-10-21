// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//会被复制到服务器
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	//获取鼠标直线指向的目标
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//没有碰撞阻挡，返回
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	 * 几种不同的情况
	 * A. LastActor is null && ThisActor is null
	 *		- Do nothing.
	 * B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor.
	 * C. LastActor is valid && ThisActor is null
	 *		- Highlight LastActor.
	 * D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and highlight ThisActor
	 * E. Both actors are valid, but LastActor == ThisActor
	 *		- Do nothing.
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// Case A, both are null - do nothing
		}
		else
		{
			// Case B
			ThisActor->HighlightActor();
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E, do nothing
			}
		}
	}

}

//绑定MappingContext,设置鼠标
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//查看Context是否被设置，如果false，会崩溃
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//多人游戏时，只有在本地机器上才有本地玩家，所以有可能为空
	if(Subsystem)
	{
		//有多个mapping文件时，优先级数字越大，越先加载
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	

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

	//InputComponent(基类变量)，只想EnhancedInputComponent，因为UE Editor中的Project Settings下的
	//Default Input Component Class为EnhancedInputComponent，也可以自定义成其他
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
