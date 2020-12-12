#include "FullscreenWindow.h"

namespace ue
{
	FullscreenWindow::FullscreenWindow(bool isShowCursor):
		_hasInit(false),
		_isShowCursor(isShowCursor),
		_isCursorShown(false),
		_originCursorState(false),
		_isWindowShown(false),
        _screenWidth(0),
        _screenHeight(0),
        _positionX(0),
        _positionY(0),
        _hwnd(nullptr),
        _hinstance(nullptr),
        _windowClassEx(0)
    {
    }

	void FullscreenWindow::Init(uintptr_t WndProc)
	{
		if (_hasInit )
		{
			return;
		}
		_hasInit = true;

		WNDCLASSEX wex = { 0 };
		DEVMODE dmScreenSettings;

		//Retrieve current Instance Handle
		_hinstance = GetModuleHandle(nullptr);

		//Init WNDCLASSEX data
		wex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wex.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
		wex.hInstance = _hinstance;
		wex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wex.hIconSm = wex.hIcon;
		wex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
		wex.lpszClassName = L"FullscreenWindow";
		wex.cbSize = sizeof(WNDCLASSEX);

		//Register window class for our Fullscreen Window
		_windowClassEx = ::RegisterClassExW(&wex);
		if (API_FAILED(_windowClassEx))
		{
			LOGMSG("RegisterClassEx failed", 0);
		}

		_screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
		_screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

		ZeroMemory(&dmScreenSettings,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)_screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)_screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		::ChangeDisplaySettingsW(&dmScreenSettings, CDS_FULLSCREEN);

		_hwnd = ::CreateWindowExW(
			WS_EX_APPWINDOW, MAKEINTRESOURCE(_windowClassEx),
			L"", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			_positionX, _positionY,
			_screenWidth, _screenHeight,
			nullptr, nullptr, _hinstance, nullptr
		);
		if (nullptr == _hwnd)
		{
			LOGMSG("CreateWindowExW failed", 0);
		}

		CURSORINFO cursorInfo = { 0 };
		GetCursorInfo(&cursorInfo);
		if (CURSOR_SHOWING == cursorInfo.flags)
		{
			_isCursorShown = true;
			_originCursorState = true;
		}
	}

	void FullscreenWindow::ShowWindow()
	{
		if (_isWindowShown)return;

		::ShowWindow(_hwnd, SW_SHOW);
		_isWindowShown = true;

		::SetForegroundWindow(_hwnd);
		::SetFocus(_hwnd);

		if (_isShowCursor)
		{
			this->ShowCursor();
		}
		else
		{
			this->HideCursor();
		}
	}

	int FullscreenWindow::GetScreenWidth() const
	{
		return _screenWidth;
	}

	int FullscreenWindow::GetScreenHeight() const
	{
		return _screenHeight;
	}

	int FullscreenWindow::GetPositionX() const
	{
		return _positionX;
	}

	int FullscreenWindow::GetPositionY() const
	{
		return _positionY;
	}

	uintptr_t FullscreenWindow::GetWindowPtr() const
	{
		return reinterpret_cast<uintptr_t>(_hwnd);
	}

	bool FullscreenWindow::GetCursorState()
	{
		return _isCursorShown;
	}

	void FullscreenWindow::HideCursor()
	{
		if (_isCursorShown)
		{
			_isCursorShown = false;
			::ShowCursor(FALSE);
		}
	}

	void FullscreenWindow::ShowCursor()
	{
		if (!_isCursorShown)
		{
			_isCursorShown = true;
			::ShowCursor(TRUE);
		}
	}

	bool FullscreenWindow::IsFullScreen() const
	{
		return true;
	}

	void FullscreenWindow::SetCursorPosition(int x, int y)
	{
		::SetCursorPos(x,y);
	}

	void FullscreenWindow::SetCursorPositionX(int x)
	{
		POINT currentCursorPosition = { 0,0 };
		::GetCursorPos(&currentCursorPosition);
		::SetCursorPos(x, currentCursorPosition.y);
	}

	void FullscreenWindow::SetCursorPositionY(int y)
	{
		POINT currentCursorPosition = { 0,0 };
		::GetCursorPos(&currentCursorPosition);
		::SetCursorPos(currentCursorPosition.x, y);
	}

	FullscreenWindow::~FullscreenWindow()
	{
		// Show the mouse cursor.
		if (_originCursorState)
		{
			this->ShowCursor();
		}

		::ChangeDisplaySettingsW(nullptr, 0);
		_hwnd = nullptr;

		// Remove the application instance.
		::UnregisterClassW(MAKEINTRESOURCE(_windowClassEx), _hinstance);
		_hinstance = nullptr;
		_windowClassEx = 0;
	}
}
