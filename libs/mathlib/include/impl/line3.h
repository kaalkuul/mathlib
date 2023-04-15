#pragma once

MATHLIB_NS_BEGIN

template <class Real>
Line3<Real>::Line3()
{
}

template <class Real>
Line3<Real> Line3<Real>::from(const Vec3<Real>& start, const Vec3<Real>& end)
{
	Line3<Real> line;
	line.start = start;
	line.end = end;
	return line;
}

//
// Comparison operators
//

template <class Real>
bool Line3<Real>::operator==(const Line3<Real>& rhs) const
{
	return start == rhs.start && end == rhs.end;
}

template <class Real>
bool Line3<Real>::operator!=(const Line3<Real>& rhs) const
{
	return start != rhs.start || end != rhs.end;
}

//
// Functions
//

template <class Real>
Real Line3<Real>::length() const
{
	return (end - start).length();
}

template <class Real>
Real Line3<Real>::lengthSqr() const
{
	return (end - start).lengthSqr();
}

template <class Real>
bool Line3<Real>::isNull() const
{
	return end == start;
}

template <class Real>
Vec3<Real> Line3<Real>::pointAt(Real t) const
{
	return lerp(start, end, t);	
}

template <class Real>
Real Line3<Real>::distance(const Vec3<Real>& point) const
{
	Vec3<Real> d = end - start;
	Vec3<Real> northo = (point - start) % d;
	Vec3<Real> n = d % northo;
	Real l = n.normalize();
	return (l == Real(0))
		? MATHLIB_NS::distance(start, point)
		: abs(n * (point - start));
}

template <class Real>
template <class CastReturnType>
Line3<CastReturnType> Line3<Real>::cast() const
{
	return Line3<CastReturnType>::from(
		start.template cast<CastReturnType>(),
		end.template cast<CastReturnType>()
	);
}

MATHLIB_NS_END
