// Copyright Yang Yu


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
