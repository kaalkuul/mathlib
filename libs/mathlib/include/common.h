#pragma once

#include <cmath>
#include <limits>

#define MATHLIB_NS mathlib

#define MATHLIB_NS_BEGIN namespace MATHLIB_NS {

#define MATHLIB_NS_END }

MATHLIB_NS_BEGIN

// Coordinates used in vectors
enum class Coord : unsigned int
{
	X = 0,
	Y,
	Z,
	NX,
	NY,
	NZ,
    Undefined = 0xff
};

enum class ResponseCurveType : unsigned int
{
	Zero = 0,
    Linear = 1,
    Parabolic = 2,
    Cubic = 3,
    Exponential = 4,
    Cosine = 5,
    Undefined = 0xff
};

template <class Real>
struct MatrixTolerance
{
	Real normal;
	Real orthogonal;
	Real identity;
};

template <class Real> class Constants;
template <class Real> class TriDiagonal;
template <class Real> class GaussJordan;
template <class Real> class ColorRGB;
template <class Real> class ColorRGBA;
template <class Real> class ColorHSV;
template <class Real> class AABB2;
template <class Real> class AABB3;
template <class Real> class CAABB2;
template <class Real> class CAABB3;
template <class Real> class Vec2;
template <class Real> class Vec3;
template <class Real> class Vec4;
template <class Real> class Mat2;
template <class Real> class Mat3;
template <class Real> class Mat4;
template <class Real> class Mat34;
template <class Real> class Quat;
template <class Real> class Line2;
template <class Real> class Line3;
template <class Real> class Ray2;
template <class Real> class Ray3;
template <class Real> class Tri2;
template <class Real> class Plane;
template <class Real> class Circle;
template <class Real> class Sphere;
template <class Real> class HermiteSplineSegment3;
template <class Real> class BezierSegment3;
template <class Real> class BezierSegmentFwdDiff3;
template <class Real> class SplineSolver3;
template <class Real> class Frustum;

typedef Constants<float> Constantsf;
typedef TriDiagonal<float> TriDiagonalf;
typedef GaussJordan<float> GaussJordanf;
typedef ColorRGB<float> ColorRGBf;
typedef ColorRGBA<float> ColorRGBAf;
typedef ColorHSV<float> ColorHSVf;
typedef AABB2<float> AABB2f;
typedef AABB3<float> AABB3f;
typedef CAABB2<float> CAABB2f;
typedef CAABB3<float> CAABB3f;
typedef Vec2<float> Vec2f;
typedef Vec3<float> Vec3f;
typedef Vec4<float> Vec4f;
typedef Mat2<float> Mat2f;
typedef Mat3<float> Mat3f;
typedef Mat4<float> Mat4f;
typedef Mat34<float> Mat34f;
typedef Quat<float> Quatf;
typedef Line2<float> Line2f;
typedef Line3<float> Line3f;
typedef Ray2<float> Ray2f;
typedef Ray3<float> Ray3f;
typedef Tri2<float> Tri2f;
typedef Plane<float> Planef;
typedef Circle<float> Circlef;
typedef Sphere<float> Spheref;
typedef HermiteSplineSegment3<float> HermiteSplineSegment3f;
typedef BezierSegment3<float> BezierSegment3f;
typedef BezierSegmentFwdDiff3<float> BezierSegmentFwdDiff3f;
typedef SplineSolver3<float> SplineSolver3f;
typedef Frustum<float> Frustumf;

typedef Constants<double> Constantsd;
typedef TriDiagonal<double> TriDiagonald;
typedef GaussJordan<double> GaussJordand;
typedef ColorRGB<double> ColorRGBd;
typedef ColorRGBA<double> ColorRGBAd;
typedef ColorHSV<double> ColorHSVd;
typedef AABB2<double> AABB2d;
typedef AABB3<double> AABB3d;
typedef CAABB2<double> CAABB2d;
typedef CAABB3<double> CAABB3d;
typedef Vec2<double> Vec2d;
typedef Vec3<double> Vec3d;
typedef Vec4<double> Vec4d;
typedef Mat2<double> Mat2d;
typedef Mat3<double> Mat3d;
typedef Mat4<double> Mat4d;
typedef Mat34<double> Mat34d;
typedef Quat<double> Quatd;
typedef Line2<double> Line2d;
typedef Line3<double> Line3d;
typedef Ray2<double> Ray2d;
typedef Ray3<double> Ray3d;
typedef Tri2<double> Tri2d;
typedef Plane<double> Planed;
typedef Circle<double> Circled;
typedef Sphere<double> Sphered;
typedef HermiteSplineSegment3<double> HermiteSplineSegment3d;
typedef BezierSegment3<double> BezierSegment3d;
typedef BezierSegmentFwdDiff3<double> BezierSegmentFwdDiff3d;
typedef SplineSolver3<double> SplineSolver3d;
typedef Frustum<double> Frustumd;

MATHLIB_NS_END
