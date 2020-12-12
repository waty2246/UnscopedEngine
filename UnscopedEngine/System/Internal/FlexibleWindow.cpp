#include "FlexibleWindow.h"

namespace ue
{
	FlexibleWindow::FlexibleWindow(int screenWidth, int screenHeight, int positionX, int positionY, bool isShowCursor,const std::wstring& title):
		FlexibleWindow(screenWidth,screenHeight,positionX,positionY, isShowCursor,std::wstring(title))
	{
	}

	FlexibleWindow::FlexibleWindow(int screenWidth, int screenHeight, int positionX, int positionY, bool isShowCursor, std::wstring&& title) :
		_hasInit(false),
		_isShowCursor(isShowCursor),
		_isCursorShown(false),
		_originCursorState(false),
		_isWindowShown(false),
		_windowWidth(0),
		_windowHeight(0),
		_screenWidth(screenWidth),
		_screenHeight(screenHeight),
		_positionX(positionX),
		_positionY(positionY),
		_hwnd(nullptr),
		_hinstance(nullptr),
		_windowClassEx(0),
		_title(std::move(title))
	{
	}

	void FlexibleWindow::Init(uintptr_t WndProc)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		WNDCLASSEX wex = { 0 };

		//Retrieve current Instance Handle
		_hinstance = GetModuleHandle(nullptr);

		//Init WNDCLASSEX data
		wex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wex.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
		wex.hInstance = _hinstance;
		wex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wex.hIconSm = wex.hIcon;
		wex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wex.lpszClassName = L"FlexibleWindow";
		wex.cbSize = sizeof(WNDCLASSEX);

		//Register window class for our Fullscreen Window
		_windowClassEx = RegisterClassExW(&wex);
		if (API_FAILED(_windowClassEx))
		{
			LOGMSG("RegisterClassEx failed", 0);
		}

		DWORD windowStyleEx = WS_EX_APPWINDOW;
		DWORD windowStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME;
		RECT rect{ 0,0,_screenWidth,_screenHeight };
		if (API_FAILED(AdjustWindowRectEx(&rect, windowStyle, FALSE, windowStyleEx)))
		{
			LOGMSG("AdjustWindowRectEx failed", 0);
		}

		_windowWidth = rect.right-rect.left;
		_windowHeight = rect.bottom-rect.top;

		_hwnd = CreateWindowExW(
			windowStyleEx, 
			MAKEINTRESOURCE(_windowClassEx),
			_title.c_str(), windowStyle,
			_positionX, _positionY,
			_windowWidth, _windowHeight,
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

	int FlexibleWindow::GetScreenWidth() const
	{
		return _screenWidth;
	}

	int FlexibleWindow::GetScreenHeight() const
	{
		return _screenHeight;
	}

	int FlexibleWindow::GetPositionX() const
	{
		return _positionX;
	}

	int FlexibleWindow::GetPositionY() const
	{
		return _positionY;
	}

	uintptr_t FlexibleWindow::GetWindowPtr() const
	{
		return reinterpret_cast<uintptr_t>(_hwnd);
	}

	bool FlexibleWindow::IsFullScreen() const
	{
		return false;
	}

	bool FlexibleWindow::GetCursorState()
	{
		return _isCursorShown;
	}

	std::wstring FlexibleWindow::GetWindowTitle() const
	{
		return std::wstring(_title);
	}

	void FlexibleWindow::SetScreenWidth(int screenWidth)
	{
	}

	void FlexibleWindow::SetScreenHeight(int screenHeight)
	{
	}

	void FlexibleWindow::SetPositionX(int positionX)
	{
	}

	void FlexibleWindow::SetPositionY(int positionY)
	{
	}

	void FlexibleWindow::SetWindowTitle(const std::wstring& title)
	{
		this->SetWindowTitle(std::wstring(title));
	}

	void FlexibleWindow::SetCursorPosition(int x, int y)
	{
	}

	void FlexibleWindow::SetCursorPositionX(int x)
	{
	}

	void FlexibleWindow::SetCursorPositionY(int y)
	{
	}

	void FlexibleWindow::SetWindowTitle(std::wstring&& title)
	{
		_title = std::move(title);
		if (API_FAILED(SetWindowTextW(_hwnd, _title.c_str())))
		{
			LOGMSG("SetWindowTextW falied.", 0);
		}
	}

	void FlexibleWindow::ShowWindow()
	{
		if (_isWindowShown) return;

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

	void FlexibleWindow::ShowCursor()
	{
		if (_isCursorShown)
		{
			_isCursorShown = false;
			::ShowCursor(FALSE);
		}
	}

	void FlexibleWindow::HideCursor()
	{
		if (!_isCursorShown)
		{
			_isCursorShown = true;
			::ShowCursor(TRUE);
		}
	}

	FlexibleWindow::~FlexibleWindow()
	{
		if (_originCursorState)
		{
			this->ShowCursor();
		}

		_hwnd = nullptr;

		// Remove the application instance.
		::UnregisterClassW(MAKEINTRESOURCE(_windowClassEx), _hinstance);
		_hinstance = nullptr;
		_windowClassEx = 0;
	}
}
