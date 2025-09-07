// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/LyraCameraMode.h"
#include "GGCameraMode_FirstPerson.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GGCORERUNTIME_API UGGCameraMode_FirstPerson : public ULyraCameraMode
{
	GENERATED_BODY()

public:
	UGGCameraMode_FirstPerson();

protected:
	virtual void UpdateView(float DeltaTime) override;
};
