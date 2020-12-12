#pragma once

#include<string>
#include"IDisposable.h"

namespace ue
{
	class IServiceProvider
	{
	public:
		virtual IDisposable* GetService(const std::string& serviceName) = 0;

		virtual ~IServiceProvider(){}
	};
}