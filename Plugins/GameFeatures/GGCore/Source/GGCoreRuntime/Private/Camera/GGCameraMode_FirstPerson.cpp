// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/GGCameraMode_FirstPerson.h"

UGGCameraMode_FirstPerson::UGGCameraMode_FirstPerson()
{
	FieldOfView = 90.0f;
}

void UGGCameraMode_FirstPerson::UpdateView(float DeltaTime)
{
	Super::UpdateView(DeltaTime);

	const FVector PivotLocation = GetPivotLocation();
	const FRotator PivotRotation = GetPivotRotation();

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = PivotRotation;
	View.FieldOfView = FieldOfView;
}
