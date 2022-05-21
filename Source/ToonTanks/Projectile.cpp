// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Smoke Trail");

	ParticleSystemComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent->MaxSpeed = 1300;
	ProjectileMovementComponent->InitialSpeed = 1300;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& HitResult)
{
	auto MyOwner = GetOwner();
	if(HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, HitResult.ImpactPoint, GetActorRotation());
	}
	
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	if(HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	
	if(MyOwner)
	{
		auto InstigatorOwner = MyOwner->GetInstigatorController();
		if(OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorOwner,this, UDamageType::StaticClass());
			GetWorld()->DestroyActor(this);
		}
	}
	GetWorld()->DestroyActor(this);
}

