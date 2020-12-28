#pragma once

#include"Graphics/Core/IRenderObject.h"
#include"Core/ServiceConsumer.h"
#include"Graphics/Core/IGraphicsController.h"
#include"Objects/TerrainObject.h"

namespace ue
{
	class TerrainScene :public IRenderObject, public ServiceConsumer
	{
	public:
		TerrainScene();

		virtual void Init(uintptr_t state) override;

		virtual void Update() override;

		virtual void Render() override;

	private:
		ServicePtr<IGraphicsController> _graphics;
		std::unique_ptr<TerrainObject> _terrainObject;

	};
}