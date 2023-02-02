#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "Templates/SubclassOf.h"
#include "Engine/NetSerialization.h"
#include "CollisionTypes.generated.h"

// 可访问的FHitResult
USTRUCT(BlueprintType)
struct FHitResultVisiable
{
	GENERATED_BODY()

	/** Face index we hit (for complex hits with triangle meshes). */
	UPROPERTY(VisibleAnywhere)
	int32 FaceIndex;

	/**
	 * 'Time' of impact along trace direction (ranging from 0.0 to 1.0) if there is a hit, indicating time between TraceStart and TraceEnd.
	 * For swept movement (but not queries) this may be pulled back slightly from the actual time of impact, to prevent precision problems with adjacent geometry.
	 */
	UPROPERTY(VisibleAnywhere)
	float Time;
	 
	/** The distance from the TraceStart to the Location in world space. This value is 0 if there was an initial overlap (trace started inside another colliding object). */
	UPROPERTY(VisibleAnywhere)
	float Distance; 
	
	/**
	 * The location in world space where the moving shape would end up against the impacted object, if there is a hit. Equal to the point of impact for line tests.
	 * Example: for a sphere trace test, this is the point where the center of the sphere would be located when it touched the other object.
	 * For swept movement (but not queries) this may not equal the final location of the shape since hits are pulled back slightly to prevent precision issues from overlapping another surface.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantize Location;

	/**
	 * Location in world space of the actual contact of the trace shape (box, sphere, ray, etc) with the impacted object.
	 * Example: for a sphere trace test, this is the point where the surface of the sphere touches the other object.
	 * @note: In the case of initial overlap (bStartPenetrating=true), ImpactPoint will be the same as Location because there is no meaningful single impact point to report.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantize ImpactPoint;

	/**
	 * Normal of the hit in world space, for the object that was swept. Equal to ImpactNormal for line tests.
	 * This is computed for capsules and spheres, otherwise it will be the same as ImpactNormal.
	 * Example: for a sphere trace test, this is a normalized vector pointing in towards the center of the sphere at the point of impact.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantizeNormal Normal;

	/**
	 * Normal of the hit in world space, for the object that was hit by the sweep, if any.
	 * For example if a sphere hits a flat plane, this is a normalized vector pointing out from the plane.
	 * In the case of impact with a corner or edge of a surface, usually the "most opposing" normal (opposed to the query direction) is chosen.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantizeNormal ImpactNormal;

	/**
	 * Start location of the trace.
	 * For example if a sphere is swept against the world, this is the starting location of the center of the sphere.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantize TraceStart;

	/**
	 * End location of the trace; this is NOT where the impact occurred (if any), but the furthest point in the attempted sweep.
	 * For example if a sphere is swept against the world, this would be the center of the sphere if there was no blocking hit.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector_NetQuantize TraceEnd;

	/**
	  * If this test started in penetration (bStartPenetrating is true) and a depenetration vector can be computed,
	  * this value is the distance along Normal that will result in moving out of penetration.
	  * If the distance cannot be computed, this distance will be zero.
	  */
	UPROPERTY(VisibleAnywhere)
	float PenetrationDepth;

	/** If the hit result is from a collision this will have extra info about the item that hit the second item. */
	UPROPERTY(VisibleAnywhere)
	int32 MyItem;

	/** Extra data about item that was hit (hit primitive specific). */
	UPROPERTY(VisibleAnywhere)
	int32 Item;

	/** Index to item that was hit, also hit primitive specific. */
	UPROPERTY(VisibleAnywhere)
	uint8 ElementIndex;

	/** Indicates if this hit was a result of blocking collision. If false, there was no hit or it was an overlap/touch instead. */
	UPROPERTY(VisibleAnywhere)
	uint8 bBlockingHit : 1;

	/**
	 * Whether the trace started in penetration, i.e. with an initial blocking overlap.
	 * In the case of penetration, if PenetrationDepth > 0.f, then it will represent the distance along the Normal vector that will result in
	 * minimal contact between the swept shape and the object that was hit. In this case, ImpactNormal will be the normal opposed to movement at that location
	 * (ie, Normal may not equal ImpactNormal). ImpactPoint will be the same as Location, since there is no single impact point to report.
	 */
	UPROPERTY(VisibleAnywhere)
	uint8 bStartPenetrating : 1;
	
	/**
	 * Physical material that was hit.
	 * @note Must set bReturnPhysicalMaterial on the swept PrimitiveComponent or in the query params for this to be returned.
	 */
	//UPROPERTY(VisibleAnywhere)
	//TWeakObjectPtr<class UPhysicalMaterial> PhysMaterial;

	/** Handle to the object hit by the trace. */
	UPROPERTY(VisibleAnywhere)
	FActorInstanceHandle HitObjectHandle;

	/** PrimitiveComponent hit by the trace. */
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<class UPrimitiveComponent> Component;

	/** Name of bone we hit (for skeletal meshes). */
	UPROPERTY(VisibleAnywhere)
	FName BoneName;

	/** Name of the _my_ bone which took part in hit event (in case of two skeletal meshes colliding). */
	UPROPERTY(VisibleAnywhere)
	FName MyBoneName;

	FHitResultVisiable(): FaceIndex(0), Time(0), Distance(0), PenetrationDepth(0), MyItem(0), Item(0), ElementIndex(0),
	                      bBlockingHit(0),
	                      bStartPenetrating(0)
	{
		HitObjectHandle = FActorInstanceHandle();
	}

	FHitResultVisiable& operator = (const FHitResult& HitResult);
	// {
	// 	FaceIndex = HitResult.FaceIndex;
	// 	Time = HitResult.Time;
	// 	Distance = HitResult.Distance;
	// 	Location = HitResult.Location;
	// 	ImpactPoint = HitResult.ImpactPoint;
	// 	Normal = HitResult.Normal;
	// 	ImpactNormal = HitResult.ImpactNormal;
	// 	TraceStart = HitResult.TraceStart;
	// 	TraceEnd = HitResult.TraceEnd;
	// 	PenetrationDepth = HitResult.PenetrationDepth;
	// 	MyItem = HitResult.MyItem;
	// 	Item = HitResult.Item;
	// 	ElementIndex = HitResult.ElementIndex;
	// 	bBlockingHit = HitResult.bBlockingHit;
	// 	bStartPenetrating = HitResult.bStartPenetrating;
	// 	PhysMaterial = HitResult.PhysMaterial;
	// 	HitObjectHandle = HitResult.HitObjectHandle;
	// 	Component = HitResult.Component;
	// 	BoneName = HitResult.BoneName;
	// 	MyBoneName = HitResult.MyBoneName;
	// 	
	// 	return *this;
	// }
};
