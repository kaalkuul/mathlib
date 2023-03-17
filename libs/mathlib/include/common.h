#pragma once

#include <cmath>
#include <limits>

#define MATHLIB_NS mathlib

#define MATHLIB_NS_BEGIN namespace MATHLIB_NS {

#define MATHLIB_NS_END }

MATHLIB_NS_BEGIN

// Coordinates used in vectors
enum Coord : unsigned int
{
	X,
	Y,
	Z,
	NX,
	NY,
	NZ
};

enum class ResponseCurveType : unsigned int
{
	Zero = 0,
    Linear = 1,
    Parabolic = 2,
    Cubic = 3,
    Exponential = 4,
    Cosine = 5
};

template <class Real>
struct MatrixTolerance
{
	Real normal;
	Real orthogonal;
	Real identity;
};

template <class Real> class Constants;
template <class Real> class Vec2;
template <class Real> class Vec3;
template <class Real> class Vec4;
template <class Real> class Mat2;
template <class Real> class Mat3;
template <class Real> class Mat4;
template <class Real> class Mat34;
template <class Real> class Quat;
template <class Real> class ColorRGB;
template <class Real> class ColorRGBA;
template <class Real> class ColorHSV;

typedef Constants<float> Constantsf;
typedef Vec2<float> Vec2f;
typedef Vec3<float> Vec3f;
typedef Vec4<float> Vec4f;
typedef Mat2<float> Mat2f;
typedef Mat3<float> Mat3f;
typedef Mat4<float> Mat4f;
typedef Mat34<float> Mat34f;
typedef Quat<float> Quatf;
typedef ColorRGB<float> ColorRGBf;
typedef ColorRGBA<float> ColorRGBAf;
typedef ColorHSV<float> ColorHSVf;

typedef Constants<double> Constantsd;
typedef Vec2<double> Vec2d;
typedef Vec3<double> Vec3d;
typedef Vec4<double> Vec4d;
typedef Mat2<double> Mat2d;
typedef Mat3<double> Mat3d;
typedef Mat4<double> Mat4d;
typedef Mat34<double> Mat34d;
typedef Quat<double> Quatd;
typedef ColorRGB<double> ColorRGBd;
typedef ColorRGBA<double> ColorRGBAd;
typedef ColorHSV<double> ColorHSVd;

MATHLIB_NS_END
