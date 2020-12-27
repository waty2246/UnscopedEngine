#pragma once

#include"../Models/TriangleModel.h"
#include"Graphics/DX11/DX11IndexDrawShader.h"
#include"Graphics/DX11/DX11RenderObjectBase.h"

namespace ue
{
	template<typename Model, typename Shader>
	class DX11PolygonObject : public DX11RenderObjectBase
	{
	public:
		DX11PolygonObject();

		virtual void Init(uintptr_t state) override;
		virtual void Update()override;
		virtual void Render() override;
	private:
		bool _hasInit;
		std::unique_ptr<PolygonModel> _model;
		std::unique_ptr<DX11IndexDrawShader> _shader;
	};

	
	template<typename Model, typename Shader>
	DX11PolygonObject<Model,Shader>::DX11PolygonObject() :
		_hasInit(false),
		_model(std::make_unique<Model>()),
		_shader(std::make_unique<Shader>())
	{
	}

	template<typename Model, typename Shader>
	void DX11PolygonObject<Model, Shader>::Init(uintptr_t state)
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
		vertexBufferDesc.ByteWidth = sizeof(PolygonVertex) * _model->GetVertexCount();
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

	template<typename Model, typename Shader>
	void DX11PolygonObject<Model, Shader>::Update()
	{
	}

	template<typename Model, typename Shader>
	void DX11PolygonObject<Model, Shader>::Render()
	{
		unsigned int stride;
		unsigned int offset;

		stride = sizeof(PolygonVertex);
		offset = 0;

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_shader->Render(_model->GetIndexCount());
	}

}


