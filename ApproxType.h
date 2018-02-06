#pragma once

#define MAX(a, b) ((a) > (b) ? ( a) : (b)) 
#define MIN(a, b) ((a) > (b) ? ( b) : (a)) 

template<typename T, int AccuracyScore>
class ApproxType
{
public: 
	ApproxType()
	{
		m_data = (T)0;
	}
	ApproxType(T _in)   
	{
		m_data = _in;
	}

	~ApproxType() {}

	T Get()
	{
		return m_data;
	}

	T m_data;

	template<int AccuracyScoreIn>
	auto operator+(const ApproxType<T, AccuracyScoreIn>& _rhs) ->  ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn) >
	{
		T data = m_data + _rhs.m_data;
		return ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn)> ( data );
	}

	template< int AccuracyScoreIn>
	auto operator-(const ApproxType<T, AccuracyScoreIn>& _rhs)  ->  ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn) >
	{
		T data = m_data - _rhs.m_data;
		return ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn)>(data);
	}

	template< int AccuracyScoreIn>
	auto operator*(const ApproxType<T, AccuracyScoreIn>& _rhs) ->  ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn) >
	{
		T data = m_data * _rhs.m_data;
		return ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn)>(data);
	}

	template< int AccuracyScoreIn>
	auto operator/(const ApproxType<T, AccuracyScoreIn>& _rhs) ->  ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn) >
	{
		T data = m_data / _rhs.m_data;
		return ApproxType<T, MIN(AccuracyScore, AccuracyScoreIn)>(data);
	}

	template< int AccuracyScoreIn>
	auto operator=(const ApproxType<T, AccuracyScoreIn>& _rhs) ->  ApproxType<T,  AccuracyScoreIn >
	{
		T data = _rhs.m_data;
		return ApproxType<T, AccuracyScoreIn>(data);
	}

};


//Example of function accuracy clamping
/*
template< float func(float) >
class FuncWrapper
{
public:

	static float Call(const float& _in)
	{
		return func(_in);
	}
}

template< typename T, int accNumurator >
float sinf(ApproxType<T, accNumurator> _x)
{
	static constexpr int accuracy = 10;
	typedef std::conditional < accNumurator <= accuracy, FuncWrapper<cosApprox10>, FuncWrapper<std::sinf> >::type A;

	return A::Call(_x.Get());
}

*/