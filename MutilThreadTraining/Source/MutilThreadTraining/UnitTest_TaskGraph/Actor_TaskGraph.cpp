// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_TaskGraph.h"

#include "TaskGraph_UnitTest.h"

// Sets default values
AActor_TaskGraph::AActor_TaskGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActor_TaskGraph::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_TaskGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/**
 *					   --->线程3--->
 *	线程1 ---> 线程2 --->		   --->线程5
 *					   --->线程4--->
 */
void AActor_TaskGraph::UnitTest1()
{
	FGraphEventRef GraphEvent1 = TGraphTask<FTaskGraph_UnitTest>::CreateTask().ConstructAndDispatchWhenReady(TEXT("线程1"));

	FGraphEventArray PrerequistesForThread2;
	PrerequistesForThread2.Add(GraphEvent1);
	FGraphEventRef GraphEvent2 = TGraphTask<FTaskGraph_UnitTest>::CreateTask(&PrerequistesForThread2).ConstructAndDispatchWhenReady(TEXT("线程2"));

	FGraphEventArray PrerequistesForThread3;
	PrerequistesForThread3.Add(GraphEvent2);
	FGraphEventRef GraphEvent3 = TGraphTask<FTaskGraph_UnitTest>::CreateTask(&PrerequistesForThread3).ConstructAndDispatchWhenReady(TEXT("线程3"));

	FGraphEventArray PrerequistesForThread4;
	PrerequistesForThread4.Add(GraphEvent2);
	FGraphEventRef GraphEvent4 = TGraphTask<FTaskGraph_UnitTest>::CreateTask(&PrerequistesForThread4).ConstructAndDispatchWhenReady(TEXT("线程4"));

	FGraphEventArray PrerequistesForThread5;
	PrerequistesForThread5.Add(GraphEvent3);
	PrerequistesForThread5.Add(GraphEvent4);
	FGraphEventRef GraphEvent5 = TGraphTask<FTaskGraph_UnitTest>::CreateTask(&PrerequistesForThread5).ConstructAndDispatchWhenReady(TEXT("线程5"));
}

