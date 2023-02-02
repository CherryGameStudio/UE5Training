#pragma once

// TODO 模板元编程知识补充，目前代码有问题。


template <typename Ret, typename ... Args>
class FunctionCommandBase
{
public:
	virtual ~FunctionCommandBase() {}
	virtual Ret operator() (Args...) = 0; 
};

/**
 * 函数指针，lambda
 */template <typename Functor, typename Ret, typename ... Args>
class FunctorCommand : public FunctionCommandBase<Ret, Args...>
{
public:
	FunctorCommand(Functor const& InFunctor)
		: MyFunc(InFunctor) {}

	FunctorCommand(Functor&& InFunctor)
		: MyFunc(std::move(InFunctor)) {}

	virtual Ret operator() (Args... InArgs) override
	{
		return MyFunc(std::forward<Args>(InArgs)...);
	}
	
private:
	Functor MyFunc;
};

/**
 * 成员函数指针
 */
template <typename Caller, typename CallerIndeed, typename Ret, typename ... Args>
class PMFCommand : public FunctionCommandBase<Ret, Args...>
{
public:
	using PMF = Ret(Caller::*)(Args...);

	PMFCommand(CallerIndeed InCaller, PMF InPMF)
		: LocalCaller(InCaller), MemberFunctionPoint(InPMF) {}

	virtual Ret operator() (Args... InArgs) override
	{
		return LocalCaller->*MemberFunctionPoint(std::forward<Args>(InArgs)...);
	}

private:
	CallerIndeed LocalCaller;
	PMF MemberFunctionPoint;
};

/**
 * 集成
*/
template<typename FuncType>
class MyTFunction;

template<typename Ret, typename ... Args>
class MyTFunction<Ret(Args...)>
{
public:
	template<typename Functor>
	MyTFunction(Functor const& InFunctor)
		: Command(new FunctorCommand<Functor, Ret, Args...>( std::forward<Functor>(InFunctor) ))
	{}

	template<typename Caller, typename CallerIndeed>
	MyTFunction(CallerIndeed InCaller, Ret(Caller::*InFunc)(Args...))
		: Command(new PMFCommand<Caller, CallerIndeed, Ret, Args...>(InCaller, InFunc))
	{}

	Ret operator() (Args... InArgs)
	{
		return Command(InArgs...);
	}

	~MyTFunction()
	{
		if (Command)
		{
			delete Command;
			Command = nullptr;
		}	
	}
	
private:
	FunctionCommandBase<Ret, Args...>* Command = nullptr;
};