// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GeometricCurveWidget.generated.h"


UENUM(BlueprintType)
enum class EGeometricCurveType : uint8
{
	Linear,
	EaseIn,
	EaseOut,
	EaseInOut,
	SinIn,
	SinOut,
	SinInOut,
	ExpoIn,
	ExpoOut,
	ExpoInOut,
	CircularIn,
	CircularOut,
	CircularInOut,
	InterpStep
};

USTRUCT(BlueprintType)
struct FGeometricCurveConfig
{
	GENERATED_BODY()

	float EvaluateFunctionValue(float XValue) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGeometricCurveType GeometricCurveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Exponent = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Length = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XIndex = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BrushSize = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Green;
};

/**
 * 
 */
UCLASS()
class BASICS_API UGeometricCurveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	// 坐标轴位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ZeroPoint = FVector2D(500, 500);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D AxisLength = FVector2D(1000, 1000);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AxisBrushSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor AxisColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGeometricCurveConfig> Configs;

private:
	void GetIndexPoints(TArray<FVector2D>& Points)
	{
		for (FVector2D& Point : Points)
		{
			Point.X += ZeroPoint.X;
			Point.Y += ZeroPoint.Y;
		}
	}
	
	//线的绘制
	void DrawSmoothedLine(
		FSlateWindowElementList& OutDrawElement,
		int InLayerId,
		const FGeometry& InAllottedGeometry
	);
};
