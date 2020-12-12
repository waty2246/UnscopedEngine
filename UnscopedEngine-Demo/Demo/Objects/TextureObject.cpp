#include "TextureObject.h"

namespace ue
{
	TextureObject::TextureObject():
		_hasInit(false),
		_texture2D(std::make_unique<DX11Texture2D>("Resources\\Assets\\texture.bmp",ImageType::BITMAP))
	{
	}

	void TextureObject::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		DX11ObjectBase::Init(state);

		_model = std::make_unique<TextureModel>();
		_model->Init(state);

		_shader = std::make_unique<DX11TextureShader>();
		_shader->Init(state);

		HRESULT hResult = HRESULT(0);
		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
		D3D11_SUBRESOURCE_DATA indexData = { 0 };



		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(TextureDataType) * _model->GetVertexCount();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		vertexData.pSysMem = _model->GetVertices();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		hResult = _device->CreateBuffer(&vertexBufferDesc, &vertexData, _vertexBuffer.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateBuffer failed.", hResult);
		}

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(UINT) * _model->GetIndexCount();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		indexData.pSysMem = _model->GetIndices();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		hResult = _device->CreateBuffer(&indexBufferDesc, &indexData, _indexBuffer.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateBuffer failed.", hResult);
		}

		_texture2D->Init(state);

		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// Create the texture sampler state.
		hResult = _device->CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateSamplerState failed.", hResult);
		}
	}

	void TextureObject::Frame()
	{
	}

	void TextureObject::Render()
	{
		unsigned int stride;
		unsigned int offset;

		stride = sizeof(TextureDataType);
		offset = 0;

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_shader->Render(_model->GetIndexCount(),_texture2D->GetShaderResourceView(),_samplerState.Get());
	}
}

