// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


//#include "Particles/ParticleSystem.h"
// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";
		
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire() {
	//  ׷������˫�۵�ʮ��׼��λ�ã���Ļ���룩�Ĺ켣
	AActor* MyOwner = GetOwner(); //��ȡ����������
	if (MyOwner) {
		FVector EyeLocation; //˫��λ��
		FRotator EyeRotation;//˫��ת��
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;//��ײ
		QueryParams.AddIgnoredActor(MyOwner);//�����Լ�
		QueryParams.AddIgnoredActor(this);//��������
		QueryParams.bTraceComplex = true;//���������Ӿ�ȷ

		FVector TracerEndPoint = TraceEnd;


		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility,QueryParams))
		{//������������ײ�¼�����ʱ�����˺�

			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor,20.0f,ShotDirection,Hit,MyOwner->GetInstigatorController(),this,DamageType);
			if (ImpactEffect) 
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}
			
			TracerEndPoint = Hit.ImpactPoint;
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f,0,1.0f);
		
		if (MuzzleEffect) 
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
		}
		
		if (TracerEffect) 
		{
			FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

			UParticleSystemComponent* TracerComp =UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect,MuzzleLocation);
			
			if (TracerComp) 
			{
				TracerComp->SetVectorParameter(TracerTargetName,TracerEndPoint);
			}
		}
	



	}
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

