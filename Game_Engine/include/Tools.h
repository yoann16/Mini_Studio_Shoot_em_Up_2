#pragma once
#include <limits>

class Timer
{
public:
	Timer(const float& timer);
	bool AutoActionIsReady(const float& framerate);
	bool ActionIsReady();
	void resetTimer();
	void setNewTimer(const float& timer);
	float getTotalTimer();
	float getCurrentTimer();
	void NextTIck(const float& framerate, const float& idx = 1);
	void PreviousTick(const float& framerate, const float& idx = 1);
	void Start();
	void Stop();
private:
	float m_TotalTimer;
	float m_CurrentTimer;
	bool m_start;
};



class Counter
{
public:
	Counter(const float& count, const float& min = std::numeric_limits<float>::min());

	Counter();

	bool AutCounterMax();

	bool CounterMax();

	void resetCounter();

	void setNewCounter(const float& max, const float& min);

	float getTotalCounter();

	float GetCurrentCounter();

	void NextTIck(const float& idx = 1);

	void PreviousTick(const float& idx = 1);

	void Start();

	void Stop();

private:
	float m_TotalCounter;
	float m_CurrentCounter;
	float m_minimalCounter;
	bool m_start;
};