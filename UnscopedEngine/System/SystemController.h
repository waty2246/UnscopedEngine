#pragma once

#include"Common.h"
#include"IWindow.h"
#include"IEventHandler.h"
#include"Core/ServiceBuilder.h"
#include"Core/ServiceConsumer.h"
#include"IApplication.h"
#include"Components/TimerComponent.h"

namespace ue
{
	class SystemController :public IEventHandler,public ServiceConsumer
	{
	public:
		SystemController();

		virtual void Init(uintptr_t state = InitializeState::UNSPECIFIED)override;
		virtual void Run(IEventHandler* eventHandler=nullptr);
		ServiceBuilder* GetServiceBuilder()const;
		virtual void OnKeyDown(const KeyInfo& keyDownInfo) override;
		virtual void OnKeyUp(const KeyInfo& keyUpInfo) override;
		virtual void OnMouseDown(const MouseInfo& mouseDownInfo) override;
		virtual void OnMouseUp(const MouseInfo& mouseUpInfo) override;
		virtual void OnMouseMove(const MouseInfo& mouseMoveInfo) override;
		virtual void OnMouseWheel(const MouseInfo& mouseWheelInfo) override;
		virtual void HandleBeforeFrame() override;
		virtual void HandleAfterFrame() override;

		virtual ~SystemController();

	private:
		bool Update();

	private:
		bool _hasInit;
		size_t _lastState;
		std::unique_ptr<ServiceBuilder> _serviceBuilder;

		ServicePtr<IWindow> _window;
		ServicePtr<IApplication> _application;
		ServicePtr<TimerComponent> _timer;
	};
}


