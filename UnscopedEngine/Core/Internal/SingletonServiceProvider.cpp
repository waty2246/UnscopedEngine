#include "SingletonServiceProvider.h"

namespace ue
{
	void SingletonServiceProvider::AddService(const char* serviceName, IDisposable* instance)
	{
		_container.insert({ serviceName,std::unique_ptr<IDisposable>(instance) });
	}

	IDisposable* SingletonServiceProvider::GetService(const std::string& serviceName)
	{
		return _container.at(serviceName).get();
	}

	SingletonServiceProvider::~SingletonServiceProvider()
	{
	}
}

