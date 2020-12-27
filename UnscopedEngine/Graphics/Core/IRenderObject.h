#pragma once


#include"Core/IInitializable.h"

namespace ue
{
	/// <summary>
	/// Handle logic, effect and draw
	/// </summary>

	class IRenderObject : public IInitializable
	{
	public:
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}