#pragma once

#include"Common.h"
#include"Core/ServiceConsumer.h"
#include"Components/CameraComponent.h"
#include"DemoInputComponent.h"
#include"Components/TimerComponent.h"
#include"Graphics/Point.h"
#include"Core/IInitializable.h"

namespace ue
{
	class MovementComponent: public IInitializable, public ServiceConsumer
	{
	public:
		MovementComponent();

		virtual void Init(uintptr_t state) override;
		virtual void Update();

	private:
		void SimulateGravity();
		void GoForward();
		void GoBackward();
		void GoLeft();
		void GoRight();
		void LookUp();
		void LookDown();
		void LookLeft();
		void LookRight();
		void CalculateRotation();
		void CalculatePosition();

	private:
		bool _hasInit;

		const float MAX_FORWARDSPEED_ACCELERATION_PERSEC;
		const float MAX_BACKWARDSPEED_ACCELERATION_PERSEC;
		const float MAX_LEFTRIGHTSPEED_ACCELERATION_PERSEC;
		const float MAX_FORWARD_SPEED;
		const float MAX_BACKWARD_SPEED;
		const float MAX_LEFTRIGHT_SPEED;
		const float MAX_SPEED_DECELERATION_PERSEC;
		const float MAX_LOOKSPEED_PERSEC;
		const float STOP_RATIO;
		const float STOP_LOOK_RATIO;
		const float SPEED_FACTOR;

		float _goForwardSpeed;
		float _goBackwardSpeed;
		float _goLeftSpeed;
		float _goRightSpeed;
		float _lookLeftSpeed;
		float _lookRightSpeed;
		float _lookUpSpeed;
		float _lookDownSpeed;
		float _straightRadians;
		float _sideRadians;

		float _frameTime;

		Point2D<int> _currentMousePosition;
		Point2D<int> _lastMousePosition;

		ServicePtr<CameraComponent> _camera;
		ServicePtr<DemoInputComponent> _input;
		ServicePtr<TimerComponent> _timer;
	};
}
