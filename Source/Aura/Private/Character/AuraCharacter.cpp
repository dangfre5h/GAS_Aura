// Copyright Yang Yu


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
