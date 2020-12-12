#pragma once

#include"Common.h"
#include"System/IWindow.h"

namespace ue
{
	class FullscreenWindow: public IWindow
	{
	public:
		FullscreenWindow(bool isShowCursor);

		virtual void Init(uintptr_t WndProc) override final;
		virtual void ShowWindow()override final;
		virtual int GetScreenWidth() const override final;
		virtual int GetScreenHeight() const override final;
		virtual int GetPositionX() const override final;
		virtual int GetPositionY() const override final;
		virtual bool IsFullScreen() const override final;
		virtual uintptr_t GetWindowPtr()const override final;
		virtual bool GetCursorState()override final;

		virtual void ShowCursor() override final;
		virtual void HideCursor() override final;
		virtual void SetCursorPosition(int x, int y) override final;
		virtual void SetCursorPositionX(int x) override final;
		virtual void SetCursorPositionY(int y) override final;

		~FullscreenWindow();

	protected:
		bool _hasInit;
		bool _isWindowShown;
		const bool _isShowCursor;
		bool _isCursorShown;
		bool _originCursorState;
		int _screenWidth;
		int _screenHeight;
		int _positionX;
		int _positionY;
		HWND _hwnd;
		HINSTANCE _hinstance;
		ATOM _windowClassEx;
	};
}


