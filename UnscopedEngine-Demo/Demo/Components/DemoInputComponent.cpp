#include "DemoInputComponent.h"

namespace ue
{
	DemoInputComponent::DemoInputComponent():
		_hasInit(false),
		_keyState(std::make_unique<bool[]>(255)),
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

	void DemoInputComponent::Update()
	{
	}

	bool DemoInputComponent::IsTerminateTrigger()
	{
		return _keyState[KeyCode::ESCAPE];
	}

	bool DemoInputComponent::IsMoveLeft()
	{
		return _keyState[KeyCode::A];
	}

	bool DemoInputComponent::IsMoveRight()
	{
		return _keyState[KeyCode::D];
	}

	bool DemoInputComponent::IsMoveForward()
	{
		return _keyState[KeyCode::W];
	}

	bool DemoInputComponent::IsMoveBackward()
	{
		return _keyState[KeyCode::S];
	}

	bool DemoInputComponent::IsLookLeft()
	{
		return _keyState[KeyCode::LEFT];
	}

	bool DemoInputComponent::IsLookRight()
	{
		return _keyState[KeyCode::RIGHT];
	}

	bool DemoInputComponent::IsLookUp()
	{
		return _keyState[KeyCode::UP];
	}

	bool DemoInputComponent::IsLookDown()
	{
		return _keyState[KeyCode::DOWN];
	}

	void DemoInputComponent::CaptureMouseEvent(const MouseInfo& mouseInfo)
	{
		_mouseInfo = mouseInfo;
	}

	void DemoInputComponent::CaptureKeyEvent(const KeyInfo& keyInfo)
	{
		_keyState[keyInfo.GetKeyCode()] = keyInfo.IsDown();
	}

	void DemoInputComponent::ResetStates()
	{
		_mouseInfo = { MouseButton::UNKNOWN,_mouseInfo.GetMousePositionX(),_mouseInfo.GetMousePositionY(),0 };
	}
}

