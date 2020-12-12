#include"../Components/DemoInputComponent.h"
#include "DemoEventHandler.h"


namespace ue
{
	DemoEventHandler::DemoEventHandler()
	{
	}

	void DemoEventHandler::OnKeyDown(const KeyInfo& keyDownInfo)
	{
		_input->CaptureKeyEvent(keyDownInfo);
	}

	void DemoEventHandler::OnKeyUp(const KeyInfo& keyUpInfo)
	{
		_input->CaptureKeyEvent(keyUpInfo);
	}

	void DemoEventHandler::OnMouseDown(const MouseInfo& mouseDownInfo)
	{
		_input->CaptureMouseEvent(mouseDownInfo);
	}

	void DemoEventHandler::OnMouseUp(const MouseInfo& mouseUpInfo)
	{
		_input->CaptureMouseEvent(mouseUpInfo);
	}

	void DemoEventHandler::OnMouseMove(const MouseInfo& mouseMoveInfo)
	{
		_input->CaptureMouseEvent(mouseMoveInfo);
	}

	void DemoEventHandler::OnMouseWheel(const MouseInfo& mouseWheelInfo)
	{
		_input->CaptureMouseEvent(mouseWheelInfo);
	}

	void DemoEventHandler::HandleBeforeFrame()
	{
	}

	void DemoEventHandler::HandleAfterFrame()
	{
		_input->ResetStates();
	}

	void DemoEventHandler::Init(uintptr_t state)
	{
		_input = this->GetService<DemoInputComponent>();
	}

}

