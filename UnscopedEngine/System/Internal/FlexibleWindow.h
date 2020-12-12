#pragma once

#include"System/IFlexibleWindow.h"

namespace ue
{
	class FlexibleWindow: public IFlexibleWindow
	{
	public:
		FlexibleWindow(int screenWidth, int screenHeight, int positionX, int positionY,bool isShowCursor, const std::wstring& title);
		FlexibleWindow(int screenWidth, int screenHeight, int positionX, int positionY, bool isShowCursor, std::wstring&& title);

		virtual void Init(uintptr_t WndProc) override final;
		virtual int GetScreenWidth() const override final;
		virtual int GetScreenHeight() const override final;
		virtual int GetPositionX() const override final;
		virtual int GetPositionY() const override final;
		virtual uintptr_t GetWindowPtr()const final;
		virtual std::wstring GetWindowTitle() const override final;
		virtual bool IsFullScreen() const override final;
		virtual bool GetCursorState()override final;

		virtual void ShowWindow() override final;
		virtual void ShowCursor() override;
		virtual void HideCursor() override;
		virtual void SetScreenWidth(int screenWidth) override final;
		virtual void SetScreenHeight(int screenHeight) override final;
		virtual void SetPositionX(int positionX) override final;
		virtual void SetPositionY(int positionY) override final;
		virtual void SetWindowTitle(const std::wstring& title) override final;
		virtual void SetWindowTitle(std::wstring&& title) override final;
		virtual void SetCursorPosition(int x, int y) override final;
		virtual void SetCursorPositionX(int x) override final;
		virtual void SetCursorPositionY(int y) override final;
		
		virtual ~FlexibleWindow();

	private:
		bool _hasInit;
		bool _isWindowShown;
		const bool _isShowCursor;
		bool _isCursorShown;
		bool _originCursorState;
		int _windowWidth;
		int _windowHeight;
		int _screenWidth;
		int _screenHeight;
		int _positionX;
		int _positionY;

		HWND _hwnd;
		HINSTANCE _hinstance;
		ATOM _windowClassEx;
		std::wstring _title;		
	};
}


