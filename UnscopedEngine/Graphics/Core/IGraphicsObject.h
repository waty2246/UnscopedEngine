#pragma once

#include"Core/IInitializable.h"

namespace ue
{
	class IGraphicsObject : public IInitializable
	{
	public:
		virtual void Frame() = 0;
		virtual void Render() = 0;
	};
}