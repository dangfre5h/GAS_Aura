// Copyright Yang Yu


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	// 设置为false，无需每帧执行Tick函数
	PrimaryActorTick.bCanEverTick = false;

	//创建Weapon组件，传参数为组件名称，类型FName,FName类型无需使用TEXT宏，直接输入字符即可，可自动转换
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//将武器附加在名称为"WeaponHandSocket"的插座上
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//武器没有碰撞
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}


