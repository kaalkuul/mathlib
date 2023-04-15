#pragma once

MATHLIB_NS_BEGIN

template <class Real>
Ray2<Real>::Ray2()
{
}

template <class Real>
Ray2<Real> Ray2<Real>::from(const Vec2<Real>& start, const Vec2<Real>& direction)
{
	Ray2<Real> line;
	line.start = start;
	line.direction = direction.normalized();
	return line;
}

//
// Comparison operators
//

template <class Real>
bool Ray2<Real>::operator==(const Ray2<Real>& rhs) const
{
	return start == rhs.start && direction == rhs.direction;
}

template <class Real>
bool Ray2<Real>::operator!=(const Ray2<Real>& rhs) const
{
	return start != rhs.start || direction != rhs.direction;
}

//
// Functions
//

template <class Real>
Vec2<Real> Ray2<Real>::pointAt(Real dist) const
{
	return start + direction * dist;
}

template <class Real>
Real Ray2<Real>::distance(const Vec2<Real> &point) const
{
	return MATHLIB_NS::abs(-direction.y * (point.x - start.x) + direction.x * (point.y - start.y));
}

template <class Real>
template <class CastReturnType>
Ray2<CastReturnType> Ray2<Real>::cast() const
{
	return Ray2<CastReturnType>::from(
		start.template cast<CastReturnType>(),
		direction.template cast<CastReturnType>()
	);
}

MATHLIB_NS_END
