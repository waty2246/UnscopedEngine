#pragma once

#include"Graphics/DX11/DX11MatrixShaderBase.h"

namespace ue
{
	class DX11TextureShader : public DX11MatrixShaderBase
	{
	public:
		DX11TextureShader();

		virtual void Init(uintptr_t state)override;
		virtual void Render(UINT indexCount, ID3D11ShaderResourceView* texture, ID3D11SamplerState* samplerState);

	protected:
		bool _hasInit;
		ComPtr<ID3D11InputLayout> _layout;
	};
}