// Copyright Yang Yu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

//����ʵ��һЩEffect��Actor�Ļ��࣬��Ѫƿ����ƿ��
//��Ҫ����overlap���

class USphereComponent;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	//UFUNCTION����ӣ�������Ч
	//OtherActor�Ǵ����ص��¼������壬ͨ���ǿ��Ƶ���ҽ�ɫ
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//�����ص��¼��ĺ���
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

private:
	//���ڱ����ص����
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	//���ڱ���Actor�ľ�̬�壬����ҩƿ
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
