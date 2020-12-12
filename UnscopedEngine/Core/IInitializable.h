#pragma once

#include<cstdint>
#include"IDisposable.h"

//Mark current reinitialize state inside an initializable class as not process when Init method has called.
#define INITIALIZE_IGNORED_STATE uintptr_t(0)

//Mark the first initialize state inside an initializable class as not process.
#define INITIALIZE_UNITTESTS_STATE uintptr_t(1)

namespace ue
{
	/// <summary>
	/// Base class for component that need initialization before used.
	/// </summary>
	class IInitializable : public IDisposable
	{
	public:
		virtual void Init(uintptr_t state) = 0;
	};
}