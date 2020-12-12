#include"System/IWindow.h"
#include "CameraComponent.h"

namespace ue
{
	CameraComponent::CameraComponent():
		_hasInit(false),
		_nearPlane(0.1f),_farPlane(1000.0f),_fieldOfView(DirectX::XM_PIDIV4),
		_aspectRatio(0.0f),
		_cameraPosition(0.0f, 0.0f, -5.0f),
		_cameraRotation(0.0f,0.0f,0.0f),
		_cameraFocus(0.0f, 0.0f, 1.0f),
		_worldMatrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		),
		_viewMatrix(),
		_projectionMatrix(),
		_orthoMatrix()
	{
	}

	void CameraComponent::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		auto window = this->GetService<IWindow>();
		_aspectRatio = static_cast<float>(window->GetScreenWidth()) / static_cast<float>(window->GetScreenHeight());

		DirectX::XMStoreFloat4x4A(&_projectionMatrix, DirectX::XMMatrixPerspectiveFovLH(_fieldOfView,_aspectRatio, _nearPlane, _farPlane));
		DirectX::XMStoreFloat4x4A(&_orthoMatrix, DirectX::XMMatrixOrthographicLH(static_cast<float>(window->GetScreenWidth()), static_cast<float>(window->GetScreenHeight()), _nearPlane, _farPlane));
	}

	void CameraComponent::Frame()
	{
		DirectX::XMVECTOR upVector = DirectX::XMVectorSet(_worldMatrix._21, _worldMatrix._22, _worldMatrix._23, _worldMatrix._24);
		DirectX::XMVECTOR cameraPosition = DirectX::XMLoadFloat3A(&_cameraPosition);
		DirectX::XMVECTOR focusVector= DirectX::XMLoadFloat3A(&_cameraFocus);
		DirectX::XMVECTOR cameraRotation = DirectX::XMLoadFloat3A(&_cameraRotation);
		DirectX::XMMATRIX rotationMatrix=DirectX::XMMatrixRotationRollPitchYawFromVector(cameraRotation);

		focusVector = DirectX::XMVector3TransformCoord(focusVector, rotationMatrix);
		DirectX::XMStoreFloat3A(&_cameraFocus, focusVector);

		DirectX::XMVECTOR focusPosition = DirectX::XMVectorAdd(cameraPosition, focusVector);
		DirectX::XMStoreFloat4x4A(&_viewMatrix,DirectX::XMMatrixLookAtLH(cameraPosition, focusPosition, upVector));

		_cameraRotation = { 0.0f,0.0f,0.0f };
	}

	void CameraComponent::SetPosition(float x, float y, float z)
	{
		_cameraPosition.x = x;
		_cameraPosition.y = y;
		_cameraPosition.z = z;
	}

	void CameraComponent::SetRotation(float roll, float pitch, float yaw) 
	{
		const float dtr = DirectX::XM_PI / 180.f;
		_cameraRotation.x = roll * dtr;
		_cameraRotation.y = pitch * dtr;
		_cameraPosition.z = yaw * dtr;
	}

	void CameraComponent::SetFocus(float x, float y, float z)
	{
		_cameraFocus.x = x;
		_cameraFocus.y = y;
		_cameraFocus.z = z;
	}

	const DirectX::XMFLOAT3A& CameraComponent::GetPosition() const 
	{
		return _cameraPosition;
	}

	const DirectX::XMFLOAT3A& CameraComponent::GetFocus() const
	{
		return _cameraFocus;
	}

	DirectX::XMMATRIX CameraComponent::GetWorldMatrix() const
	{
		return DirectX::XMLoadFloat4x4A(&_worldMatrix);
	}

	DirectX::XMMATRIX CameraComponent::GetViewMatrix() const
	{
		return DirectX::XMLoadFloat4x4A(&_viewMatrix);
	}

	DirectX::XMMATRIX CameraComponent::GetProjectionMatrix() const
	{
		return DirectX::XMLoadFloat4x4A(&_projectionMatrix);
	}

	DirectX::XMMATRIX CameraComponent::GetOrthoMatrix() const
	{
		return DirectX::XMLoadFloat4x4A(&_orthoMatrix);
	}
}