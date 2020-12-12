#pragma once

#include"Common.h"
#include"Core/IServiceProvider.h"

namespace ue
{
	extern IServiceProvider* CurrentServiceProvider;

	/// <summary>
	/// A default implementation ServiceProvider for the application.
	/// </summary>
	class SingletonServiceProvider : public IServiceProvider
	{
		friend class ServiceBuilder;
	public:
		virtual IDisposable* GetService(const std::string& serviceName)override;

		~SingletonServiceProvider();
	private:
		SingletonServiceProvider() {}
		void AddService(const char* serviceName, IDisposable* instance);

	private:
		std::unordered_map<std::string, std::unique_ptr<IDisposable>> _container;

	};
}