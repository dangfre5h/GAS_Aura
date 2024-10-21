// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//�ᱻ���Ƶ�������
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	//��ȡ���ֱ��ָ���Ŀ��
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//û����ײ�赲������
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	 * ���ֲ�ͬ�����
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

//��MappingContext,�������
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//�鿴Context�Ƿ����ã����false�������
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//������Ϸʱ��ֻ���ڱ��ػ����ϲ��б�����ң������п���Ϊ��
	if(Subsystem)
	{
		//�ж��mapping�ļ�ʱ�����ȼ�����Խ��Խ�ȼ���
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	

	//�Ƿ���ʾ���
	bShowMouseCursor = true;
	//�������
	DefaultMouseCursor = EMouseCursor::Default;
	//��겻��������
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

//��InputAction�Ͷ�Ӧ�����뺯��
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent(�������)��ֻ��EnhancedInputComponent����ΪUE Editor�е�Project Settings�µ�
	//Default Input Component ClassΪEnhancedInputComponent��Ҳ�����Զ��������
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//��ǿ�����InputAction�������߼�����
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

//�����߼�����
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//��ΪIA_Move�����Ƕ�ά
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//��ȡ��ǰ����
	const FRotator Rotation = GetControlRotation();
	//ֻ��ҪY�ķ���
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//��ȡ��һ�����X��Y����
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//��ȡ�������Ľ�ɫ
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}
