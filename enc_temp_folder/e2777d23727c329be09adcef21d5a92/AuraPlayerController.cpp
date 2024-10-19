// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	//�ᱻ���Ƶ�������
	bReplicates = true;
}

//��MappingContext,�������
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//�鿴Context�Ƿ����ã����false�������
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	//�ж��mapping�ļ�ʱ�����ȼ�����Խ��Խ�ȼ���
	Subsystem->AddMappingContext(AuraContext, 0);

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

	//InputComponent(�������)
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
