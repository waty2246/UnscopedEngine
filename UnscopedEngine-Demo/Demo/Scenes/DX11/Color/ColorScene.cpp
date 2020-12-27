#include "ColorScene.h"

namespace ue
{
	ColorScene::ColorScene():
		_triangleObject(std::make_unique<DX11PolygonObject<TriangleModel, DX11ColorShader>>())
	{
	}

	void ColorScene::Init(uintptr_t state)
	{
		_triangleObject->Init(state);
	}

	void ColorScene::Update()
	{
		_triangleObject->Update();
	}

	void ColorScene::Render()
	{
		_triangleObject->Render();
	}
}

