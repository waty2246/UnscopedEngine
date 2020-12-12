#pragma once

#include"IWindow.h"

namespace ue
{
	class IFlexibleWindow :virtual public IWindow
	{
	public:
		virtual std::wstring GetWindowTitle()const = 0;

		virtual void SetScreenWidth(int screenWidth) = 0;
		virtual void SetScreenHeight(int screenHeight) = 0;

		virtual void SetPositionX(int positionX) = 0;
		virtual void SetPositionY(int positionY) = 0;

		virtual void SetWindowTitle(const std::wstring& title) = 0;
		virtual void SetWindowTitle(std::wstring&& title) = 0;
	};
}