#pragma once

#include"Core/IDisposable.h"

namespace ue
{
	class MockService : public IDisposable
	{
	public:
		MockService();
		virtual ~MockService();
	private:
		int* _data;
	};
}


