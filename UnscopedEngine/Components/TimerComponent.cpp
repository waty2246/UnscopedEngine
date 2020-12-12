#include "TimerComponent.h"
#include "TimerComponent.h"

namespace ue
{
	float ToTimeUnit(const std::chrono::duration<float,std::nano>& duration,TimeUnit timeUnit)
	{
		float result = 0.0;
		switch (timeUnit)
		{
		case TimeUnit::SECOND:
			{
				result= std::chrono::duration_cast<std::chrono::duration<float, std::deci>>(duration).count()/10.0f;
				break;
			}
		case TimeUnit::MILLISECOND:
			{
				result= std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(duration).count();
				break;
			}
		case TimeUnit::MICROSECOND:
			{
				result= std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(duration).count();
				break;
			}
		default:
			{
				result = duration.count();
				break;
			}	
		}

		if (result < 0.0)
		{
			result = 0.0;
		}

		return result;
	}

	TimerComponent::TimerComponent():
		_hasInit(false),
		_isPaused(false),
		_pausedTime(0),
		_deltaTime(0),
		_stopTime(),
		_previousTime(),
		_baseTime(),
		_time()
	{
	}

	void TimerComponent::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;
	}

	float TimerComponent::GetTotalTime(TimeUnit timeUnit)
	{
		if (_isPaused)
		{
			return ToTimeUnit((_stopTime - _baseTime) - _pausedTime,timeUnit);
		}
		else
		{
			return ToTimeUnit((_previousTime - _baseTime) - _pausedTime, timeUnit);
		}
	}

	float TimerComponent::GetFrameTime(TimeUnit timeUnit)
	{
		return ToTimeUnit(_deltaTime, timeUnit);
	}

	float TimerComponent::GetCurrentPausedTime(TimeUnit timeUnit)
	{
		if (_isPaused)
		{
			return ToTimeUnit(_time.now() - _stopTime, timeUnit);
		}

		return 0.0;
	}

	float TimerComponent::GetTotalPausedTime(TimeUnit timeUnit)
	{
		if (_isPaused)
		{
			_pausedTime += (_time.now() - _stopTime);
		}

		return ToTimeUnit(_pausedTime,timeUnit);
	}

	bool TimerComponent::IsPaused() const
	{
		return _isPaused;
	}

	void TimerComponent::Start()
	{
		_baseTime = _time.now();
		_previousTime = _baseTime;
	}

	void TimerComponent::Pause()
	{
		if (!_isPaused)
		{
			_stopTime = _time.now();
			_isPaused = true;
		}
	}

	void TimerComponent::Reset()
	{
		_isPaused = false;
		_pausedTime = std::chrono::duration<float, std::nano>(0);
		_deltaTime = _pausedTime;
		Start();
	}

	void TimerComponent::Resume()
	{
		if (_isPaused)
		{
			_previousTime = _time.now();
			_pausedTime += (_previousTime - _stopTime);
			_isPaused = false;
		}
	}

	void TimerComponent::Tick()
	{
		if (_isPaused)
		{
			_deltaTime = std::chrono::duration<float,std::nano>(0);
		}
		else
		{
			auto currentTime = _time.now();
			_deltaTime = currentTime - _previousTime;
			_previousTime = currentTime;
		}
	}
}

