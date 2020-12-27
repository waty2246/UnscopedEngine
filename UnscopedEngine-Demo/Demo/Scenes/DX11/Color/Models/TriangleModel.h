#pragma once

#include"PolygonModel.h"

namespace ue
{
	class TriangleModel :public PolygonModel
	{
	public:
		void Init(uintptr_t state = InitializeState::UNSPECIFIED) override;
	};
}