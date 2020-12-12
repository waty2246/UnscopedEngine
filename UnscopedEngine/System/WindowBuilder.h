#pragma once

#include"Common.h"
#include"IWindow.h"

namespace ue
{
	enum class WindowMode
	{
		WINDOW,
		FULLSCREEN
	};

	class WindowBuilder
	{
	public:
		WindowBuilder();

		WindowBuilder* SetWindowMode(WindowMode windowMode);
		WindowBuilder* SetCursorDisplay(bool isShowCursor);
		WindowBuilder* SetScreenWidth(int screenWidth);
		WindowBuilder* SetScreenHeight(int screenHeight);
		WindowBuilder* SetPositionX(int x);
		WindowBuilder* SetPositionY(int y);
		WindowBuilder* SetWindowTitle(const wchar_t* title);

		IWindow* Build();
	private:
		WindowMode _windowMode;
		bool _isShowCursor;
		int _screenWidth;
		int _screenHeight;
		int _positionX;
		int _positionY;
		LPCWSTR _title;
	};
}


