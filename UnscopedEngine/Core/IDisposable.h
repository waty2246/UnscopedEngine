#pragma once

namespace ue
{
	/// <summary>
	/// Base class for service implementation when register with service builder.
	/// </summary>
	class IDisposable
	{
	public:
		virtual ~IDisposable(){}
	};
}