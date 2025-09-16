// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/GGCameraMode_FirstPerson.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UGGCameraMode_FirstPerson::UGGCameraMode_FirstPerson()
{
	FieldOfView = 90.0f;
	ViewOffset = FVector::ZeroVector;
	PivotOffset = FVector::ZeroVector;
}

void UGGCameraMode_FirstPerson::UpdateView(float DeltaTime)
{
	Super::UpdateView(DeltaTime);

	ACharacter* CharacterOwner = Cast<ACharacter>(GetTargetActor());
	if (!CharacterOwner) return;

	USkeletalMeshComponent* Mesh = CharacterOwner->GetMesh();
	if (!Mesh) return;
	
	
	if (Mesh->DoesSocketExist(CameraSocketName))
	{
		const FTransform SocketTransform = Mesh->GetSocketTransform(CameraSocketName, RTS_World);
		const FVector TargetLocation = SocketTransform.GetLocation();

		if (bEnablePositionLag)
		{
			//카메라 보정함수
			View.Location = FMath::VInterpTo(View.Location, TargetLocation, DeltaTime, PositionLag);
		}
		else
		{
			View.Location = TargetLocation;
		}
	}
	
	if (!ViewOffset.IsZero())
	{
		View.Location += View.Rotation.RotateVector(ViewOffset);
	} 
}

FVector UGGCameraMode_FirstPerson::GetPivotLocation() const
{
	const FVector BasePivotLocation = Super::GetPivotLocation();

	const FVector NewPivotLocation = BasePivotLocation + PivotOffset;

	return NewPivotLocation;
}
