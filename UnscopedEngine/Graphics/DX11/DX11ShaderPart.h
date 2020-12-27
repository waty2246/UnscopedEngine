#pragma once

#include"DX11Common.h"
#include"Core/IInitializable.h"
#include"Core/ServiceConsumer.h"
#include"Components/CameraComponent.h"

namespace ue
{
	class DX11ShaderPart :public IInitializable, public ServiceConsumer
	{
	public:
		virtual void Init(uintptr_t state) override;

	protected:
		ServicePtr<ID3D11Device> _device;
		ServicePtr<ID3D11DeviceContext> _deviceContext;
	};

	struct MatrixConstBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX wvp;
	};

	class DX11MatrixShaderPart : public DX11ShaderPart
	{
	public:
		virtual void Init(uintptr_t state)override;
		virtual void RenderMatrix(bool isOrtho = false);

	private:
		ServicePtr<CameraComponent> _camera;
		ComPtr<ID3D11Buffer> _matrixBuffer;
	};
}
