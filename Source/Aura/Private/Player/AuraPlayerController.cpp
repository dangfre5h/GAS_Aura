// Copyright Yang Yu


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	//�ᱻ���Ƶ�������
	bReplicates = true;
}

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
