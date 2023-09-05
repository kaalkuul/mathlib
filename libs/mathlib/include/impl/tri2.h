#pragma once

MATHLIB_NS_BEGIN

template <class Real>
Tri2<Real>::Tri2()
{
}

template <class Real>
Tri2<Real> Tri2<Real>::from(const Vec2<Real>& a, const Vec2<Real>& b, const Vec2<Real>& c)
{
	Tri2<Real> result;
	result.a = a;
	result.b = b;
	result.c = c;
	return result;
}

//
// Comparison operators
//

template <class Real>
bool Tri2<Real>::operator==(const Tri2<Real>& rhs) const
{
	return a == rhs.a && b == rhs.b && c == rhs.c;
}

template <class Real>
bool Tri2<Real>::operator!=(const Tri2<Real>& rhs) const
{
	return a != rhs.a || b != rhs.b || c != rhs.c;
}

//
// Functions
//

template <class Real>
bool Tri2<Real>::contains(const Vec2<Real> &p) const
{
    Real cross1 = Vec2<Real>::crossProduct(a, b, p);
    Real cross2 = Vec2<Real>::crossProduct(b, c, p);
    Real cross3 = Vec2<Real>::crossProduct(c, a, p);

    return (cross1 >= Real(0) && cross2 >= Real(0) && cross3 >= Real(0))
		|| (cross1 <= Real(0) && cross2 <= Real(0) && cross3 <= Real(0));
}

template <class Real>
template <class CastReturnType>
Tri2<CastReturnType> Tri2<Real>::cast() const
{
	return Tri2<CastReturnType>::from(
		a.template cast<CastReturnType>(),
		b.template cast<CastReturnType>(),
		c.template cast<CastReturnType>()
	);
}

MATHLIB_NS_END
