#pragma once

#include"System/IWindow.h"
#include"DX11Common.h"
#include"Core/ServiceConsumer.h"
#include"Graphics/IGraphicsController.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

namespace ue
{
	class DXD11GraphicsSettings
	{
	public:
		DXD11GraphicsSettings() :_vsync(false)
		{
		}

		DXD11GraphicsSettings(bool vsync) :_vsync(vsync)
		{
		}

		inline bool GetVsync()const
		{
			return _vsync;
		}

		inline void SetVysnc(bool vsync)
		{
			_vsync = vsync;
		}

	private:
		bool _vsync;
	};

	class DX11GraphicsController : public IGraphicsController,public ServiceConsumer
	{
	public:
		DX11GraphicsController();

		virtual void Init(uintptr_t state) override;

		virtual void TurnOnDepth() override;

		virtual void TurnOffDepth() override;

		virtual void TurnOnWireframe() override;

		virtual void TurnOffWireframe() override;

		virtual void BeginRender() override;

		virtual void EndRender() override;

		virtual const VideoCardInfo& GetVideoCardInfo() const override;

		virtual ID3D11Device* GetDevice()const;

		virtual ID3D11DeviceContext* GetDeviceContext()const;

		virtual ~DX11GraphicsController();

	private:
		void CreateDeviceAndSwapChain();
		void CreateDepthStencilBuffer();
		void CreateDepthStencilView();
		void CreateRenderTargetView();
		void CreateDepthStencilState(ID3D11DepthStencilState** depthStencilState, bool isDisabled = false);
		void CreateRasterizerState(ID3D11RasterizerState** depthStencilState, bool isWireframe = false);
		void CreateViewPort();

	private:
		bool _hasInit;
		const DXGI_FORMAT colorFormat;
		const float _clearColor[4];
		DXGI_RATIONAL _refreshRate;
		std::unique_ptr<VideoCardInfo> _videoCardInfo;
		std::unique_ptr<DXD11GraphicsSettings> _settings;
		const std::unique_ptr<D3D11_VIEWPORT> _viewport;

		ServicePtr<IWindow> _window;

		ComPtr<IDXGIFactory> _factory;
		ComPtr<IDXGIAdapter> _adapter;
		ComPtr<ID3D11Device> _device;
		ComPtr<ID3D11DeviceContext> _deviceContext;
		ComPtr<IDXGISwapChain> _swapChain;
		ComPtr<ID3D11RenderTargetView> _renderTargetView;
		ComPtr<ID3D11Texture2D> _depthStencilBuffer;
		ComPtr<ID3D11DepthStencilState> _depthStencilDisabledState;
		ComPtr<ID3D11DepthStencilState> _depthStencilState;
		ComPtr<ID3D11DepthStencilView> _depthStencilView;
		ComPtr<ID3D11RasterizerState> _rasterizerState;
		ComPtr<ID3D11RasterizerState> _rasterizerWireframeState;
	};

}

