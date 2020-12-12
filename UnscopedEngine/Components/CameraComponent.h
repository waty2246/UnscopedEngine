#pragma once

#include"Common.h"
#include"Core/IInitializable.h"
#include"Core/ServiceConsumer.h"

namespace ue
{
	class CameraComponent :public IInitializable, public ServiceConsumer
	{
	public:
		CameraComponent();

		virtual void Init(uintptr_t state) override;
		void Frame();

		void SetPosition(float x, float y, float z) ;
		void SetRotation(float roll, float pitch, float yaw);
		void SetFocus(float x, float y, float z);

		const DirectX::XMFLOAT3A& GetPosition()const ;
		const DirectX::XMFLOAT3A& GetFocus()const ;

		DirectX::XMMATRIX GetWorldMatrix()const;
		DirectX::XMMATRIX GetViewMatrix()const;
		DirectX::XMMATRIX GetProjectionMatrix()const;
		DirectX::XMMATRIX GetOrthoMatrix()const;

	protected:
		bool _hasInit;

		const float _nearPlane;
		const float _farPlane;
		const float _fieldOfView;
		float _aspectRatio;

		DirectX::XMFLOAT3A _cameraPosition;
		DirectX::XMFLOAT3A _cameraFocus;
		DirectX::XMFLOAT3A _cameraRotation;

		const DirectX::XMFLOAT4X4A _worldMatrix;
		DirectX::XMFLOAT4X4A _viewMatrix;
		DirectX::XMFLOAT4X4A _projectionMatrix;
		DirectX::XMFLOAT4X4A _orthoMatrix;
	};
}


