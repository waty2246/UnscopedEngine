#pragma once

#include"Graphics/Core/IRenderObject.h"
#include"Objects/TerrainObject.h"

namespace ue
{
	class TerrainScene :public IRenderObject
	{
	public:
		TerrainScene();

		virtual void Init(uintptr_t state) override;

		virtual void Update() override;

		virtual void Render() override;

	private:
		std::unique_ptr<TerrainObject> _terrainObject;

	};
}