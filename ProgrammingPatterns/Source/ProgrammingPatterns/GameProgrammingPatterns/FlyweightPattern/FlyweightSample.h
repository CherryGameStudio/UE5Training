#pragma once

// 内蕴对象，对象个数少，内存占用大，可以重复利用的
class Website
{
public:
	Website(FString InName)
		: Name(InName)
	{}

	FString GetName() { return Name; }
	
private:
	FString Name;

	//... 一系列数据
};

// 内蕴对象池
class WebsitePool
{
public:
	static Website* GetWebsite(FString WebsiteName)
	{
		static TMap<FString, Website*> S_WebSitePool;
		if (Website* OldWebsite = S_WebSitePool.FindRef(WebsiteName))
		{
			return OldWebsite;
		}

		Website* NewWebsite = new Website(WebsiteName);
		S_WebSitePool.Add(WebsiteName ,NewWebsite);
		UE_LOG(LogTemp, Log, TEXT("创建了Website：%s"), *WebsiteName);
		return NewWebsite;
	}
};

// 外蕴对象，每个对象必须独一
class User
{
public:
	User(int32 InUserID)
		: UserID(InUserID)
	{}
	
	int32 GetID() { return UserID; }
	
private:
	int32 UserID;
};


// 实际享元对象，内蕴对象在池内共享，外蕴对象各自独立
class FlyweightObject
{
public:
	FlyweightObject(int32 InUserID, FString WebsiteName)
	{
		MyUser = new User(InUserID);
		MyWebsite = WebsitePool::GetWebsite(WebsiteName);
	}

	~FlyweightObject()
	{
		if (MyUser)
		{
			delete MyUser;
			MyUser = nullptr;
		}

		UE_LOG(LogTemp, Log, TEXT("~FlyweightObject()"));
	}

	void Print() const
	{
		UE_LOG(LogTemp, Log, TEXT("UserID: %d, Name: %s"), MyUser->GetID(), *MyWebsite->GetName());
	}
	
private:
	User* MyUser;
	Website* MyWebsite;
};