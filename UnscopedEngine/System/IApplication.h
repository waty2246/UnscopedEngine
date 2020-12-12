#pragma once

#include"Core/IInitializable.h"

namespace ue
{
	class IApplication : public IInitializable
	{
	public:
		/// <summary>
		/// Called when there is no available event to begin processing application logic and render scene.
		/// </summary>
		/// <returns>
		/// true - to continue processing
		/// false - to exit application
		/// </returns>
		virtual bool Frame() = 0;
	};
}