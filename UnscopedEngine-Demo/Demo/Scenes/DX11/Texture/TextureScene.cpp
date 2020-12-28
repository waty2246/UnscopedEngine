#include "TextureScene.h"

namespace ue
{
	TextureScene::TextureScene():
		_textureObject(std::make_unique<TextureObject>())
	{
	}

	void TextureScene::Init(uintptr_t state)
	{
		_graphics = this->GetService<IGraphicsController>();
		_textureObject->Init(state);
	}

	void TextureScene::Update()
	{
		_textureObject->Update();
	}

	void TextureScene::Render()
	{
		_textureObject->Render();
	}
}

