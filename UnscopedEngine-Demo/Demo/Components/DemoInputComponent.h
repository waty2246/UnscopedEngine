#pragma once

#include"Core/ServiceConsumer.h"
#include"Graphics/Point.h"
#include"System/IEventHandler.h"
#include"System/IWindow.h"

namespace ue
{
	class DemoInputComponent :public IInitializable,public ServiceConsumer
	{
	public:
		DemoInputComponent();

		virtual void Init(uintptr_t state)override;

		void Update();

		bool IsTerminateTrigger();

		bool IsMoveLeft();
		bool IsMoveRight();
		bool IsMoveForward();
		bool IsMoveBackward();

		bool IsLookLeft();
		bool IsLookRight();
		bool IsLookUp();
		bool IsLookDown();
	private:
		void CaptureMouseEvent(const MouseInfo& mouseInfo);
		void CaptureKeyEvent(const KeyInfo& keyInfo);
		void ResetStates();

	private:
		bool _hasInit;
		MouseInfo _mouseInfo;

		std::unique_ptr<bool[]> _keyState;

		ServicePtr<IWindow> _window;

		friend class DemoEventHandler;
	};
}
