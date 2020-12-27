#include"DX11Config.h"
#include "DX11GraphicsController.h"

namespace ue
{
	DX11GraphicsController::DX11GraphicsController() :
		_hasInit(false),
		_clearColor{1.0f,1.0f,1.0f,1.0f},
		colorFormat(DXGI_FORMAT_R8G8B8A8_UNORM),
		_refreshRate{ 60,1 },
		_viewport(std::make_unique<D3D11_VIEWPORT>()),
		_settings(std::make_unique<DXD11GraphicsSettings>())
	{
	}

	DX11GraphicsController::~DX11GraphicsController()
	{
	}

	void DX11GraphicsController::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		HRESULT hResult = HRESULT(0);
		UINT numModes = 0;

		ComPtr<IDXGIFactory2> factory{};
		ComPtr<IDXGIAdapter> adapter{};
		ComPtr<IDXGIOutput> output{};

		DXGI_ADAPTER_DESC adapterDesc = { 0 };
		std::unique_ptr<DXGI_MODE_DESC[]> modeDescs;

		//Get usage services
		_window = this->GetService<IWindow>();

		hResult = CreateDXGIFactory1(IID_PPV_ARGS(factory.GetAddressOf()));
		if (FAILED(hResult))
		{
			LOGMSG("CreateDXGIFactory failed.", hResult);
		}

		hResult = factory->EnumAdapters(0, adapter.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIFactory::EnumAdapters failed.", hResult);
		}

		hResult = adapter->GetDesc(&adapterDesc);
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIAdapter::GetDesc failed.", hResult);
		}

		//Init VideoCardInfo
		_videoCardInfo = std::make_unique<VideoCardInfo>(adapterDesc.Description, adapterDesc.DedicatedVideoMemory/1024/1024);

		hResult=adapter->EnumOutputs(0, output.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIAdapter::EnumOutputs failed.", hResult);
		}

		hResult = output->GetDisplayModeList(colorFormat, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIOutput::GetDisplayModeList failed.", hResult);
		}

		modeDescs = std::make_unique<DXGI_MODE_DESC[]>(numModes);
		hResult = output->GetDisplayModeList(colorFormat, DXGI_ENUM_MODES_INTERLACED, &numModes, modeDescs.get());
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIOutput::GetDisplayModeList failed.", hResult);
		}

		//Get maximum support refresh rate on screen size.
		for (UINT i = 0; i < numModes; i++)
		{
			if (modeDescs[i].Width == static_cast<UINT>(_window->GetScreenWidth()))
			{
				if (modeDescs[i].Height == static_cast<UINT>(_window->GetScreenHeight()))
				{
					_refreshRate.Numerator = modeDescs[i].RefreshRate.Numerator;
					_refreshRate.Denominator = modeDescs[i].RefreshRate.Denominator;
				}
			}
		}

		this->CreateDevice(adapter.Get());
		this->CreateSwapChain(factory.Get());
		this->CreateRenderTargetView();
		this->CreateDepthStencilBuffer();
		this->CreateDepthStencilView();

		this->CreateDepthStencilState(_depthStencilState.GetAddressOf());
		this->CreateDepthStencilState(_depthStencilDisabledState.GetAddressOf(),true);
		this->CreateRasterizerState(_rasterizerState.GetAddressOf());
		this->CreateRasterizerState(_rasterizerWireframeState.GetAddressOf(),true);
		this->CreateViewPort();

		_deviceContext->OMSetDepthStencilState(_depthStencilState.Get(), 1);
		_deviceContext->RSSetState(_rasterizerState.Get());

#if OUTPUT_VIDEO_CARD_INFO == 1
		std::wcout << " Video Card Info: " << _videoCardInfo->GetVideoCardName() << " (" << _videoCardInfo->GetDedicatedMemory() << "MB)" << std::endl;
#endif

#if OUTPUT_SCREEN_REFRESH_RATE_INFO == 1
		std::cout << " Ssreen Refresh Rate: " << _refreshRate.Numerator / _refreshRate.Denominator<<"Hz" << std::endl;
#endif
	}

	void DX11GraphicsController::BeginRender()
	{
		_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
		_deviceContext->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
		_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
		_deviceContext->RSSetViewports(1, _viewport.get());
	}

	void DX11GraphicsController::EndRender()
	{
		if (_settings->GetVsync())
		{
			_swapChain->Present(1, 0);
		}
		else
		{
			_swapChain->Present(0, 0);
		}
	}

	const VideoCardInfo& DX11GraphicsController::GetVideoCardInfo() const
	{
		return *_videoCardInfo.get();
	}

	ID3D11Device* DX11GraphicsController::GetDevice() const
	{
		return _device.Get();
	}

	ID3D11DeviceContext* DX11GraphicsController::GetDeviceContext() const
	{
		return _deviceContext.Get();
	}

	void DX11GraphicsController::CreateDevice(IDXGIAdapter* adapter)
	{
		HRESULT hResult{ 0 };
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;
		D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
		UINT creationFlags = 0;

#if ENABLE_DEBUG_LAYER == 1
		// If the project is in a debug build, enable the debug layer.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		if (adapter != nullptr)
		{
			driverType = D3D_DRIVER_TYPE_UNKNOWN;
		}

		hResult = D3D11CreateDevice(adapter, driverType, nullptr, creationFlags, &featureLevel, 1, D3D11_SDK_VERSION, _device.GetAddressOf(), nullptr, _deviceContext.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("D3D11CreateDevice failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateSwapChain(IDXGIFactory2* factory)
	{
		HRESULT hResult = HRESULT(0);
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		std::unique_ptr< DXGI_SWAP_CHAIN_FULLSCREEN_DESC> fullscreenDescPtr{};
		

		swapChainDesc.BufferCount = 2;
		swapChainDesc.Width = _window->GetScreenWidth();
		swapChainDesc.Height = _window->GetScreenHeight();
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;

		// Turn off multisampling
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Flags = 0;

		if (_window->IsFullScreen())
		{
			fullscreenDescPtr = std::make_unique<DXGI_SWAP_CHAIN_FULLSCREEN_DESC>();
			fullscreenDescPtr->ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			fullscreenDescPtr->Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			fullscreenDescPtr->Windowed = false;

			if (_settings->GetVsync())
			{
				fullscreenDescPtr->RefreshRate = _refreshRate;
			}
			else
			{
				fullscreenDescPtr->RefreshRate = { 0,1 };
			}
		}

		hResult = factory->CreateSwapChainForHwnd(_device.Get(), reinterpret_cast<HWND>(_window->GetWindowPtr()), &swapChainDesc, fullscreenDescPtr.get(),nullptr,_swapChain.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("IDXGIFactory2::CreateSwapChainForHwnd failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateDepthStencilBuffer()
	{
		HRESULT hResult = HRESULT(0);
		D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0 };

		depthStencilBufferDesc.Width = _window->GetScreenWidth();
		depthStencilBufferDesc.Height = _window->GetScreenHeight();
		depthStencilBufferDesc.MipLevels = 1;
		depthStencilBufferDesc.ArraySize = 1;
		depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilBufferDesc.SampleDesc.Count = 1;
		depthStencilBufferDesc.SampleDesc.Quality = 0;
		depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilBufferDesc.CPUAccessFlags = 0;
		depthStencilBufferDesc.MiscFlags = 0;

		hResult = _device->CreateTexture2D(&depthStencilBufferDesc, nullptr, _depthStencilBuffer.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateTexture2D failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateDepthStencilView()
	{
		HRESULT hResult = HRESULT(0);
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		hResult = _device->CreateDepthStencilView(_depthStencilBuffer.Get(), &depthStencilViewDesc, _depthStencilView.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateDepthStencilView failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateRenderTargetView()
	{
		HRESULT hResult = HRESULT(0);
		ComPtr<ID3D11Texture2D> backBufferPtr;

		hResult = _swapChain->GetBuffer(0, IID_PPV_ARGS(backBufferPtr.GetAddressOf()));
		if (FAILED(hResult))
		{
			LOGMSG("IDXGISwapChain::GetBuffer failed.", hResult);
		}

		hResult = _device->CreateRenderTargetView(backBufferPtr.Get(), nullptr, _renderTargetView.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateRenderTargetView failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateDepthStencilState(ID3D11DepthStencilState** depthStencilState, bool isDisabled)
	{
		HRESULT hResult = HRESULT(0);
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };

		if (isDisabled)
		{
			depthStencilDesc.DepthEnable = false;
		}
		else
		{
			depthStencilDesc.DepthEnable = true;
		}
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing.
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing.
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hResult = _device->CreateDepthStencilState(&depthStencilDesc, depthStencilState);
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateDepthStencilState failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateRasterizerState(ID3D11RasterizerState** rasterizerState, bool isWireframe)
	{
		HRESULT hResult = HRESULT(0);
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

		if (isWireframe)
		{
			rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		}
		else
		{
			rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		}

		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = true;
		
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.MultisampleEnable = false;
		rasterizerDesc.ScissorEnable = false;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		hResult = _device->CreateRasterizerState(&rasterizerDesc, rasterizerState);
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateRasterizerState failed.", hResult);
		}
	}

	void DX11GraphicsController::CreateViewPort()
	{
		_viewport->Width = static_cast<float>(_window->GetScreenWidth());
		_viewport->Height = static_cast<float>(_window->GetScreenHeight());
		_viewport->MinDepth = 0.0f;
		_viewport->MaxDepth = 1.0f;
		_viewport->TopLeftX = 0.0f;
		_viewport->TopLeftY = 0.0f;
	}

	void DX11GraphicsController::TurnOnDepth()
	{
		_deviceContext->OMSetDepthStencilState(_depthStencilState.Get(), 1);
	}

	void DX11GraphicsController::TurnOffDepth()
	{
		_deviceContext->OMSetDepthStencilState(_depthStencilDisabledState.Get(), 1);
	}

	void DX11GraphicsController::TurnOnWireframe()
	{
		_deviceContext->RSSetState(_rasterizerWireframeState.Get());
	}

	void DX11GraphicsController::TurnOffWireframe()
	{
		_deviceContext->RSSetState(_rasterizerState.Get());
	}
}

