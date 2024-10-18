// Copyright Yang Yu


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// 设置为false，无需每帧执行Tick函数
	PrimaryActorTick.bCanEverTick = false;

}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


