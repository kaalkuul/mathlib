#pragma once

MATHLIB_NS_BEGIN

template <class Real>
Ray3<Real>::Ray3()
{
}

template <class Real>
Ray3<Real> Ray3<Real>::from(const Vec3<Real>& start, const Vec3<Real>& direction)
{
	Ray3<Real> line;
	line.start = start;
	line.direction = direction.normalized();
	return line;
}

//
// Comparison operators
//

template <class Real>
bool Ray3<Real>::operator==(const Ray3<Real>& rhs) const
{
	return start == rhs.start && direction == rhs.direction;
}

template <class Real>
bool Ray3<Real>::operator!=(const Ray3<Real>& rhs) const
{
	return start != rhs.start || direction != rhs.direction;
}

//
// Functions
//

template <class Real>
Vec3<Real> Ray3<Real>::pointAt(Real dist) const
{
	return start + direction * dist;
}

template <class Real>
Real Ray3<Real>::distance(const Vec3<Real>& point) const
{
	Vec3<Real> northo = (point - start) % direction;
	Vec3<Real> n = direction % northo;
	Real l = n.normalize();
	return (l == Real(0))
		? MATHLIB_NS::distance(start, point)
		: MATHLIB_NS::abs(n * (point - start));
}

template <class Real>
template <class CastReturnType>
Ray3<CastReturnType> Ray3<Real>::cast() const
{
	return Ray3<CastReturnType>::from(
		start.template cast<CastReturnType>(),
		direction.template cast<CastReturnType>()
	);
}

MATHLIB_NS_END
