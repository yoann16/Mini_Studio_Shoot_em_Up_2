#include "Tools.h"

Timer::Timer(const float& timer)
	:m_TotalTimer(timer)
	, m_CurrentTimer(0)
	, m_start(true)
{
}
bool Timer::AutoActionIsReady(const float& framerate)
{
	if (m_CurrentTimer >= m_TotalTimer)
	{
		resetTimer();
		return true;
	}
	NextTIck(framerate);
	return false;
}
bool Timer::ActionIsReady()
{
	if (m_CurrentTimer >= m_TotalTimer)
		return true;
	return false;
}
void Timer::resetTimer()
{
	m_CurrentTimer = 0;
}
void Timer::setNewTimer(const float& timer)
{
	m_TotalTimer = timer;
}
float Timer::getTotalTimer()
{
	return m_TotalTimer;
}
float Timer::getCurrentTimer()
{
	return m_CurrentTimer;
}
void Timer::NextTIck(const float& framerate, const float& idx)
{
	if (!m_start)
		return;

	m_CurrentTimer += framerate * idx;
	if (m_CurrentTimer >= m_TotalTimer)
		m_CurrentTimer = m_TotalTimer;
}
void Timer::PreviousTick(const float& framerate, const float& idx)
{
	if (!m_start)
		return;
	m_CurrentTimer -= framerate * idx;
	if (m_CurrentTimer <= 0)
		m_CurrentTimer = 0;
}
void Timer::Start()
{
	m_start = true;
}
void Timer::Stop()
{
	m_start = false;
}

Counter::Counter(const float& count, const float& min)
	:m_TotalCounter(count)
	, m_minimalCounter(min)
	, m_CurrentCounter(0)
	, m_start(true)
{
}
Counter::Counter()
	:m_TotalCounter(std::numeric_limits<float>::max())
	, m_minimalCounter(std::numeric_limits<float>::min())
	, m_CurrentCounter(0)
	, m_start(true)
{
}

bool Counter::AutCounterMax()
{
	if (m_CurrentCounter >= m_TotalCounter)
	{
		resetCounter();
		return true;
	}
	NextTIck();
	return false;
}
bool Counter::CounterMax()
{
	if (m_CurrentCounter >= m_TotalCounter)
		return true;
	return false;
}
void Counter::resetCounter()
{
	m_CurrentCounter = 0;
}
void Counter::setNewCounter(const float& max, const float& min)
{
	m_TotalCounter = max;
	m_minimalCounter = min;
}
float Counter::getTotalCounter()
{
	return m_TotalCounter;
}
float Counter::GetCurrentCounter()
{
	return m_CurrentCounter;
}
void Counter::NextTIck(const float& idx)
{
	if (!m_start)
		return;

	m_CurrentCounter += idx;
	if (m_CurrentCounter >= m_TotalCounter)
		m_CurrentCounter = m_TotalCounter;
}
void Counter::PreviousTick(const float& idx)
{
	if (!m_start)
		return;
	m_CurrentCounter -= idx;
	if (m_CurrentCounter <= m_minimalCounter)
		m_CurrentCounter = m_minimalCounter;
}
void Counter::Start()
{
	m_start = true;
}
void Counter::Stop()
{
	m_start = false;
}