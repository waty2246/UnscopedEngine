#include"IServiceProvider.h"
#include "ServiceConsumer.h"

namespace ue
{
	extern IServiceProvider* CurrentServiceProvider = nullptr;

	IDisposable* ServiceConsumer::GetService(const std::string& serviceName)
	{
		return CurrentServiceProvider->GetService(serviceName);
	}
}

