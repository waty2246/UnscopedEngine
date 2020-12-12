#pragma once

#include"Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	enum class TimeUnit
	{
		SECOND,
		MILLISECOND,
		MICROSECOND,
		NANOSECOND
	};

	class TimerComponent : public IInitializable
	{
	public:
		TimerComponent();

		virtual void Init(uintptr_t state) override;

		/// <summary>
		/// Total time game has played since SystemController::Run method invoked
		/// </summary>
		/// <returns></returns>
		virtual float GetTotalTime(TimeUnit timeUnit=TimeUnit::MILLISECOND);

		/// <summary>
		/// Total time between two frames
		/// </summary>
		/// <returns></returns>
		virtual float GetFrameTime(TimeUnit timeUnit = TimeUnit::MILLISECOND);

		virtual float GetCurrentPausedTime(TimeUnit timeUnit = TimeUnit::MILLISECOND);

		virtual float GetTotalPausedTime(TimeUnit timeUnit = TimeUnit::MILLISECOND);

		virtual bool IsPaused()const;

		
		virtual void Pause();
		virtual void Reset();
		virtual void Resume();
		
	protected:
		virtual void Start();
		virtual void Tick();

	private:
		bool _hasInit;
		std::chrono::high_resolution_clock _time;

		std::chrono::duration<float, std::nano> _deltaTime;
		std::chrono::duration<float, std::nano> _pausedTime;
		std::chrono::high_resolution_clock::time_point _stopTime;
		std::chrono::high_resolution_clock::time_point _previousTime;
		std::chrono::high_resolution_clock::time_point _baseTime;
		bool _isPaused;

		friend class SystemController;
	};
}