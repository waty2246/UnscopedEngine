#include "DemoInputComponent.h"

namespace ue
{
	DemoInputComponent::DemoInputComponent():
		_hasInit(false),
		_mouseX(0),
		_mouseY(0),
		_keyInfo(KeyCode::NONE, false),
		_mouseInfo(MouseButton::NONE, 0, 0, 0)
	{
	}

	void DemoInputComponent::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		_window = this->GetService<IWindow>();
	}

	void DemoInputComponent::Frame()
	{
	}

	bool DemoInputComponent::IsTerminateTrigger()
	{
		return _keyInfo.IsDown() && _keyInfo.GetKeyCode() == KeyCode::ESCAPE;
	}

	bool DemoInputComponent::IsMoveLeft()
	{
		return _keyInfo.IsDown() && _keyInfo.GetKeyCode() == KeyCode::A;
	}

	bool DemoInputComponent::IsMoveRight()
	{
		return _keyInfo.IsDown() && _keyInfo.GetKeyCode() == KeyCode::D;
	}

	bool DemoInputComponent::IsMoveForward()
	{
		return _keyInfo.IsDown() && _keyInfo.GetKeyCode() == KeyCode::W;
	}

	bool DemoInputComponent::IsMoveBackward()
	{
		return _keyInfo.IsDown() && _keyInfo.GetKeyCode() == KeyCode::S;
	}

	bool DemoInputComponent::IsLookLeft()
	{
		return false;
	}

	bool DemoInputComponent::IsLookRight()
	{
		return false;
	}

	bool DemoInputComponent::IsLookUp()
	{
		return false;
	}

	bool DemoInputComponent::IsLookDown()
	{
		return false;
	}

	void DemoInputComponent::CaptureMouseEvent(const MouseInfo& mouseInfo)
	{
		_mouseInfo = mouseInfo;
		_mouseX = mouseInfo.GetMousePositionX();
		_mouseY = mouseInfo.GetMousePositionY();
	}

	void DemoInputComponent::CaptureKeyEvent(const KeyInfo& keyInfo)
	{
		_keyInfo = keyInfo;
	}

	void DemoInputComponent::ResetStates()
	{
		_keyInfo = { KeyCode::UNKNOWN,false };
		_mouseInfo = { MouseButton::UNKNOWN,_mouseInfo.GetMousePositionX(),_mouseInfo.GetMousePositionY(),0 };
	}
}

