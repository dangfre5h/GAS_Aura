// Copyright Yang Yu


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: ��ʱʹ��const_castǿ��ͨ��AuraAttributeSet���в������ã�������Ҫ��Ϊͨ��Gameplay Effectʵ��

	//�����Ƶ����תΪIAbilitySystemInterface
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//��ȡASC,Ȼ���ȡAS
		const UAttributeSet* AttributeSet = ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass());
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
		//const UAuraAttributeSet�޷�ֱ��SetHealth��ת��ȥ��const
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 15.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	//����ײ��������ײ����
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}


