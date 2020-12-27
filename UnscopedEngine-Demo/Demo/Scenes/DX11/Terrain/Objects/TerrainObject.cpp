#include "TerrainObject.h"

namespace ue
{
	TerrainObject::TerrainObject(std::string terrainHeightMap):
		_hasInit(false),
		_model(std::make_unique<TerrainModel>(terrainHeightMap)),
		_shader(std::make_unique<DX11TerrainShader>())
	{
	}

	void TerrainObject::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}

		_hasInit = true;

		DX11RenderObjectBase::Init(state);
		_model->Init(state);
		_shader->Init(state);

		HRESULT hResult = HRESULT(0);
		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
		D3D11_SUBRESOURCE_DATA indexData = { 0 };

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(TerrainVertex) * _model->GetVertexCount();
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
	}

	void TerrainObject::Update()
	{
	}

	void TerrainObject::Render()
	{
		unsigned int stride;
		unsigned int offset;

		stride = sizeof(TerrainVertex);
		offset = 0;

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_shader->Render(_model->GetIndexCount());
	}
}

