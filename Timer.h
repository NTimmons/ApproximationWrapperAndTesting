#pragma once

#include <chrono>
template <typename Y>
class Timer
{
	typedef std::chrono::high_resolution_clock	high_resolution_clock;
public:

	void Start() 
	{ 
		m_startTime = high_resolution_clock::now(); 
	} 

	Y GetElapsedTime()
	{ 
		return std::chrono::duration_cast<Y>(high_resolution_clock::now() - m_startTime);
	}

	template <typename T, typename Traits>
	friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, Timer<Y>& _timer)
	{
		return out << _timer.GetElapsedTime().count();
	}

	high_resolution_clock::time_point m_startTime;
};
