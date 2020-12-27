#pragma once

#include"DX11Common.h"
#include"Core/IInitializable.h"
#include"Graphics/Core/IRenderObject.h"
#include"Core/ServiceConsumer.h"

namespace ue
{
	class DX11RenderObjectBase : public IRenderObject,public ServiceConsumer
	{
	public:
		virtual void Init(uintptr_t state) override;

	protected:
		ServicePtr<ID3D11Device> _device;
		ServicePtr<ID3D11DeviceContext> _deviceContext;

		ComPtr<ID3D11Buffer> _vertexBuffer;
		ComPtr<ID3D11Buffer> _indexBuffer;
	};
}