// Copyright Yang Yu


#include "Character/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	//�ý�ɫ��ת��ָ���������ƶ�����ʹ��RotationRate��Ϊ��ת����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//������ת���ʣ���Ϊֻ��ƫ����ת
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	//ֻ��ƽ���ƶ�
	GetCharacterMovement()->bConstrainToPlane = true;
	//ʹ��ɫ��ʼʱ�ܹ���׽��ƽ��
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//����������������ƽ������Rotation,���������ֻӰ�������
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;



}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// ΪServer��ʼ��Ability Actor
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// ΪClient��ʼ��Ability Actor
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState)
		UAbilitySystemComponent* ASC = AuraPlayerState->GetAbilitySystemComponent();
	ASC->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = ASC;
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//����HUD
	//������Ϸ�У�PlayerController����Ϊ�գ���Ϊ��client�У�ֻ���Լ���PlayerController��������ҵ�PlayerController�ǿյ�
	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	if (AuraPlayerController)
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD)//HUDֻ�ڱ�����Ч���п���Ϊ��
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

}
