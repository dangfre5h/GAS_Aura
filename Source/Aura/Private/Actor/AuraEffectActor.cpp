// Copyright Yang Yu


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

//Ӧ��Ч����Actor��
void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectrClass)
{
	//ͨ���⺯����ȡASC
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr) return;

	check(GameplayEffectrClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//�ѵ�ǰEffectActor��ӵ�EffectContextHandle��Դ����
	EffectContextHandle.AddSourceObject(this);
	//����EffectSpecHandle
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectrClass, 1.f, EffectContextHandle);
	//����ϷЧ��Ӧ�õ�Target��
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}


