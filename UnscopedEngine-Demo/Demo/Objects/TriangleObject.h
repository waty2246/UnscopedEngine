#pragma once

#include"../Models/TriangleModel.h"
#include"../Shaders/DX11ColorShader.h"
#include"Graphics/DX11/DX11ObjectBase.h"

namespace ue
{
	class TriangleObject : public DX11ObjectBase
	{
	public:
		TriangleObject();

		virtual void Init(uintptr_t state) override;
		virtual void Frame()override;
		virtual void Render() override;
	private:
		bool _hasInit;
		std::unique_ptr<TriangleModel> _model;
		std::unique_ptr<DX11ColorShader> _shader;
	};
}