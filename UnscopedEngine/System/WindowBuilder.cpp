#include"Internal/FullscreenWindow.h"
#include"Internal/FlexibleWindow.h"
#include "WindowBuilder.h"


namespace ue
{
	WindowBuilder::WindowBuilder():
		_windowMode(WindowMode::WINDOW),
		_isShowCursor(true),
		_screenWidth(800),
		_screenHeight(600),
		_positionX(0),
		_positionY(0),
		_title()
	{
	}

	WindowBuilder* WindowBuilder::SetWindowMode(WindowMode windowMode)
	{
		_windowMode = windowMode;
		return this;
	}

	WindowBuilder* WindowBuilder::SetCursorDisplay(bool isShowCursor)
	{
		_isShowCursor = isShowCursor;
		return this;
	}

	WindowBuilder* WindowBuilder::SetScreenWidth(int screenWidth)
	{
		_screenWidth = screenWidth;
		return this;
	}
	WindowBuilder* WindowBuilder::SetScreenHeight(int screenHeight)
	{
		_screenHeight = screenHeight;
		return this;
	}

	WindowBuilder* WindowBuilder::SetPositionX(int x)
	{
		_positionX = x;
		return this;
	}

	WindowBuilder* WindowBuilder::SetPositionY(int y)
	{
		_positionY = y;
		return this;
	}

	WindowBuilder* WindowBuilder::SetWindowTitle(const wchar_t* title)
	{
		_title = title;
		return this;
	}

	IWindow* WindowBuilder::Build()
	{
		if (WindowMode::WINDOW == _windowMode)
		{
			return new FlexibleWindow(_screenWidth, _screenHeight, _positionX, _positionY,_isShowCursor,std::wstring(_title));
		}

		return new FullscreenWindow(_isShowCursor);
	}
}