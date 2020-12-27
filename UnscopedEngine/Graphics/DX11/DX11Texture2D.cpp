#include"DX11GraphicsController.h"
#include "DX11Texture2D.h"

namespace ue
{
	DX11Texture2D::DX11Texture2D(std::string&& fileName, ImageType imageType):
		_hasInit(false),
		_fileName(fileName),
		_imageType(imageType),
		_bindFlags(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET),
		_miscFlags(D3D11_RESOURCE_MISC_GENERATE_MIPS),
		_isAutoGenerateMipmaps(true),
		_isSampledTexture(false),
		_usage(D3D11_USAGE_DEFAULT),
		_cpuAccess(0),
		_colorFormat(DXGI_FORMAT_R8G8B8A8_UNORM)
	{
	}

	DX11Texture2D::DX11Texture2D(const std::string& fileName, ImageType imageType):
		DX11Texture2D(std::string(fileName),imageType)
	{
	}

	void DX11Texture2D::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		HRESULT hResult = HRESULT(0);
		ImageColorFormat imageColorFormat=ImageColorFormat::UNKNOW;

		D3D11_TEXTURE2D_DESC texture2DDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

		ZeroMemory(&texture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		auto graphics = this->GetService<IGraphicsController,DX11GraphicsController>();

		switch (_colorFormat)
		{
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			{
				imageColorFormat = ImageColorFormat::R8G8B8A8;
				break;
			}
		}
		auto image= std::make_unique<Image>(_fileName, _imageType, imageColorFormat);
		image->Init(state);

		UINT mipLevels = 0; 
		if (_isAutoGenerateMipmaps)
		{
			// These flags must be include when auto generate mipmaps and mipLevels must be set to 0.
			_bindFlags |= D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			_miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
		}
		else
		{
			if (_isSampledTexture)
			{
				mipLevels = 1;
			}
		}

		texture2DDesc.Width = image->GetImageWidth();
		texture2DDesc.Height = image->GetImageHeight();
		texture2DDesc.MipLevels = mipLevels;
		texture2DDesc.ArraySize = 1;
		texture2DDesc.Format = _colorFormat;
		texture2DDesc.SampleDesc.Count = 1;
		texture2DDesc.SampleDesc.Quality = 0;
		texture2DDesc.Usage = _usage;
		texture2DDesc.BindFlags = _bindFlags;
		texture2DDesc.CPUAccessFlags = _cpuAccess;
		texture2DDesc.MiscFlags = _miscFlags;
		

		auto rowPitch = (image->GetImageWidth() * 4);

		// Create the texture
		if (D3D11_USAGE_IMMUTABLE == _usage)
		{
			D3D11_SUBRESOURCE_DATA textureData = { 0 };
			textureData.pSysMem = image->GetImageData();
			textureData.SysMemPitch = rowPitch;

			hResult = graphics->GetDevice()->CreateTexture2D(&texture2DDesc, &textureData, _texture2D.GetAddressOf());
			if (FAILED(hResult))
			{
				LOGMSG("ID3D11Device::CreateTexture2D failed.", hResult);
			}
		}
		else
		{
			hResult = graphics->GetDevice()->CreateTexture2D(&texture2DDesc, nullptr, _texture2D.GetAddressOf());
			if (FAILED(hResult))
			{
				LOGMSG("ID3D11Device::CreateTexture2D failed.", hResult);
			}

			// Copy the texture data into the texture.
			// The recommendation when use Map/Unmap is to create buffers with dynamic usage that is going to be reloaded each frame or on a very regular basis.
			// UpdateSubresource incurs more CPU overhead than Map/Unmap but it is recommended for default usage because efficient buffer management (the data is on higher speed memory).
			if (D3D11_USAGE_DEFAULT == _usage)
			{
				graphics->GetDeviceContext()->UpdateSubresource(_texture2D.Get(), 0, nullptr, image->GetImageData(), rowPitch, 0);
			}
			else
			{
				D3D11_MAPPED_SUBRESOURCE textureData = { 0 };
				hResult=graphics->GetDeviceContext()->Map(_texture2D.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &textureData);
				if (FAILED(hResult))
				{
					LOGMSG("ID3D11DeviceContext::Map failed.", hResult);
				}

				textureData.pData = image->GetImageData();
				textureData.RowPitch = rowPitch;

				graphics->GetDeviceContext()->Unmap(_texture2D.Get(),0);
			}
		}

		// Fill shader resource view descriptor
		srvDesc.Format = _colorFormat;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		hResult = graphics->GetDevice()->CreateShaderResourceView(_texture2D.Get(), &srvDesc, _texture2DView.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateShaderResourceView failed.", hResult);
		}

		// Generate mipmaps for this texture.
		if (_isAutoGenerateMipmaps)
		{
			graphics->GetDeviceContext()->GenerateMips(_texture2DView.Get());
		}
	}

	ID3D11ShaderResourceView* DX11Texture2D::GetShaderResourceView()const
	{
		return _texture2DView.Get();
	}

	DX11Texture2D::~DX11Texture2D()
	{
	}
}
