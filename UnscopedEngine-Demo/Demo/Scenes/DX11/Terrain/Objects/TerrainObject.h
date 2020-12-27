#pragma once

#include"../Models/TerrainModel.h"
#include"../Shaders/DX11TerrainShader.h"
#include"Graphics/DX11/DX11Texture2D.h"
#include"Graphics/DX11/DX11RenderObjectBase.h"

namespace ue
{
	class TerrainObject : public DX11RenderObjectBase
	{
	public:
		TerrainObject(std::string terrainHeightMap);

		virtual void Init(uintptr_t state) override;
		virtual void Update()override;
		virtual void Render() override;

	private:
		bool _hasInit;
		std::unique_ptr<TerrainModel> _model;
		std::unique_ptr<DX11IndexDrawShader> _shader;
	};
}