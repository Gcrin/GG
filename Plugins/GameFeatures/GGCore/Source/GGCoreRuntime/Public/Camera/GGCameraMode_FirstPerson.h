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
	virtual FVector GetPivotLocation() const override;

	// 카메라의 위치를 조정하기 위한 오프셋 변수입니다.
	UPROPERTY(EditDefaultsOnly, Category = "First Person")
	FVector ViewOffset;

	// 피벗 위치를 조정하기 위한 변수입니다. 캐릭터의 기본 눈 위치를 기준으로 합니다.
	UPROPERTY(EditDefaultsOnly, Category = "First Person")
	FVector PivotOffset;

	// 카메라 보정 값
	UPROPERTY(EditDefaultsOnly, Category="First Person", meta=(ClampMin="0.0", UIMin="0.0", ToolTip="위치 보정 속도. 0이면 즉시 이동"))
	float PositionLag = 20.f;

	// 카메라를 붙일 소켓 이름
	UPROPERTY(EditDefaultsOnly, Category="First Person")
	FName CameraSocketName = TEXT("CameraSocket");

	// 카메라 보정 활성화
	UPROPERTY(EditDefaultsOnly, Category="First Person")
	bool bEnablePositionLag = true;
	
};
