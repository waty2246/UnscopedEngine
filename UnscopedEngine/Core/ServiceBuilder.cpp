#include"Core/Internal/SingletonServiceProvider.h"
#include "ServiceBuilder.h"

namespace ue
{
	ServiceBuilder::ServiceBuilder():_hasBuild(false),_serviceProvider(new SingletonServiceProvider())
	{
	}

	ServiceBuilder::~ServiceBuilder()
	{
		CurrentServiceProvider = nullptr;
	}

	ServiceBuilder* ServiceBuilder::AddService(const char* serviceName, IDisposable* instance)
	{
		static_cast<SingletonServiceProvider*>(_serviceProvider.get())->AddService(serviceName, instance);
		return this;
	}

	void ServiceBuilder::Build()
	{
		if (_hasBuild)
		{
			throw std::exception("Invalid ServiceBuilder::Build method invocation.");
		}
		
		_hasBuild = true;

		CurrentServiceProvider = _serviceProvider.get();
	}
}
