// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionClient.h"
#include "ActionPawn.h"
#include "InputManager.h"
#include "ActionHelper.h"




AActionPawn::AActionPawn( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{

	// Create root component
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>( this, TEXT( "RootComponent" ) );

	// Create camera component 
	ActionPawnCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "ActionPawnCamera" ) );
	ActionPawnCamera->SetupAttachment( RootComponent );

	FTransform ActionPawnCameraTransform( FRotator::ZeroRotator, FVector( 0.f, 0.f, 70.f ) );
	ActionPawnCamera->SetRelativeTransform( ActionPawnCameraTransform );

	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>( this, TEXT( "PawnMesh1P" ) );
	Mesh1P->SetupAttachment( ActionPawnCamera );
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	FTransform Mesh1PTransform( FRotator( 0.f, -90.f, 0.f ), FVector( 0.f, 0.f, -150.f ) );
	Mesh1P->SetRelativeTransform( Mesh1PTransform );

	Mesh3P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>( this, TEXT( "PawnMesh3P" ) );
	Mesh3P->SetupAttachment( RootComponent );
	Mesh3P->bOnlyOwnerSee = false;
	Mesh3P->bOwnerNoSee = true;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh3P->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	FTransform Mesh3PTransform( FRotator( 0.f, -90.f, 0.f ), FVector( 0.f, 0.f, -86.f ) );
	Mesh3P->SetRelativeTransform( Mesh3PTransform );

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 2.f;
	BaseLookUpRate = 2.f;

	MaxSpeed = 440;
	Acceleration = 1000.f;
	Deceleration = 2000.f;
	TurningBoost = 8.0f;

}

// Called when the game starts or when spawned
void AActionPawn::BeginPlay()
{
	Super::BeginPlay();


	//FRotator eulerRot = FRotator( 12, -3.4, 7 );
	//FRotator eulerRot = FRotator( 0.f, 0.f, 86.1f );
	FRotator eulerRot = FRotator( 10.f, 30.f, 279.1f );
	FQuat quatRot = eulerRot.Quaternion();
	//quatRot = FQuat()
	//quatRot.GetForwardVector();
	//Quaternion quatRot = Quaternion::FromEuler( eulerRot );


	//std::cout << quatRot.X << ", " << quatRot.Y << ", " << quatRot.Z << ", " << quatRot.W << std::endl;

	ActionHelper::ScreenMsg( "quatRot.X = ", quatRot.X );
	ActionHelper::ScreenMsg( "quatRot.Y = ", quatRot.Y );
	ActionHelper::ScreenMsg( "quatRot.Z = ", quatRot.Z );
	ActionHelper::ScreenMsg( "quatRot.W = ", quatRot.W );

	//FRotator newRot = quatRot.Rotator();

	//ActionHelper::ScreenMsg( "newRot.X = ", newRot.Roll );
	//ActionHelper::ScreenMsg( "newRot.Y = ", newRot.Pitch );
	//ActionHelper::ScreenMsg( "newRot.Z = ", newRot.Yaw );

	
	ActionHelper::ScreenMsg( "quatRot.GetForwardVector().X = ", quatRot.GetForwardVector().X );
	ActionHelper::ScreenMsg( "quatRot.GetForwardVector().Y = ", quatRot.GetForwardVector().Y );
	ActionHelper::ScreenMsg( "quatRot.GetForwardVector().Z = ", quatRot.GetForwardVector().Z );

	ActionHelper::ScreenMsg( "quatRot.GetRightVector().X = ", quatRot.GetRightVector().X );
	ActionHelper::ScreenMsg( "quatRot.GetRightVector().Y = ", quatRot.GetRightVector().Y );
	ActionHelper::ScreenMsg( "quatRot.GetRightVector().Z = ", quatRot.GetRightVector().Z );

	ActionHelper::ScreenMsg( "quatRot.GetUpVector().X = ", quatRot.GetUpVector().X );
	ActionHelper::ScreenMsg( "quatRot.GetUpVector().Y = ", quatRot.GetUpVector().Y );
	ActionHelper::ScreenMsg( "quatRot.GetUpVector().Z = ", quatRot.GetUpVector().Z );
}


// Called every frame
void AActionPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	Update();
}

// Called to bind functionality to input
void AActionPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	check( PlayerInputComponent );
	PlayerInputComponent->BindAxis( "MoveForward", this, &AActionPawn::MoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &AActionPawn::MoveRight );
	PlayerInputComponent->BindAxis( "Turn", this, &AActionPawn::Turn );
	PlayerInputComponent->BindAxis( "LookUp", this, &AActionPawn::LookUp );
}



void AActionPawn::MoveForward( float Val )
{
	//if (Val != 0.f)
	//{
		//const FQuat Rotation = GetActorQuat();
		//const FVector Direction = FQuatRotationMatrix( Rotation ).GetScaledAxis( EAxis::X );
		//ActionAddMovementInput( Direction * Val );


		InputManager::sInstance->HandleInput( InputManager::EIA_MoveForward, Val );
	//}
}

void AActionPawn::MoveRight( float Val )
{
	//if (Val != 0.f)
	//{
		//const FQuat Rotation = GetActorQuat();
		//const FVector Direction = FQuatRotationMatrix( Rotation ).GetScaledAxis( EAxis::Y );
		//ActionAddMovementInput( Direction * Val );

		InputManager::sInstance->HandleInput( InputManager::EIA_MoveRight, Val );
	//}
}

void AActionPawn::Turn( float Val )
{
	//APawn::AddControllerYawInput( Val );
	//if ( Val != 0 )
	//{
		//FRotator newRot( GetActorRotation() );
		//newRot.Yaw += ( BaseTurnRate * Val );
		//SetActorRotation( newRot );

		InputManager::sInstance->HandleInput( InputManager::EIA_Turn, Val );

	//}

}

void AActionPawn::LookUp( float Val )
{
	//AddControllerPitchInput( Val );

	//if ( ActionPawnCamera && Val != 0 )
	//{
		//FRotator newRot( ActionPawnCamera->GetComponentRotation() );
		//newRot.Pitch = FMath::Clamp( ( newRot.Pitch + ( -1 * BaseLookUpRate * Val ) ), -89.f, 89.f );
		//ActionPawnCamera->SetWorldRotation( newRot );

		InputManager::sInstance->HandleInput( InputManager::EIA_LookUp, Val );
	//}
}

bool AActionPawn::IsExceedingMaxSpeed( float inMaxSpeed ) const
{
	inMaxSpeed = FMath::Max( 0.f, inMaxSpeed );
	const float MaxSpeedSquared = FMath::Square( inMaxSpeed );

	// Allow 1% error tolerance, to account for numeric imprecision.
	const float OverVelocityPercent = 1.01f;
	return ( Velocity.SizeSquared() > MaxSpeedSquared * OverVelocityPercent );
}

void AActionPawn::ActionAddMovementInput( FVector WorldDirection, float ScaleValue /*= 1.0f*/ )
{
	ActionControlInputVector += WorldDirection * ScaleValue;
}

FVector AActionPawn::ActionConsumeMovementInputVector()
{
	ActionLastControlInputVector = ActionControlInputVector;
	ActionControlInputVector = FVector::ZeroVector;
	return ActionLastControlInputVector;
}

FVector AActionPawn::ActionGetPendingInputVector() const
{
	// There's really no point redirecting to the MovementComponent since GetInputVector is not virtual there, and it just comes back to us.
	return ActionControlInputVector;
}

void AActionPawn::ApplyControlInputToVelocity( float DeltaTime )
{
	const FVector ControlAcceleration = ActionGetPendingInputVector().GetClampedToMaxSize( 1.f );

	const float AnalogInputModifier = ( ControlAcceleration.SizeSquared() > 0.f ? ControlAcceleration.Size() : 0.f );
	const float MaxPawnSpeed = GetMaxSpeed() * AnalogInputModifier;
	const bool bExceedingMaxSpeed = IsExceedingMaxSpeed( MaxPawnSpeed );

	if (AnalogInputModifier > 0.f && !bExceedingMaxSpeed)
	{
		// Apply change in velocity direction
		if (Velocity.SizeSquared() > 0.f)
		{
			// Change direction faster than only using acceleration, but never increase velocity magnitude.
			const float TimeScale = FMath::Clamp( DeltaTime * TurningBoost, 0.f, 1.f );
			Velocity = Velocity + ( ControlAcceleration * Velocity.Size() - Velocity ) * TimeScale;
		}
	}
	else
	{
		// Dampen velocity magnitude based on deceleration.
		if (Velocity.SizeSquared() > 0.f)
		{
			const FVector OldVelocity = Velocity;
			const float VelSize = FMath::Max( Velocity.Size() - FMath::Abs( Deceleration ) * DeltaTime, 0.f );
			Velocity = Velocity.GetSafeNormal() * VelSize;

			// Don't allow braking to lower us below max speed if we started above it.
			if (bExceedingMaxSpeed && Velocity.SizeSquared() < FMath::Square( MaxPawnSpeed ))
			{
				Velocity = OldVelocity.GetSafeNormal() * MaxPawnSpeed;
			}
		}
	}

	// Apply acceleration and clamp velocity magnitude.
	const float NewMaxSpeed = ( IsExceedingMaxSpeed( MaxPawnSpeed ) ) ? Velocity.Size() : MaxPawnSpeed;
	Velocity += ControlAcceleration * FMath::Abs( Acceleration ) * DeltaTime;
	Velocity = Velocity.GetClampedToMaxSize( NewMaxSpeed );

	Velocity.Z = 0.f;

	ActionConsumeMovementInputVector();
}

void AActionPawn::Update()
{
	//if (GetPlayerId() == NetworkManager::sInstance->GetPlayerId())
	//{
		const Action* pendingMove = InputManager::sInstance->GetAndClearPendingAction();
		//in theory, only do this if we want to sample input this frame / if there's a new move ( since we have to keep in sync with server )
		if (pendingMove) //is it time to sample a new move...
		{
			float deltaTime = pendingMove->GetDeltaTime();

			//apply that input

			ProcessInput( deltaTime, pendingMove->GetInputState() );

			//and simulate!

			//SimulateMovement( deltaTime );

			//LOG( "Client Move Time: %3.4f deltaTime: %3.4f left rot at %3.4f", latestMove.GetTimestamp(), deltaTime, GetRotation() );
		}
	//}
	//else
	//{
	//	SimulateMovement( Timing::sInstance.GetDeltaTime() );

	//	if (RoboMath::Is2DVectorEqual( GetVelocity(), Vector3::Zero ))
	//	{
	//		//we're in sync if our velocity is 0
	//		mTimeLocationBecameOutOfSync = 0.f;
	//	}
	//}
}

void AActionPawn::ProcessInput( float inDeltaTime, const ActionInputState& inInputState )
{
	FRotator newRot( GetActorRotation() );
	newRot.Yaw += ( BaseTurnRate * inInputState.GetDesiredTurnAmount() );
	SetActorRotation( newRot );

	newRot = ActionPawnCamera->GetComponentRotation();
	newRot.Pitch = FMath::Clamp( ( newRot.Pitch + ( -1 * BaseLookUpRate * inInputState.GetDesiredLookUpAmount() ) ), -89.f, 89.f );
	ActionPawnCamera->SetWorldRotation( newRot );

	//const FQuat Rotation = GetActorQuat();
	//const FVector Direction = FQuatRotationMatrix( Rotation ).GetScaledAxis( EAxis::X );
	//ActionAddMovementInput( Direction * Val );

	//const FQuat Rotation = GetActorQuat();
	//const FVector Direction = FQuatRotationMatrix( Rotation ).GetScaledAxis( EAxis::Y );
	//ActionAddMovementInput( Direction * Val );

	const FQuatRotationMatrix newRotMatrix = FQuatRotationMatrix( newRot.Quaternion() );
	ActionAddMovementInput( newRotMatrix.GetScaledAxis( EAxis::X ), inInputState.GetDesiredMoveForwardAmount() );
	ActionAddMovementInput( newRotMatrix.GetScaledAxis( EAxis::Y ), inInputState.GetDesiredMoveRightAmount() );


	ApplyControlInputToVelocity( inDeltaTime );

	// Move actor
	FVector Delta = Velocity * inDeltaTime;

	if (!Delta.IsNearlyZero( 1e-6f ))
	{
		SetActorLocation( GetActorLocation() + Delta );
	}

}

bool AActionPawn::IsFirstPerson() const
{
	return true;
	//return IsAlive() && Controller && Controller->IsLocalPlayerController();
}

void AActionPawn::OnCameraUpdate( const FVector& CameraLocation, const FRotator& CameraRotation )
{
	USkeletalMeshComponent* DefMesh1P = Cast<USkeletalMeshComponent>( GetClass()->GetDefaultSubobjectByName( TEXT( "PawnMesh1P" ) ) );
	const FMatrix DefMeshLS = FRotationTranslationMatrix( DefMesh1P->RelativeRotation, DefMesh1P->RelativeLocation );
	const FMatrix LocalToWorld = ActorToWorld().ToMatrixWithScale();

	// Mesh rotating code expect uniform scale in LocalToWorld matrix

	const FRotator RotCameraPitch( CameraRotation.Pitch, 0.0f, 0.0f );
	const FRotator RotCameraYaw( 0.0f, CameraRotation.Yaw, 0.0f );

	const FMatrix LeveledCameraLS = FRotationTranslationMatrix( RotCameraYaw, CameraLocation ) * LocalToWorld.Inverse();
	const FMatrix PitchedCameraLS = FRotationMatrix( RotCameraPitch ) * LeveledCameraLS;
	const FMatrix MeshRelativeToCamera = DefMeshLS * LeveledCameraLS.Inverse();
	const FMatrix PitchedMesh = MeshRelativeToCamera * PitchedCameraLS;

	Mesh1P->SetRelativeLocationAndRotation( PitchedMesh.GetOrigin(), PitchedMesh.Rotator() );
}
