#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const CAABB2<Real> CAABB2<Real>::One = CAABB2<Real>(
	Vec2<Real>(Real(0), Real(0)),
	Vec2<Real>(Real(1), Real(1)));

template <class Real>
CAABB2<Real>::CAABB2()
{
}

template <class Real>
CAABB2<Real>::CAABB2(const Vec2<Real>& _center, const Vec2<Real>& size)
: center(_center), extents(size * Real(0.5))
{
}


//
//  Setters
//

template <class Real>
CAABB2<Real>& CAABB2<Real>::set(const Vec2<Real>& point)
{
	center = point;
	extents = Vec2<Real>::Zero;
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::set(const Vec2<Real>& center, const Vec2<Real>& size)
{
	this->center = center;
	this->extents = size * Real(0.5);
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::set(const AABB2<Real>& box)
{
	center = (box.inf + box.sup) * Real(0.5);
	extents = (box.sup - box.inf) * Real(0.5);
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::set(int count, const Vec2<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	const Vec2<Real>* p = points;

	Vec2<Real> inf = *p;
	Vec2<Real> sup = *p;

	p++;
	count--;

	while (count-- > 0)
	{
		if (p->x < inf.x) inf.x = p->x;
		if (p->y < inf.y) inf.y = p->y;

		if (p->x > sup.x) sup.x = p->x;
		if (p->y > sup.y) sup.y = p->y;

		p++;
	}

	return set(AABB2<Real>(inf, sup));
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::set(int count, const Vec2<Real>* points, int stride)
{
	assert(count > 0);
	assert(points != nullptr);

	const char* p = (const char*)(points);
	const Vec2<Real>* v = (const Vec2<Real>*)(p);

	Vec2<Real> inf = *v;
	Vec2<Real> sup = *v;

	p += stride;
	count--;

	while (count-- > 0)
	{
		v = (const Vec2<Real>*)(p);

		if (v->x < inf.x) inf.x = v->x;
		if (v->y < inf.y) inf.y = v->y;

		if (v->x > sup.x) sup.x = v->x;
		if (v->y > sup.y) sup.y = v->y;

		p += stride;
	}

    return set(AABB2<Real>(inf, sup));
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::add(const Vec2<Real>& point)
{
	Vec2<Real> inf = center - extents;
	Vec2<Real> sup = center + extents;

	bool outside = false;

	if (point.x < inf.x)
	{
		inf.x = point.x;
		outside = true;
	}
	if (point.y < inf.y)
	{
		inf.y = point.y;
		outside = true;
	}

	if (point.x > sup.x)
	{
		sup.x = point.x;
		outside = true;
	}
	if (point.y > sup.y)
	{
		sup.y = point.y;
		outside = true;
	}

    return outside ? set(AABB2<Real>(inf, sup)) : *this;
}


//
//  Assignments
//

template <class Real>
CAABB2<Real> CAABB2<Real>::from(const Vec2<Real>& point)
{
	CAABB2<Real> result;
	result.center = point;
	result.extents = Vec2<Real>::Zero;
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::from(const Vec2<Real>& center, const Vec2<Real>& size)
{
	CAABB2<Real> result;
	result.center = center;
	result.extents = size * Real(0.5);
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::fromInfSup(const Vec2<Real>& inf, const Vec2<Real>& sup)
{
	CAABB2<Real> result;
	result.center = (inf + sup) * Real(0.5);
	result.extents = (sup - inf) * Real(0.5);
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::from(int count, const Vec2<Real>* points)
{
	CAABB2<Real> result;
	result.set(count, points);
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::from(int count, const Vec2<Real>* points, int stride)
{
	CAABB2<Real> result;
	result.set(count, points, stride);
	return result;
}


//
//  Assignments
//

template <class Real>
CAABB2<Real>& CAABB2<Real>::operator+= (const Vec2<Real>& t)
{
	center += t;
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::operator-= (const Vec2<Real>& t)
{
	center -= t;
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::operator*= (Real k)
{
	extents *= k;
	return *this;
}

template <class Real>
CAABB2<Real>& CAABB2<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	extents /= k;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
CAABB2<Real> CAABB2<Real>::operator+ (const Vec2<Real>& t) const
{
	CAABB2<Real> result;
	result.center = center + t;
	result.extents = extents;
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::operator- (const Vec2<Real>& t) const
{
	CAABB2<Real> result;
	result.center = center - t;
	result.extents = extents;
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::operator* (Real k) const
{
	CAABB2<Real> result;
	result.center = center;
	result.extents = extents * k;
	return result;
}

template <class Real>
CAABB2<Real> CAABB2<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	CAABB2<Real> result;
	result.center = center;
	result.extents = extents / k;
	return result;
}


//
// Comparison operators
//

template <class Real>
bool CAABB2<Real>::operator==(const CAABB2<Real>& rhs) const
{
	return center == rhs.center && extents == rhs.extents;
}

template <class Real>
bool CAABB2<Real>::operator!=(const CAABB2<Real>& rhs) const
{
	return center != rhs.center || extents != rhs.extents;
}

//
// Functions
//

template <class Real>
Vec2<Real> CAABB2<Real>::inf() const
{
	return center - extents;
}

template <class Real>
Vec2<Real> CAABB2<Real>::sup() const
{
	return center + extents;
}

template <class Real>
Vec2<Real> CAABB2<Real>::size() const
{
	return extents * Real(2);
}

template <class Real>
Circle<Real> CAABB2<Real>::innerCircle() const
{
	Circle<Real> result;
	result.center = center;
	result.radius = abs(extents[extents.minorCoord()]);
	return result;
}

template <class Real>
Circle<Real> CAABB2<Real>::outerCircle() const
{
	Circle<Real> result;
	result.center = center;
	result.radius = extents.length();
	return result;
}

template <class Real>
Real CAABB2<Real>::area() const
{
	return extents.x * extents.y * Real(4);
}

template <class Real>
bool CAABB2<Real>::isNull() const
{
	return extents.isNull();
}

template <class Real>
Vec2<Real> CAABB2<Real>::pointAt(const Vec2<Real>& t) const
{
	Vec2<Real> result = center;
	result.x += extents.x * t.x;
	result.y += extents.y * t.y;
	return result;
}

template <class Real>
bool CAABB2<Real>::contains(const Vec2<Real>& point) const
{
	return (point.x >= center.x - extents.x && point.x <= center.x + extents.x)
		&& (point.y >= center.y - extents.y && point.y <= center.y + extents.y);
}

template <class Real>
bool CAABB2<Real>::contains(const CAABB2<Real>& box) const
{
	const Vec2<Real>& c = box.center;
	const Vec2<Real>& e = box.extents;
	return (c.x - e.x >= center.x - extents.x && c.x + e.x <= center.x + extents.x)
		&& (c.y - e.y >= center.y - extents.y && c.y + e.y <= center.y + extents.y);
}

template <class Real>
bool CAABB2<Real>::intersects(const CAABB2<Real>& box) const
{
	const Vec2<Real>& m1 = inf();
	const Vec2<Real>& M1 = sup();
	const Vec2<Real>& m2 = box.inf();
	const Vec2<Real>& M2 = box.sup();
	if (m2.x > M1.x || M2.x < m1.x) return false;
	if (m2.y > M1.y || M2.y < m1.y) return false;
	return true;
}

template <class Real>
template <class CastReturnType>
CAABB2<CastReturnType> CAABB2<Real>::cast() const
{
	CAABB2<CastReturnType> result;
	result.center = center.template cast<CastReturnType>();
	result.extents = extents.template cast<CastReturnType>();
	return result;
}

MATHLIB_NS_END
