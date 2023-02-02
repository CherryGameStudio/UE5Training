#include "EasyCommand.h"

TransformCommand::TransformCommand(AActor* TargetActor, FTransform TargetTransform)
{
	MyActor = TargetActor;
	MyTransform = TargetTransform;
}

void TransformCommand::Execute()
{
	MyLastTrans = MyActor->GetActorTransform();
	MyActor->SetActorTransform(MyTransform);
}

bool TransformCommand::CanExecute()
{
	if (MyActor && MyTransform.IsValid())
	{
		return true;
	}

	return false;
}

void TransformCommand::UnDo()
{
	MyActor->SetActorTransform(MyLastTrans);
}
