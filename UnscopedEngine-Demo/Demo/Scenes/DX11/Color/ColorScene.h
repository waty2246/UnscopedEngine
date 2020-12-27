#pragma once

#include"Common.h"
#include"Graphics/Core/IRenderObject.h"
#include"Shaders/DX11ColorShader.h"
#include"Objects/DX11PolygonObject.h"

namespace ue
{
	class ColorScene : public IRenderObject
	{
	public:
		ColorScene();

		virtual void Init(uintptr_t state) override;

		virtual void Update() override;

		virtual void Render() override;

	private:
		std::unique_ptr<DX11PolygonObject<TriangleModel, DX11ColorShader>> _triangleObject;
	};
}