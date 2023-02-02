#include "CollisionTypes.h"

FHitResultVisiable& FHitResultVisiable::operator = (const FHitResult& HitResult)
{
	FaceIndex = HitResult.FaceIndex;
	Time = HitResult.Time;
	Distance = HitResult.Distance;
	Location = HitResult.Location;
	ImpactPoint = HitResult.ImpactPoint;
	Normal = HitResult.Normal;
	ImpactNormal = HitResult.ImpactNormal;
	TraceStart = HitResult.TraceStart;
	TraceEnd = HitResult.TraceEnd;
	PenetrationDepth = HitResult.PenetrationDepth;
	MyItem = HitResult.MyItem;
	Item = HitResult.Item;
	ElementIndex = HitResult.ElementIndex;
	bBlockingHit = HitResult.bBlockingHit;
	bStartPenetrating = HitResult.bStartPenetrating;
	//PhysMaterial = HitResult.PhysMaterial.Get();
	HitObjectHandle = HitResult.HitObjectHandle;
	Component = HitResult.Component;
	BoneName = HitResult.BoneName;
	MyBoneName = HitResult.MyBoneName;
		
	return *this;
}