#pragma once

#include"DX11ShaderBase.h"

namespace ue
{
	class DX11IndexDrawShader :public DX11ShaderBase
	{
	public:
		virtual void Render(UINT indexCount)=0;
	};
}