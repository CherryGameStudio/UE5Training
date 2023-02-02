#pragma once

/**
 * 优点：实现简单，利用C++动态实现分派和内存布局。
 * 缺点：因为OOD，新命令的实现必须继承自ICommand，不够灵活。
 */
class ICommand
{
public:
	virtual ~ICommand() = default;
	bool TryExecute()
	{
		if (CanExecute())
		{
			Execute();
			return true;
		}

		return false;
	}
	virtual void UnDo() = 0;
	
protected:
	virtual void Execute() = 0;
	virtual bool CanExecute() = 0;
	
};

class TransformCommand : public ICommand
{
public:
	TransformCommand(AActor* TargetActor, FTransform TargetTransform);
	virtual void UnDo() override;
	
protected:
	virtual void Execute() override;
	virtual bool CanExecute() override;

private:
	AActor* MyActor;
	FTransform MyTransform;
	FTransform MyLastTrans;
};