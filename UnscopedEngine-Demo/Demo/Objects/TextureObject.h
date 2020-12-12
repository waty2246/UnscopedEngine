#pragma once

#include"../Models/TextureModel.h"
#include"../Shaders/DX11TextureShader.h"
#include"Graphics/DX11/DX11Texture2D.h"
#include"Graphics/DX11/DX11ObjectBase.h"

namespace ue
{
	class TextureObject : public DX11ObjectBase
	{
	public:
		TextureObject();

		virtual void Init(uintptr_t state) override;
		virtual void Frame()override;
		virtual void Render() override;

	private:
		bool _hasInit;
		std::unique_ptr<TextureModel> _model;
		std::unique_ptr<DX11TextureShader> _shader;
		std::unique_ptr<DX11Texture2D> _texture2D;
		ComPtr<ID3D11SamplerState> _samplerState;
	};
}