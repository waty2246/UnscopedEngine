#pragma once

#include"Common.h"
#include"IDisposable.h"

namespace ue
{
	enum InitializeState : uintptr_t
	{
		UNSPECIFIED=0,	// The Current state when invoke IInitializable::Init is unspecified
		UNIT_TEST=1,	// The current state when invoke IInitializable::Init is inside a unit test
	};

	/// <summary>
	/// Base class for component that need initialization before used.
	/// </summary>
	class IInitializable : public IDisposable
	{
	public:
		virtual void Init(uintptr_t state) = 0;
	};
}