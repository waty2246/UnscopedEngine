#include "DX11MatrixShaderBase.h"

namespace ue
{
	void DX11MatrixShaderBase::Init(uintptr_t state)
	{
		DX11ShaderBase::Init(state);

		HRESULT hResult = HRESULT(0);
		D3D11_BUFFER_DESC matrixBufferDesc;

		_camera = this->GetService<CameraComponent>();

		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixCBufferType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		hResult = _device->CreateBuffer(&matrixBufferDesc, nullptr, _matrixBuffer.GetAddressOf());
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11Device::CreateBuffer failed.", hResult);
		}
	}

	void DX11MatrixShaderBase::RenderMatrix(bool isOrtho)
	{
		HRESULT hResult=HRESULT(0);
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		MatrixCBufferType* dataPtr;
		DirectX::XMMATRIX worldMatrix;
		DirectX::XMMATRIX viewMatrix;
		DirectX::XMMATRIX projectionMatrix;
		DirectX::XMMATRIX worldViewProjection;

		worldMatrix = _camera->GetWorldMatrix();
		viewMatrix = _camera->GetViewMatrix();
		if (isOrtho)
		{
			projectionMatrix = _camera->GetOrthoMatrix();
		}
		else
		{
			projectionMatrix = _camera->GetProjectionMatrix();
		}

		worldViewProjection = DirectX::XMMatrixMultiply(worldMatrix, viewMatrix);
		worldViewProjection = DirectX::XMMatrixMultiply(worldViewProjection, projectionMatrix);
		worldViewProjection = DirectX::XMMatrixTranspose(worldViewProjection);

		worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
		viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
		projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);

		hResult = _deviceContext->Map(_matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(hResult))
		{
			LOGMSG("ID3D11DeviceContext::Map failed.", hResult);
		}

		dataPtr = reinterpret_cast<MatrixCBufferType*>(mappedResource.pData);

		dataPtr->world = worldMatrix;
		dataPtr->view = viewMatrix;
		dataPtr->projection = projectionMatrix;
		dataPtr->wvp = worldViewProjection;

		_deviceContext->Unmap(_matrixBuffer.Get(), 0);

		_deviceContext->VSSetConstantBuffers(0, 1, _matrixBuffer.GetAddressOf());
	}
}

