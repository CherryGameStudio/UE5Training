#pragma once
#include "Ray.h"
struct Ray;
enum class RelationshipBetweenRays;

namespace Cherry
{
	class GeometryLibrary
	{
	public:
		// 计算两条线的关系
		static RelationshipBetweenRays GetInfoBetweenRays(const Ray& Ray1, const Ray& Ray2, float& OutDeltaRay1, float& OutDeltaRay2);

	};
}

