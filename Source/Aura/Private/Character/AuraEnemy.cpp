// Copyright Yang Yu


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	//设置成block才能被鼠标指向识别
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//创建ASC和AS
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	//设置ASC可复制
	AbilitySystemComponent->SetIsReplicated(true);


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");

}

void AAuraEnemy::HighlightActor()
{
	//因为后期处理体积PostProcessVolume下面所选择的材料，是针对CustomDepth为250的网格进行高亮，所以此处赋值250
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
