#pragma once

#include"DX11ShaderBase.h"
#include"Components/CameraComponent.h"

namespace ue
{
	struct MatrixCBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX wvp;
	};

	class DX11MatrixShaderBase : public DX11ShaderBase
	{
	public:
		virtual void Init(uintptr_t state)override;

	protected:
		virtual void RenderMatrix(bool isOrtho=false);

	protected:
		ServicePtr<CameraComponent> _camera;
		ComPtr<ID3D11Buffer> _matrixBuffer;
	};
}