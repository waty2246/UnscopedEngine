#include"MovementComponent.h"

namespace ue
{
	MovementComponent::MovementComponent():
		_hasInit(false),
		MAX_FORWARDSPEED_ACCELERATION_PERSEC(10.0f),
		MAX_BACKWARDSPEED_ACCELERATION_PERSEC(7.0f),
		MAX_LEFTRIGHTSPEED_ACCELERATION_PERSEC(6.0f),
		MAX_LEFTRIGHT_SPEED(350.0f),
		MAX_FORWARD_SPEED(600.0f),
		MAX_BACKWARD_SPEED(400.0f),
		MAX_SPEED_DECELERATION_PERSEC(2.0f),
		MAX_LOOKSPEED_PERSEC(0.0f),
		STOP_RATIO(0.5f),
		STOP_LOOK_RATIO(0.75f),
		SPEED_FACTOR(20.0f),
		_goForwardSpeed(0.0f),
		_goBackwardSpeed(0.0f),
		_goLeftSpeed(0.0f),
		_goRightSpeed(0.0f),
		_lookLeftSpeed(0.0f),
		_lookRightSpeed(0.0f),
		_lookUpSpeed(0.0f),
		_lookDownSpeed(0.0f),
		_straightRadians(0.0f),
		_sideRadians(0.0f),
		_frameTime(0.0f)
	{
	}

	void MovementComponent::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		_camera =this->GetService<CameraComponent>();
		_input = this->GetService<DemoInputComponent>();
		_timer = this->GetService<TimerComponent>();
	}

	void MovementComponent::Update()
	{
		_frameTime = _timer->GetFrameTime(TimeUnit::SECOND);

		this->LookLeft();
		this->LookRight();
		this->LookUp();
		this->LookDown();
		this->CalculateRotation();

		this->SimulateGravity();
		this->GoForward();
		this->GoBackward();
		this->GoLeft();
		this->GoRight();
		this->CalculatePosition();

		_lastMousePosition = _currentMousePosition;
	}

	void MovementComponent::SimulateGravity()
	{
		_goForwardSpeed -= _frameTime * MAX_SPEED_DECELERATION_PERSEC;
		_goBackwardSpeed -= _frameTime * MAX_SPEED_DECELERATION_PERSEC;
		_goLeftSpeed -= _frameTime * MAX_SPEED_DECELERATION_PERSEC;
		_goRightSpeed -= _frameTime * MAX_SPEED_DECELERATION_PERSEC;
	}

	void MovementComponent::GoForward()
	{
		auto speed = _frameTime * MAX_FORWARDSPEED_ACCELERATION_PERSEC;
		if (_input->IsMoveForward())
		{
			auto maxSpeed = _frameTime * MAX_FORWARD_SPEED;
			_goForwardSpeed += speed;
			if (_goForwardSpeed > maxSpeed)
			{
				_goForwardSpeed = maxSpeed;
			}
		}
		else
		{
			_goForwardSpeed -= speed * STOP_RATIO;
			if (_goForwardSpeed < 0.0f)
			{
				_goForwardSpeed = 0.0f;
			}
		}
	}

	void MovementComponent::GoBackward()
	{
		auto speed = _frameTime * MAX_BACKWARDSPEED_ACCELERATION_PERSEC;
		if (_input->IsMoveBackward())
		{
			auto maxSpeed = _frameTime * MAX_BACKWARD_SPEED;
			_goBackwardSpeed += speed;
			if (_goBackwardSpeed > maxSpeed)
			{
				_goBackwardSpeed = maxSpeed;
			}
		}
		else
		{
			_goBackwardSpeed -= speed * STOP_RATIO;
			if (_goBackwardSpeed < 0.0f)
			{
				_goBackwardSpeed = 0.0f;
			}
		}
	}

	void MovementComponent::GoLeft()
	{
		auto speed = _frameTime * MAX_LEFTRIGHTSPEED_ACCELERATION_PERSEC;
		if (_input->IsMoveLeft())
		{
			auto maxSpeed = _frameTime * MAX_LEFTRIGHT_SPEED;
			_goLeftSpeed += speed;
			if (_goLeftSpeed > maxSpeed)
			{
				_goLeftSpeed = maxSpeed;
			}
		}
		else
		{
			_goLeftSpeed -= speed * STOP_RATIO;
			if (_goLeftSpeed <0.0f)
			{
				_goLeftSpeed = 0.0f;
			}
		}
	}

	void MovementComponent::GoRight()
	{
		auto speed = _frameTime * MAX_LEFTRIGHTSPEED_ACCELERATION_PERSEC;
		if (_input->IsMoveRight())
		{
			auto maxSpeed = _frameTime * MAX_LEFTRIGHT_SPEED;
			_goRightSpeed += speed;
			if (_goRightSpeed > maxSpeed)
			{
				_goRightSpeed = maxSpeed;
			}
		}
		else
		{
			_goRightSpeed -= speed * STOP_RATIO;
			if (_goRightSpeed < 0.0f)
			{
				_goRightSpeed = 0.0f;
			}
		}
	}

	void MovementComponent::LookUp()
	{
	}

	void MovementComponent::LookDown()
	{
	}

	void MovementComponent::LookLeft()
	{
	}

	void MovementComponent::LookRight()
	{
	}

	void MovementComponent::CalculateRotation()
	{
		decltype(auto) focus = _camera->GetFocus();

		DirectX::XMVECTOR xy = DirectX::XMLoadFloat3A(&focus);
		xy = DirectX::XMVector2Normalize(xy);
		DirectX::XMVECTOR x = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT2 dotProductResult;
		DirectX::XMStoreFloat2(&dotProductResult,DirectX::XMVector2Dot(xy, x));

		_straightRadians = acosf(dotProductResult.x);
		_sideRadians = DirectX::XM_PIDIV2 - _straightRadians;
	}

	void MovementComponent::CalculatePosition()
	{
		auto straightSpeed = (_goForwardSpeed - _goBackwardSpeed)/SPEED_FACTOR;
		auto sideSpeed = (_goLeftSpeed - _goRightSpeed)/SPEED_FACTOR;

		auto cameraPosition=_camera->GetPosition();
		cameraPosition.x += cosf(_straightRadians) * straightSpeed - cosf(_sideRadians) * sideSpeed;
		cameraPosition.z += sinf(_straightRadians) * straightSpeed - sinf(_sideRadians) * sideSpeed;

		_camera->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	}

}
