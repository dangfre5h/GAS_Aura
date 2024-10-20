// Copyright Yang Yu


#include "Character/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	//让角色旋转到指定方向再移动，且使用RotationRate作为旋转速率
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置旋转速率，因为只有偏航旋转
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	//只在平面移动
	GetCharacterMovement()->bConstrainToPlane = true;
	//使角色开始时能够捕捉到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//不让输入控制器控制胶囊体的Rotation,让输入控制只影响摄像机
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;



}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 为Server初始化Ability Actor
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 为Client初始化Ability Actor
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
}
