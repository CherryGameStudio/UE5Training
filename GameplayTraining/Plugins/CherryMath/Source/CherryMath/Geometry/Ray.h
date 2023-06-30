// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"


namespace Cherry
{
	// 两条线之间的关系。
	enum class RelationshipBetweenRays : uint8
	{
		Skewness,		// 异面
		Intersect,		// 相交
		Parallel,		// 平行
		Coincide,		// 重合
	};
	
	// 线，用于表示射线，线段，直线。
	struct Ray
	{

	public:
		Ray() = delete;

		Ray(FVector InOrigin, FVector InDirection);

		FVector GetDirection() const
		{
			return Direction;
		}
		
		FVector GetOrigin() const
		{
			return Origin;
		}

		// 点是否在线上。
		bool IsPointInRay(FVector& Point, int& OutDelta);

	private:
		// 原点 
		FVector Origin;

		// 方向
		FVector Direction;
	};
}


