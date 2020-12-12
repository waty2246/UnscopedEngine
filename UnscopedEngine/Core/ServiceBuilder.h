#pragma once

#include"Common.h"
#include"IServiceProvider.h"

namespace ue
{
	class ServiceBuilder
	{
		friend class SystemController;
	public:
		template<typename ServiceType>
		ServiceBuilder* AddService(IDisposable* instance)
		{
			if (_hasBuild)
			{
				throw std::exception("Invalid ServiceBuilder::AddService method invocation.");
			}

			return AddService(typeid(ServiceType).name(), instance);
		}

		~ServiceBuilder();
	private:
		ServiceBuilder();

		ServiceBuilder* AddService(const char* serviceName, IDisposable* instance);
		void Build();
		
	private:
		std::unique_ptr<IServiceProvider> _serviceProvider;
		bool _hasBuild;

	};
}



