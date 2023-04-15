#pragma once

MATHLIB_NS_BEGIN

template <class Real>
Line2<Real>::Line2()
{
}

template <class Real>
Line2<Real> Line2<Real>::from(const Vec2<Real>& start, const Vec2<Real>& end)
{
	Line2<Real> line;
	line.start = start;
	line.end = end;
	return line;
}

//
// Comparison operators
//

template <class Real>
bool Line2<Real>::operator==(const Line2<Real>& rhs) const
{
	return start == rhs.start && end == rhs.end;
}

template <class Real>
bool Line2<Real>::operator!=(const Line2<Real>& rhs) const
{
	return start != rhs.start || end != rhs.end;
}

//
// Functions
//

template <class Real>
Real Line2<Real>::length() const
{
	return (end - start).length();
}

template <class Real>
Real Line2<Real>::lengthSqr() const
{
	return (end - start).lengthSqr();
}

template <class Real>
bool Line2<Real>::isNull() const
{
	return end == start;
}

template <class Real>
Vec2<Real> Line2<Real>::pointAt(Real t) const
{
	return lerp(start, end, t);	
}

template <class Real>
Real Line2<Real>::distance(const Vec2<Real> &point) const
{
	Vec2<Real> d = end - start;
	Real l = d.normalize();
	return (l == Real(0))
		? MATHLIB_NS::distance(start, point)
		: abs(-d.y * (point.x - start.x) + d.x * (point.y - start.y));
}

template <class Real>
template <class CastReturnType>
Line2<CastReturnType> Line2<Real>::cast() const
{
	return Line2<CastReturnType>::from(
		start.cast<CastReturnType>(),
		end.cast<CastReturnType>()
	);
}

MATHLIB_NS_END
