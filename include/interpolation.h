#pragma once

MATHLIB_NS_BEGIN

enum class InterpolationMode
{
	Linear,
	Parabolic,
	Cubic,
	Exponential,
	Cosine,
	QuadraticIn,
	QuadraticOut,
	QuadraticInOut,
	CubicIn,
	CubicOut,
	CubicInOut,
	QuarticIn,
	QuarticOut,
	QuarticInOut,
	QuinticIn,
	QuinticOut,
	QuinticInOut,
	SinusoidalIn,
	SinusoidalOut,
	SinusoidalInOut,
	ExponentialIn,
	ExponentialOut,
	ExponentialInOut,
	Exponential2In,
	Exponential2Out,
	Exponential2InOut,
	CircularIn,
	CircularOut,
	CircularInOut
};

const float POW_2_M10 = 0.000976563f;
const float POW_2_0 = 1.0f;
const float POW_2_10 = 1024.0f;

const float INV_POW_2_0_MINUS_POW_2_M10 = 1.00098f;

template <class Real>
inline Real interpolationRatio(Real t, InterpolationMode mode)
{
	if (t <= Real(0))
		return Real(0);
	else if (t >= Real(1))
		return Real(1);

	switch (mode)
	{
	case InterpolationMode::Parabolic:	return t * t;
	case InterpolationMode::Cubic:	return t * t * t;
	case InterpolationMode::Exponential:	return pow(Real(2), t) - Real(1);
	case InterpolationMode::Cosine:	return (Real(1) - cos(t * Constants<Real>::PI_OVER_2));

	case InterpolationMode::Linear:	return t;

	case InterpolationMode::QuadraticIn:	return t * t;
	case InterpolationMode::QuadraticOut:	return t * (Real(2) - t);
	case InterpolationMode::QuadraticInOut:	return (t < Real(0.5))
		? Real(2) * t * t
		: (-Real(2) * t + Real(4)) * t - Real(1);

	case InterpolationMode::CubicIn:	return t * t * t;
	case InterpolationMode::CubicOut:	return t * (t * (t - Real(3)) + Real(3));
	case InterpolationMode::CubicInOut:	return (t < Real(0.5))
		? Real(4) * t * t * t
		: ((Real(4) * t - Real(12)) * t + Real(12)) * t - Real(3);

	case InterpolationMode::QuarticIn:	return t * t * t * t;
	case InterpolationMode::QuarticOut: {
		float t0 = t - Real(1);
		return -t0 * t0 * t0 * t0 + Real(1);
	}
	case InterpolationMode::QuarticInOut: {
		float t0 = Real(2) * t - Real(2);
		return (t < Real(0.5))
			? Real(8) * t * t * t * t
			: -Real(0.5) * (t0 * t0 * t0 * t0 - Real(2));
	}

	case InterpolationMode::QuinticIn:	return t * t * t * t * t;
	case InterpolationMode::QuinticOut: {
		float t0 = t - Real(1);
		return t0 * t0 * t0 * t0 * t0 + Real(1);
	}
	case InterpolationMode::QuinticInOut: {
		float t0 = Real(2) * t - Real(2);
		return (t < Real(0.5))
			? 16.0f * t * t * t * t * t
			: Real(0.5) * (t0 * t0 * t0 * t0 * t0 + Real(2));
	}

	case InterpolationMode::SinusoidalIn:	return Real(1) - cos(t * Constants<Real>::PI_OVER_2);
	case InterpolationMode::SinusoidalOut:	return sin(t * Constants<Real>::PI_OVER_2);
	case InterpolationMode::SinusoidalInOut:	return Real(0.5) * (Real(1) - cos(t * Constants<Real>::PI));

	case InterpolationMode::ExponentialIn:	return (pow(Real(2), Real(10) * (t - Real(1))) - POW_2_M10) * INV_POW_2_0_MINUS_POW_2_M10;
	case InterpolationMode::ExponentialOut:	return Real(1) - (pow(Real(2), -Real(10) * t) - POW_2_M10) * INV_POW_2_0_MINUS_POW_2_M10;
	case InterpolationMode::ExponentialInOut:	return (t < Real(0.5))
		? Real(0.5) * ((pow(Real(2), Real(20) * t - Real(10)) - POW_2_M10) * INV_POW_2_0_MINUS_POW_2_M10)
		: Real(0.5) * (Real(2) - (pow(Real(2), Real(10) - Real(20) * t) - POW_2_M10) * INV_POW_2_0_MINUS_POW_2_M10);

	case InterpolationMode::Exponential2In:	return pow(Real(2), Real(20) * (t - Real(1)));
	case InterpolationMode::Exponential2Out:	return Real(1) - pow(Real(2), -Real(20) * t);
	case InterpolationMode::Exponential2InOut:	return (t < Real(0.5))
		? Real(0.5) * pow(Real(2), Real(40) * t - Real(20))
		: Real(0.5) * (Real(2) - pow(Real(2), Real(20) - Real(40) * t));

	case InterpolationMode::CircularIn:	return Real(1) - sqrt(Real(1) - t * t);
	case InterpolationMode::CircularOut:	return sqrt(Real(1) - (t - Real(1)) * (t - Real(1)));
	case InterpolationMode::CircularInOut:	return (t < Real(0.5))
		? Real(0.5) * (Real(1) - sqrt(Real(1) - Real(4) * t * t))
		: Real(0.5) * (sqrt(Real(1) - (Real(4) * t - Real(8)) * t - Real(4)) + Real(1));

	default:
		assert(0);
	}

	return t;
}

template <class Real>
inline int lerp(int from, int to, Real ratio)
{
	return from + int(ratio * (to - from));
}

template <class Real>
inline Real lerp(Real from, Real to, Real ratio)
{
	Real delta = to - from;
	return from + delta * ratio;
}

template <class Real>
Vec2<Real> lerp(const Vec2<Real>& from, const Vec2<Real>& to, Real ratio)
{
	return Vec2<Real>(from.x + (to.x - from.x) * ratio,
		from.y + (to.y - from.y) * ratio);
}

template <class Real>
Vec3<Real> lerp(const Vec3<Real>& from, const Vec3<Real>& to, Real ratio)
{
	return Vec3<Real>(from.x + (to.x - from.x) * ratio,
		from.y + (to.y - from.y) * ratio,
		from.z + (to.z - from.z) * ratio);
}

template <class Real>
int lerp(int from, int to, Real ratio, InterpolationMode mode)
{
	return lerp(from, to, interpolationRatio(ratio, mode));
}

template <class Real>
Real lerp(Real from, Real to, Real ratio, InterpolationMode mode)
{
	return lerp(from, to, interpolationRatio(ratio, mode));
}

template <class Real>
Vec2<Real> lerp(const Vec2<Real>& from, const Vec2<Real>& to, Real ratio, InterpolationMode mode)
{
	return lerp(from, to, interpolationRatio(ratio, mode));
}

template <class Real>
Vec3<Real> lerp(const Vec3<Real>& from, const Vec3<Real>& to, Real ratio, InterpolationMode mode)
{
	return lerp(from, to, interpolationRatio(ratio, mode));
}

template <class Real>
Real clerp(Real from, Real to, Real ratio)
{
	Real delta = fmod(to - from + Constants<Real>::PI, Constants<Real>::PI_TIMES_2) - Constants<Real>::PI;
	return from + delta * ratio;
}

template <class Real>
Real clerpMaxAngle(Real from, Real to, Real maxAngle)
{
	Real delta = fmod(to - from + Constants<Real>::PI, Constants<Real>::PI_TIMES_2) - Constants<Real>::PI;
	Real angle = (delta >= 0)
		? (from + ((delta > maxAngle) ? maxAngle : delta))
		: (from + ((delta < -maxAngle) ? -maxAngle : delta));
	return angle;
}

template <class Real>
Real clerpMaxAngle(Real from, Real to, Real maxAngle, Real& ratio)
{
	Real delta = fmod(to - from + Constants<Real>::PI, Constants<Real>::PI_TIMES_2) - Constants<Real>::PI;
	Real angle = (delta >= 0)
		? (from + ((delta > maxAngle) ? maxAngle : delta))
		: (from + ((delta < -maxAngle) ? -maxAngle : delta));
	ratio = angle / delta;
	return angle;
}

MATHLIB_NS_END
