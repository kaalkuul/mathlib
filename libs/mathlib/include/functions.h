#pragma once

#include <cassert>

MATHLIB_NS_BEGIN

template <class Real>
Real degreeToRadian(Real x)
{
	return x * Constants<Real>::PI / Real(180);
}

template <class Real>
Real radianToDegree(Real x)
{
	return x * Real(180) / Constants<Real>::PI;
}

template <class Real>
Real asin(Real s)
{
	if (s > Real(1))
		s = Real(1);
	if (s < Real(-1))
		s = Real(-1);
	return (Real)::asin(s);
}

template <class Real>
Real acos(Real c)
{
	if (c > Real(1))
		c = Real(1);
	if (c < Real(-1))
		c = Real(-1);
	return (Real)::acos(c);
}

inline int rand(int n)
{
	return ::rand() % n;
}

inline int randBetween(int from, int to)
{
	return from + (::rand() % (to - from));
}

inline int randAmplitude(int n)
{
	return (::rand() % (2 * n)) - n;
}

inline int randAmplitude(int from, int to)
{
	int delta = to - from;
	int r = (::rand() % (2 * delta)) - delta;
	return (r >= 0) ? from + r : -from + r;
}

template <class Real>
Real rand(Real f)
{
	return Real(::rand()) * (f / Real(RAND_MAX));
}

template <class Real>
Real randBetween(Real from, Real to)
{
	return from + Real(::rand()) * (to - from) / Real(RAND_MAX);
}

template <class Real>
Real randAmplitude(Real f)
{
	return (Real(::rand()) * (Real(2) / Real(RAND_MAX)) - Real(1)) * f;
}

template <class Real>
Real randAmplitude(Real from, Real to)
{
	int r = ::rand();
	return (r >= 0)
		? (from + Real(r) * (to - from) / Real(RAND_MAX))
		: -(from + Real(r) * (to - from) / Real(RAND_MAX));
}

template <class Real>
Real fmod(Real x, Real y)
{
	assert(y != Real(0));
	return ::fmod(x, y);
}

template <class Real>
Real fmodPositive(Real x, Real y)
{
	assert(y > Real(0));
	Real r = ::fmod(x, y);
	return (r >= Real(0)) ? r : y + r;
}

template <class Real>
Real fmodCentered(Real x, Real y)
{
	Real y_2 = y * Real(0.5);
	return fmodPositive(x + y_2, y) - y_2;
}


template <class Real>
Real distance(const Vec2<Real> &a, const Vec2<Real> &b)
{
	Real x = b.x - a.x;
	Real y = b.y - a.y;
	return sqrt(x * x + y * y);
}

template <class Real>
Real distanceSqr(const Vec2<Real> &a, const Vec2<Real> &b)
{
	Real x = b.x - a.x;
	Real y = b.y - a.y;
	return x * x + y * y;
}

template <class Real>
Real distance(const Vec3<Real> &a, const Vec3<Real> &b)
{
	Real x = b.x - a.x;
	Real y = b.y - a.y;
	Real z = b.z - a.z;
	return sqrt(x * x + y * y + z * z);
}

template <class Real>
Real distanceSqr(const Vec3<Real> &a, const Vec3<Real> &b)
{
	Real x = b.x - a.x;
	Real y = b.y - a.y;
	Real z = b.z - a.z;
	return x * x + y * y + z * z;
}


inline int min(int a, int b)
{
	return (a < b) ? a : b;
}

template <class Real>
Real min(Real a, Real b)
{
	return (a < b) ? a : b;
}


inline int max(int a, int b)
{
	return (a > b) ? a : b;
}

template <class Real>
Real max(Real a, Real b)
{
	return (a > b) ? a : b;
}


inline int clippedBetween(int value, int a, int b)
{
	return (value > b)
		? b
		: (value < a) ? a : value;
}

template <class Real>
Real clippedBetween(Real value, Real a, Real b)
{
	return (value > b)
		? b
		: (value < a) ? a : value;
}

template <class Real>
Real evaluate(Real value, Real threshold, ResponseCurveType curveType)
{
	assert(threshold >= Real(0) && threshold < Real(1));

	if (value >= -threshold && value <= threshold)
	{
		value = Real(0);
	}
	else
	{
		value = (value >= Real(0))
			? (value - threshold) / (Real(1) - threshold)
			: (value + threshold) / (Real(1) - threshold);
	}

	Real result;

	switch (curveType)
	{
	case ResponseCurveType::Zero:
		result = Real(0);
		break;
	case ResponseCurveType::Linear:
		result = value;
		break;
	case ResponseCurveType::Parabolic:
		result = (value >= Real(0))
			? value * value
			: -value * value;
		break;
	case ResponseCurveType::Cubic:
		result = value * value * value;
		break;
	case ResponseCurveType::Exponential:
		result = (value >= Real(0))
			? pow(2.0f, value) - Real(1)
			: -(pow(2.0f, -value) - Real(1));
		break;
	case ResponseCurveType::Cosine:
		result = (value >= Real(0))
			? (
				(value >= Real(1))
					? Real(1)
					: (Real(1) - ::cos(value * Real(1.57079633))) / (Real(1) - ::cos(Real(1.57079633)))
			) : (
				(value <= Real(-1))
					? Real(-1)
					: -(Real(1) - ::cos((-value) * Real(1.57079633))) / (Real(1) - ::cos(Real(1.57079633)))
			);
		break;
	default:
		assert(0);
		result = Real(0);
	}
	
	return result;
}

MATHLIB_NS_END
