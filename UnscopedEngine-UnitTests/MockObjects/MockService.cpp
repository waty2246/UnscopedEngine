#include "MockService.h"

namespace ue
{
	MockService::MockService() :_data(new int[100])
	{
	}

	MockService::~MockService()
	{
		delete[] _data;
	}
}
