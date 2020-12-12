#pragma once

#include"Graphics/DX11/DX11MatrixShaderBase.h"

namespace ue
{
	class DX11ColorShader : public DX11MatrixShaderBase
	{
	public:
		DX11ColorShader();

		virtual void Init(uintptr_t state)override;
		virtual void Render(UINT indexCount);

	protected:
		bool _hasInit;
		ComPtr<ID3D11InputLayout> _layout;
	};
}