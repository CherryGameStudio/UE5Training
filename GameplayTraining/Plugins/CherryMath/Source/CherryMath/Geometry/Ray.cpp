// Fill out your copyright notice in the Description page of Project Settings.


#include "Ray.h"

namespace Cherry
{
	Ray::Ray(FVector InOrigin, FVector InDirection)
	{
		Origin = InOrigin;
		Direction = InDirection;
	}

	bool Ray::IsPointInRay(FVector& Point, int& OutDelta)
	{
		return true;
	}
}

