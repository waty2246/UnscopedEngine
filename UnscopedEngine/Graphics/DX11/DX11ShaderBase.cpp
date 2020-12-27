#include"DX11GraphicsController.h"
#include "DX11ShaderBase.h"


namespace ue
{
	std::vector<uint8_t> DX11ShaderBase::InitShaders(const char* vertexCSOFile, const char* pixelCSOFile)
	{
		this->CreatePixelShader(pixelCSOFile);
		return this->CreateVertexShader(vertexCSOFile);
	}

	std::vector<uint8_t> DX11ShaderBase::CreateVertexShader(const char* vertexCSOFile)
	{
		HRESULT hResult = HRESULT(0);

		//Optimize this to avoid double buffer copy and destroy.
		std::ifstream in(vertexCSOFile, std::ios::in | std::ios::binary);
		std::stringstream buf;
		buf << in.rdbuf();

		auto str = buf.str();

		hResult = _device->CreateVertexShader(str.c_str(), str.length(), nullptr, _vertexShader.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateVertexShader failed.", hResult);
		}

		return std::vector<uint8_t>(str.begin(),str.end());
	}

	void DX11ShaderBase::CreatePixelShader(const char* pixelCSOFile)
	{
		HRESULT hResult = HRESULT(0);

		std::ifstream in(pixelCSOFile, std::ios::in | std::ios::binary);
		std::stringstream buf;
		buf << in.rdbuf();

		auto bin = buf.str();

		hResult = _device->CreatePixelShader(bin.c_str(), bin.length(), nullptr, _pixelShader.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreatePixelShader failed.", hResult);
		}
	}
}

