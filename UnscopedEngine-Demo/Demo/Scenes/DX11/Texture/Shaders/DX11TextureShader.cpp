#include "DX11TextureShader.h"

namespace ue
{
	DX11TextureShader::DX11TextureShader() :
		_hasInit(false),
		_matrixShaderPart(std::make_unique<DX11MatrixShaderPart>())
	{
	}

	void DX11TextureShader::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		DX11ShaderBase::Init(state);
		_matrixShaderPart->Init(state);

		auto vertexShaderByteCode = this->InitShaders("Resources\\CSO\\TextureVertexShader.cso", "Resources\\CSO\\TexturePixelShader.cso");

		HRESULT hResult = HRESULT(0);
		D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "TEXCOORD";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		hResult = _device->CreateInputLayout(
			polygonLayout,
			sizeof(polygonLayout) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			vertexShaderByteCode.data(),
			vertexShaderByteCode.size(),
			_layout.GetAddressOf()
		);
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateInputLayout failed.", hResult);
		}
	}

	void DX11TextureShader::Render(UINT indexCount,ID3D11ShaderResourceView* texture,ID3D11SamplerState* samplerState)
	{
		_matrixShaderPart->RenderMatrix();

		_deviceContext->PSSetSamplers(0, 1, &samplerState);
		_deviceContext->PSSetShaderResources(0, 1, &texture);

		_deviceContext->IASetInputLayout(_layout.Get());
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		
		_deviceContext->DrawIndexed(indexCount, 0, 0);
	}
}

