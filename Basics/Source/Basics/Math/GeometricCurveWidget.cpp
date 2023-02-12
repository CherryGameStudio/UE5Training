// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometricCurveWidget.h"

#include "Components/CanvasPanelSlot.h"

int32 UGeometricCurveWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const_cast<UGeometricCurveWidget*>(this)->DrawSmoothedLine(
		OutDrawElements,
		LayerId,
		AllottedGeometry
		);
	return LayerId++;
}

void UGeometricCurveWidget::DrawSmoothedLine(FSlateWindowElementList& OutDrawElement, int InLayerId,
	const FGeometry& InAllottedGeometry)
{
	TArray<FVector2D> XAxis = {FVector2D(0,0), FVector2D(AxisLength.X,0)};
	GetIndexPoints(XAxis);
	
	FSlateDrawElement::MakeLines(
	OutDrawElement,
	InLayerId,
	InAllottedGeometry.ToPaintGeometry(),
	XAxis,
	ESlateDrawEffect::None,
	AxisColor,
	true,
	AxisBrushSize
	);

	TArray<FVector2D> YAxis = {FVector2D(0,0), FVector2D(0,-AxisLength.Y)};
	GetIndexPoints(YAxis);
	
	FSlateDrawElement::MakeLines(
	OutDrawElement,
	InLayerId,
	InAllottedGeometry.ToPaintGeometry(),
	YAxis,
	ESlateDrawEffect::None,
	AxisColor,
	true,
	AxisBrushSize
	);

	for(const FGeometricCurveConfig& Config : Configs)
	{
		TArray<FVector2D> ResultPoints;
		for (int X = 0; X < Config.Length; ++X)
		{
			// 几何公式
			int Y = Config.EvaluateFunctionValue(X);

			// UI Y轴越大，越往下
			ResultPoints.Add(FVector2D(X, -Y));
		}

		GetIndexPoints(ResultPoints);

		FSlateDrawElement::MakeLines(
			OutDrawElement,
			++InLayerId,
			InAllottedGeometry.ToPaintGeometry(),
			ResultPoints,
			ESlateDrawEffect::None,
			Config.Color,
			true,
			Config.BrushSize
		);
	}
}

float FGeometricCurveConfig::EvaluateFunctionValue(float XValue) const
{
	float ResultY = XValue;
	float Min = 0;
	float Max = Length;
	float Alpha = XValue / Max;
	float InExponent = Exponent > 0 ? Exponent : 1;
	switch (GeometricCurveType) {
		case EGeometricCurveType::Linear:
			ResultY = FMath::Lerp(Min, Max, Alpha);
			break;

		case EGeometricCurveType::EaseIn:
			ResultY = FMath::InterpEaseIn(Min, Max, Alpha, InExponent);
			break;

		case EGeometricCurveType::EaseOut:
			ResultY = FMath::InterpEaseOut(Min, Max, Alpha, InExponent);
			break;

		case EGeometricCurveType::EaseInOut:
			ResultY = FMath::InterpEaseInOut(Min, Max, Alpha, InExponent);
			break;

		case EGeometricCurveType::SinIn:
			ResultY = FMath::InterpSinIn(Min, Max, Alpha);
			break;
		
		case EGeometricCurveType::SinOut:
			ResultY = FMath::InterpSinOut(Min, Max, Alpha);
			break;
		
		case EGeometricCurveType::SinInOut:
			ResultY = FMath::InterpSinInOut(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::ExpoIn:
			ResultY = FMath::InterpExpoIn(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::ExpoOut:
			ResultY = FMath::InterpExpoOut(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::ExpoInOut:
			ResultY = FMath::InterpExpoInOut(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::CircularIn:
			ResultY = FMath::InterpCircularIn(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::CircularOut:
			ResultY = FMath::InterpCircularOut(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::CircularInOut:
			ResultY = FMath::InterpCircularInOut(Min, Max, Alpha);	
			break;
		
		case EGeometricCurveType::InterpStep:
			ResultY = FMath::InterpStep(Min, Max, Alpha, static_cast<int32>(Exponent));	
			break;
		default:
			
			;
	}

	return ResultY;
}
