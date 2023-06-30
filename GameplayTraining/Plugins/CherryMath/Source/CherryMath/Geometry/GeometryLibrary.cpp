#include "GeometryLibrary.h"

#include "Ray.h"

namespace Cherry
{
	RelationshipBetweenRays GeometryLibrary::GetInfoBetweenRays(const Ray& Ray1, const Ray& Ray2, float& OutDeltaRay1,
		float& OutDeltaRay2)
	{
		RelationshipBetweenRays Result = RelationshipBetweenRays::Coincide;

		// 两线🍌算法	Intersection of Two Lines in 3D Space
		// https://www.youtube.com/watch?v=N-qUfr-rz_Y&list=PL3d-XcUlfFv7Q6WCP1yJyN50CDwjGvrLs

		// t1,t2为若相交，交点在两条直线上移动的距离
		float t1 = 0;
		float t2 = 0;
		FVector Direction1 = Ray1.GetDirection();
		FVector Origin1 = Ray1.GetOrigin();

		FVector Direction2 = Ray2.GetDirection();
		FVector Origin2 = Ray2.GetOrigin();
			
		bool bIntersection = false;
		float Value1 = Direction2.Y * Direction1.X - Direction2.X * Direction1.Y;
		if (Value1 == 0)
		{
			FVector OriDelNormal = (Origin2 - Origin1).GetSafeNormal().GetAbs();
			FVector DirNormal1 = Direction1.GetSafeNormal().GetAbs();
			FVector DirNormal2 = Direction2.GetSafeNormal().GetAbs();
			if (DirNormal1 == DirNormal2)
			{
				if (Origin1 == Origin2 || OriDelNormal == DirNormal1)
				{
					Result = RelationshipBetweenRays::Coincide;
				}
				else
				{
					Result = RelationshipBetweenRays::Parallel;
				}
			}
			else
			{
				Result = RelationshipBetweenRays::Skewness;
			}
		}
		else
		{
			// 将X式,Y式带入得出t1和t2
			t2 = ((Origin2.X - Origin1.X) * Direction1.Y - (Origin2.Y - Origin1.Y) * Direction1.X) / Value1;
			if (Direction1.X != 0)
			{
				t1 = (t2 * Direction2.X + Origin2.X - Origin1.X) / Direction1.X;
			}
			else if (Direction2.Y != 0)
			{
				t1 = (t2 * Direction2.Y + Origin2.Y - Origin1.Y) / Direction1.Y;
			}
			else
			{
				t1 = (t2 * Direction2.Z + Origin2.Z - Origin1.Z) / Direction1.Z;
			}

			// 将t1和t2带入Z式
			if (Origin1.Z + Direction1.Z * t1 == Origin2.Z + Direction2.Z * t2)
			{
				Result = RelationshipBetweenRays::Intersect;
				OutDeltaRay1 = t1;
				OutDeltaRay2 = t2;
			}
			else
			{
				Result = RelationshipBetweenRays::Skewness;
			}
		}

		return Result;
	}
}
