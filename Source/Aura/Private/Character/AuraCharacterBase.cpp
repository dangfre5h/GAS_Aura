// Copyright Yang Yu


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	// ����Ϊfalse������ÿִ֡��Tick����
	PrimaryActorTick.bCanEverTick = false;

	//����Weapon�����������Ϊ������ƣ�����FName,FName��������ʹ��TEXT�ֱ꣬�������ַ����ɣ����Զ�ת��
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//����������������Ϊ"WeaponHandSocket"�Ĳ�����
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//����û����ײ
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}


