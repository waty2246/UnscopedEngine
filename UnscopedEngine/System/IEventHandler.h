#pragma once
#include"Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	enum class KeyCode
	{
		NONE = 0,
		SHIFT = VK_SHIFT,
		ALT = VK_MENU,
		CONTROL = VK_CONTROL,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,
		UP = VK_UP,
		DOWN = VK_DOWN,
		ENTER = VK_RETURN,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, GetX, GetY, Z,
		F1 = VK_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		ESCAPE = VK_ESCAPE,
		UNKNOWN = 999
	};

	enum class MouseButton
	{
		NONE = 0,
		LEFT = MK_LBUTTON,
		MIDDLE = MK_MBUTTON,
		RIGHT = MK_RBUTTON,
		UNKNOWN=999
	};

	class KeyInfo
	{
	public:
		inline KeyInfo(KeyCode keyCode, bool isDown = true) :_keyCode(keyCode), _isDown(isDown)
		{
		}

		inline KeyInfo(const KeyInfo&other) : _keyCode(other._keyCode), _isDown(other._isDown)
		{
		}

		const KeyInfo& operator=(const KeyInfo& other)
		{
			_keyCode=other._keyCode;
			_isDown=other._isDown;
			return *this;
		}

		inline KeyCode GetKeyCode() const
		{
			return _keyCode;
		}

		inline bool IsDown() const
		{
			return _isDown;
		}
	private:
		KeyCode _keyCode;
		bool _isDown;
	};

	class MouseInfo
	{
	public:
		inline MouseInfo(MouseButton mouseButton, int mousePositionX, int mousePositionY,int wheelDistance, KeyCode keyDownInfo = KeyCode::NONE, bool isDoubleClicked = false) :
			_mouseButton(mouseButton), _mousePositionX(mousePositionX), _mousePositionY(mousePositionY),
			_keyDownInfo(keyDownInfo), _isDoubleClicked(isDoubleClicked), _wheelDistance(wheelDistance)
		{
		}

		inline MouseInfo(const MouseInfo& other): 
			_mouseButton(other._mouseButton), _mousePositionX(other._mousePositionX), _mousePositionY(other._mousePositionY),
			_keyDownInfo(other._keyDownInfo), _isDoubleClicked(other._isDoubleClicked), _wheelDistance(other._wheelDistance)
		{
		}

		const MouseInfo& operator=(const MouseInfo& other)
		{
			_mouseButton = other._mouseButton;
			_mousePositionX=other._mousePositionX;
			_mousePositionY=other._mousePositionY;
			_keyDownInfo=other._keyDownInfo;
			_isDoubleClicked=other._isDoubleClicked;
			_wheelDistance = other._wheelDistance;
			return *this;				
		}

		inline MouseButton GetMouseButton() const
		{
			return _mouseButton;
		}

		inline int GetMousePositionX() const
		{
			return _mousePositionX;
		}

		inline int GetMousePositionY() const
		{
			return _mousePositionY;
		}

		inline KeyCode GetKeyDownInfo() const
		{
			return _keyDownInfo;
		}

		inline bool IsDoubleClicked() const
		{
			return _isDoubleClicked;
		}

		int GetWheelDistance() const
		{
			return _wheelDistance;
		}

	private:
		MouseButton _mouseButton;
		int _mousePositionX;
		int _mousePositionY;
		KeyCode _keyDownInfo;
		bool _isDoubleClicked;
		int _wheelDistance;
	};

	class IEventHandler : public IInitializable
	{
	public:
		virtual void OnKeyDown(const KeyInfo& keyDownInfo) = 0;
		virtual void OnKeyUp(const KeyInfo& keyUpInfo) = 0;
		virtual void OnMouseDown(const MouseInfo& mouseDownInfo) = 0;
		virtual void OnMouseUp(const MouseInfo& mouseUpInfo) = 0;
		virtual void OnMouseMove(const MouseInfo& mouseMoveInfo) = 0;
		virtual void OnMouseWheel(const MouseInfo& mouseWheelInfo) = 0;
		virtual void HandleBeforeFrame() = 0;
		virtual void HandleAfterFrame() = 0;

		virtual ~IEventHandler() {};
	};
}



