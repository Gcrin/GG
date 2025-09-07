// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/GGCameraMode_FirstPerson.h"

UGGCameraMode_FirstPerson::UGGCameraMode_FirstPerson()
{
	FieldOfView = 90.0f;
	ViewOffset = FVector::ZeroVector;
	PivotOffset = FVector::ZeroVector;
}

void UGGCameraMode_FirstPerson::UpdateView(float DeltaTime)
{
	Super::UpdateView(DeltaTime);

	if (!ViewOffset.IsZero())
	{
		const FRotator ViewRotation = GetCameraModeView().Rotation;
		View.Location += ViewRotation.RotateVector(ViewOffset);
	}
}

FVector UGGCameraMode_FirstPerson::GetPivotLocation() const
{
	const FVector BasePivotLocation = Super::GetPivotLocation();

	const FVector NewPivotLocation = BasePivotLocation + PivotOffset;

	return NewPivotLocation;
}
