// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VehicleTypes.h"
#include "WheeledVehicle.h"
#include "BmwPawn.generated.h"

class AVehicleTrackPoint;
class UVehicleDustType;
class AVehicleImpactEffect;

UCLASS()
class ABmwPawn : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()

	// Begin Actor overrides
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalForce, const FHitResult& Hit) override;
	virtual void FellOutOfWorld(const UDamageType& dmgType) override;
	// Begin Pawn overrides
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void TornOff() override;
	virtual void UnPossessed() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, ReplicatedUsing = OnRep_Dying)
		uint32 bIsDying : 1;

	UFUNCTION()
		void OnRep_Dying();

	virtual bool CanDie() const;
	virtual void Die();
	virtual void OnDeath();

	void OnTrackPointReached(AVehicleTrackPoint* TrackPoint);

	/** is handbrake active? */
	UFUNCTION(BlueprintCallable, Category = "Game|Vehicle")
		bool IsHandbrakeActive() const;

	float GetVehicleSpeed() const;
	float GetEngineRotationSpeed() const;
	float GetEngineMaxRotationSpeed() const;
	void OnHandbrakePressed();
	void OnHandbrakeReleased();

	void MoveForward(float Val);
	void MoveRight(float Val);

	struct FVehicleDesiredRPM
	{
		float DesiredRPM;
		float TimeStamp;
	};

	static bool GetVehicleDesiredRPM_AudioThread(const uint32 VehicleID, FVehicleDesiredRPM& OutDesiredRPM);

private:
	/*UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;*/

	static TMap<uint32, FVehicleDesiredRPM> BmwDesiredRPMs;

protected:
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		UVehicleDustType* DustType;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		TSubclassOf<AVehicleImpactEffect> ImpactTemplate;

	UPROPERTY(EditAnywhere, Category = Effects)
		float ImpactEffectNormalForceThreshold;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		UParticleSystem* DeathFX;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* DeathSound;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* EngineSound;

private:
	UPROPERTY(Category = Effects, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* EngineAC;
protected:
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* LandingSound;

	UPROPERTY(Transient)
		UParticleSystemComponent* DustPSC[4];

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* SkidSound;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* SkidSoundStop;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidFadeoutTime;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidThresholdVelocity;

	UPROPERTY(Category = Effects, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
		float LongSlipSkidThreshold;

	UPROPERTY(Category = Effects, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
		float LateralSlipSkidThreshold;

private:
	UPROPERTY()
		UAudioComponent* SkidAC;
protected:

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SpringCompressionLandingThreshold;

	bool bTiresTouchingGround;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidDurationRequiredForStopSound;

	bool bSkidding;

	float SkidStartTime;

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		TSubclassOf<UCameraShake> ImpactCameraShake;

	float ThrottleInput;
	float TurnInput;
	uint32 bHandbrakeActive : 1;
	uint32 bKeyboardThrottle : 1;
	uint32 bKeyboardTurn : 1;
	uint32 bTurnLeftPressed : 1;
	uint32 bTurnRightPressed : 1;
	uint32 bAcceleratePressed : 1;
	uint32 bBreakReversePressed : 1;

	void SpawnNewWheelEffect(int WheelIndex);
	void UpdateWheelEffects(float DeltaTime);
	void PlayDestructionFX();

protected:
	/*FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }*/
	FORCEINLINE UAudioComponent* GetEngineAC() const { return EngineAC; }
	FORCEINLINE UAudioComponent* GetSkidAC() const { return SkidAC; }
	
};
