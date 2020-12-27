#include<windowsx.h>
#include "SystemController.h"

namespace ue
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static IEventHandler* CurrentEventHandler = nullptr;

	SystemController::SystemController():
		_serviceBuilder(new ServiceBuilder()),
		_application(nullptr),_window(nullptr),
		_lastState(InitializeState::UNSPECIFIED),
		_hasInit(false)
	{
	}

	void SystemController::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		_lastState = state;
		_serviceBuilder->Build();

		//Ignore Unit Tests
		if (InitializeState::UNIT_TEST == state)
		{
			return;
		}

		CurrentEventHandler = this;

		_application = this->GetService<IApplication>();
		_window = this->GetService<IWindow>();
		_timer= this->GetService<TimerComponent>();

		//Window must be initialize firstly
		_window->Init(reinterpret_cast<uintptr_t>(WndProc));

		//Init Timer
		_timer->Init(state);

		//Init Application
		_application->Init(state);
	}

	void SystemController::Run(IEventHandler* eventHandler)
	{
		MSG msg = { 0 };
		bool done = false;

		if (eventHandler != nullptr)
		{
			CurrentEventHandler = eventHandler;
		}
		
		CurrentEventHandler->Init(_lastState);
		_window->ShowWindow();
		_timer->Start();
		while (!done)
		{
			if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			if (WM_QUIT == msg.message)
			{
				done = true;
			}
			else
			{
				//Before frame processing handle
				CurrentEventHandler->HandleBeforeFrame();

				//Calculate frame time
				_timer->Tick();

				if (!Update())
				{
					done = true;
				}

				//After frame proccessing handle
				CurrentEventHandler->HandleAfterFrame();
			}
		}
	}

	ServiceBuilder* SystemController::GetServiceBuilder() const
	{
		return _serviceBuilder.get();
	}

	SystemController::~SystemController()
	{
	}

	bool SystemController::Update()
	{
		return _application->Update();
	}

	void SystemController::OnKeyDown(const KeyInfo& keyDownInfo)
	{
	}

	void SystemController::OnKeyUp(const KeyInfo& keyUpInfo)
	{
	}

	void SystemController::OnMouseDown(const MouseInfo& mouseDownInfo)
	{
	}

	void SystemController::OnMouseUp(const MouseInfo& mouseUpInfo)
	{
	}

	void SystemController::OnMouseMove(const MouseInfo& mouseMoveInfo)
	{
	}

	void SystemController::OnMouseWheel(const MouseInfo& mouseWheelInfo)
	{
	}

	void SystemController::HandleBeforeFrame()
	{
	}

	void SystemController::HandleAfterFrame()
	{
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}

			case WM_CLOSE:
			{
				DestroyWindow(hwnd);
				return 0;
			}
			case WM_KEYDOWN:
			{
				KeyInfo keyInfo{ static_cast<KeyCode>(wParam) };
				CurrentEventHandler->OnKeyDown(keyInfo);
				return 0;
			}
			case WM_KEYUP:
			{
				KeyInfo keyInfo{ static_cast<KeyCode>(wParam),false };
				CurrentEventHandler->OnKeyUp(keyInfo);
				return 0;
			}
			case WM_MOUSEHWHEEL:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				MouseButton mouseButton = MouseButton::NONE;
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_LBUTTON:mouseButton = MouseButton::LEFT;
				case MK_MBUTTON:mouseButton = MouseButton::MIDDLE;
				case MK_RBUTTON:mouseButton = MouseButton::RIGHT;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseWheelInfo{ mouseButton, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA,keyCode };
				CurrentEventHandler->OnMouseWheel(mouseWheelInfo);
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				MouseButton mouseButton = MouseButton::NONE;
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_LBUTTON:mouseButton = MouseButton::LEFT;
				case MK_MBUTTON:mouseButton = MouseButton::MIDDLE;
				case MK_RBUTTON:mouseButton = MouseButton::RIGHT;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ mouseButton, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseMove(mouseMoveInfo);
				return 0;
			}
			case WM_MBUTTONDOWN:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::MIDDLE, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			case WM_LBUTTONDOWN:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::LEFT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::RIGHT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			case WM_LBUTTONUP:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::LEFT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseUp(mouseMoveInfo);
				return 0;
			}
			case WM_MBUTTONUP:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::MIDDLE, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseUp(mouseMoveInfo);
				return 0;
			}
			case WM_RBUTTONUP:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::RIGHT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode };
				CurrentEventHandler->OnMouseUp(mouseMoveInfo);
				return 0;
			}
			case WM_LBUTTONDBLCLK:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::LEFT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode,true };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			case WM_MBUTTONDBLCLK:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::MIDDLE, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode,true };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			case WM_RBUTTONDBLCLK:
			{
				auto keyDown = GET_KEYSTATE_WPARAM(wParam);
				KeyCode keyCode = KeyCode::NONE;
				switch (keyDown)
				{
				case MK_CONTROL:keyCode = KeyCode::CONTROL;
				case MK_SHIFT:keyCode = KeyCode::SHIFT;
				}

				MouseInfo mouseMoveInfo{ MouseButton::RIGHT, GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam),0,keyCode,true };
				CurrentEventHandler->OnMouseDown(mouseMoveInfo);
				return 0;
			}
			default:
			{
				return DefWindowProc(hwnd, msg, wParam, lParam);
			}
		}
	}
}

