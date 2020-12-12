#pragma once

#include"Common.h"
#include"Core/IInitializable.h"

typedef HWND WindowId;

namespace ue
{
	class IWindow : public IInitializable
	{
	public:
		virtual void ShowWindow() = 0;

		virtual uintptr_t GetWindowPtr()const = 0;

		virtual int GetScreenWidth()const = 0;
		virtual int GetScreenHeight()const = 0;

		virtual int GetPositionX()const = 0;
		virtual int GetPositionY()const = 0;

		virtual bool IsFullScreen()const = 0;

		virtual void ShowCursor() = 0;
		virtual void HideCursor() = 0;
		virtual bool GetCursorState() = 0;

		/// <summary>
		/// Set cursor position in relative from client window area
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		virtual void SetCursorPosition(int x,int y) = 0;
		virtual void SetCursorPositionX(int x) = 0;
		virtual void SetCursorPositionY(int y) = 0;
	};
}