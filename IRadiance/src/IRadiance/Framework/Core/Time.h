#pragma once

#include <chrono>

namespace IRadiance
{
	struct DataTime
	{
		float dt;
		float total;
	};

	class Timer
	{
	public:
		Timer();
		void Start();
		void Update();

		float GetDelta() const;
		float GetTotal() const;
		DataTime GetTimeStep() const;
	private:
		using Time = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Time>;

		inline static TimePoint Now() { return Time::now();}
		inline static float Difference(const TimePoint& _t1, const TimePoint& _t2)
		{ return std::chrono::duration<float>(_t1 - _t2).count(); }

		TimePoint m_Current;
		TimePoint m_Start;
		TimePoint m_Last;

		float m_Dt;
		const float m_MaxDt;
	};
}
