#pragma once

#include"System/IEventHandler.h"
#include"Core/ServiceConsumer.h"

namespace ue
{
	class DemoEventHandler : public IEventHandler,public ServiceConsumer
	{
	public:
		DemoEventHandler();

		virtual void Init(uintptr_t state) override;

		virtual void OnKeyDown(const KeyInfo& keyDownInfo) override;

		virtual void OnKeyUp(const KeyInfo& keyUpInfo) override;

		virtual void OnMouseDown(const MouseInfo& mouseDownInfo) override;

		virtual void OnMouseUp(const MouseInfo& mouseUpInfo) override;

		virtual void OnMouseMove(const MouseInfo& mouseMoveInfo) override;

		virtual void OnMouseWheel(const MouseInfo& mouseWheelInfo) override;

		virtual void HandleBeforeFrame() override;
		virtual void HandleAfterFrame() override;

	private:
		ServicePtr<DemoInputComponent> _input;
	};
}


