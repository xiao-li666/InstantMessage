#pragma once
#include <memory>

template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	Singleton(const Singleton<T>&) = delete;
	Singleton& operator=(const Singleton<T>&) = delete;

public:
	~Singleton() {}
	
	static std::shared_ptr<T> GetInstance()
	{
		static std::shared_ptr<T> instance = std::shared_ptr<T>(new T);
		return instance;
	}
};
