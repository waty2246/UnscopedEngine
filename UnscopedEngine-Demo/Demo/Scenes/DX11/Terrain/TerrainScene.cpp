#include "TerrainScene.h"

namespace ue
{
	TerrainScene::TerrainScene() :
		_terrainObject(std::make_unique<TerrainObject>("Resources\\Assets\\heightmap.bmp"))
	{
	}

	void TerrainScene::Init(uintptr_t state)
	{
		_graphics = this->GetService<IGraphicsController>();
		_terrainObject->Init(state);
	}

	void TerrainScene::Update()
	{
		_terrainObject->Update();
	}

	void TerrainScene::Render()
	{
		_graphics->TurnOnWireframe();
		_terrainObject->Render();
		_graphics->TurnOffWireframe();
	}

}
