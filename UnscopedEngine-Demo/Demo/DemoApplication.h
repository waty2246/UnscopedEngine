#pragma once

#include"System/IApplication.h"
#include"Components/CameraComponent.h"
#include"Graphics/Core/IRenderObject.h"
#include"Graphics/Core/IGraphicsController.h"
#include"Components/TimerComponent.h"
#include"Components/DemoInputComponent.h"
#include"System/IFlexibleWindow.h"
#include"Components/MovementComponent.h"

namespace ue
{
	class DemoApplication: public IApplication,public ServiceConsumer
	{
	public:
		DemoApplication();

		virtual void Init(uintptr_t state) override;

		virtual bool Update() override;
	private:
		void ReportFrameRate();
		void Render();

		bool _hasInit;
		int _frameCount;
		double _frameTime;
		std::wstring _windowTitle;

		ServicePtr<IGraphicsController> _graphics;
		ServicePtr<CameraComponent> _camera;
		ServicePtr<TimerComponent> _timer;
		ServicePtr<DemoInputComponent> _input;
		ServicePtr<IFlexibleWindow> _window;

		std::unique_ptr< MovementComponent> _movementComponent;

		std::unique_ptr<IRenderObject> _scene;
	};
}


