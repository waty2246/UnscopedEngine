#pragma once

#include"Graphics/Core/IRenderObject.h"
#include"Core/ServiceConsumer.h"
#include"Graphics/Core/IGraphicsController.h"
#include"Objects/DX11TextureObject.h"

namespace ue
{
	class TextureScene : public IRenderObject,public ServiceConsumer
	{
	public:
		TextureScene();

		virtual void Init(uintptr_t state) override;

		virtual void Update() override;

		virtual void Render() override;

	private:
		ServicePtr<IGraphicsController> _graphics;
		std::unique_ptr<TextureObject> _textureObject;

	};
}