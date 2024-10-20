// Copyright Yang Yu


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	//���ó�block���ܱ����ָ��ʶ��
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//����ASC��AS
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	//����ASC�ɸ���
	AbilitySystemComponent->SetIsReplicated(true);


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");

}

void AAuraEnemy::HighlightActor()
{
	//��Ϊ���ڴ������PostProcessVolume������ѡ��Ĳ��ϣ������CustomDepthΪ250��������и��������Դ˴���ֵ250
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
