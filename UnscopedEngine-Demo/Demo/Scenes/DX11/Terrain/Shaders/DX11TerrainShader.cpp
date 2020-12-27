#include "DX11TerrainShader.h"

namespace ue
{
	DX11TerrainShader::DX11TerrainShader():
		_hasInit(false),
		_matrixShaderPart(std::make_unique<DX11MatrixShaderPart>())
	{
	}

	void DX11TerrainShader::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		DX11IndexDrawShader::Init(state);
		_matrixShaderPart->Init(state);
		auto vertexShaderByteCode = this->InitShaders("Resources\\CSO\\TerrainVertexShader.cso", "Resources\\CSO\\TerrainPixelShader.cso");

		HRESULT hResult = HRESULT(0);
		D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

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

	void DX11TerrainShader::Render(UINT indexCount)
	{
		_matrixShaderPart->RenderMatrix();

		_deviceContext->IASetInputLayout(_layout.Get());
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->DrawIndexed(indexCount, 0, 0);
	}
}

