#pragma once

#include"Graphics/DX11/DX11IndexDrawShader.h"

namespace ue
{
	class DX11TerrainShader :public DX11IndexDrawShader
	{
	public:
		DX11TerrainShader();

		virtual void Init(uintptr_t state)override;
		virtual void Render(UINT indexCount);

	protected:
		bool _hasInit;
		ComPtr<ID3D11InputLayout> _layout;
		std::unique_ptr<DX11MatrixShaderPart> _matrixShaderPart;
	};
}