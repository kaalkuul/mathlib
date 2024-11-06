#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const AABB2<Real> AABB2<Real>::One = AABB2<Real>(
	Vec2<Real>(Real(-0.5), Real(-0.5)),
	Vec2<Real>(Real(0.5), Real(0.5)));

template <class Real>
AABB2<Real>::AABB2()
{
}

template <class Real>
AABB2<Real>::AABB2(const Vec2<Real>& _inf, const Vec2<Real>& _sup)
: inf(_inf), sup(_sup)
{
}


//
//  Setters
//

template <class Real>
AABB2<Real>& AABB2<Real>::set(const Vec2<Real>& point)
{
	inf = sup = point;
	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::set(const Vec2<Real>& inf, const Vec2<Real>& sup)
{
	this->inf = inf;
    this->sup = sup;
	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::set(const CAABB2<Real>& box)
{
	inf = box.inf();
	sup = box.sup();
	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::set(int count, const Vec2<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	const Vec2<Real>* p = points;

	inf = *p;
	sup = *p;

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
    
    return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::set(int count, const Vec2<Real>* points, int stride)
{
	assert(count > 0);
	assert(points != nullptr);

	const char* p = (const char*)(points);
	const Vec2<Real>* v = (const Vec2<Real>*)(p);

	inf = *v;
	sup = *v;

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

	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::add(const Vec2<Real>& point)
{
	if (point.x < inf.x)
	{
		inf.x = point.x;
	}
	if (point.y < inf.y)
	{
		inf.y = point.y;
	}

	if (point.x > sup.x)
	{
		sup.x = point.x;
	}
	if (point.y > sup.y)
	{
		sup.y = point.y;
	}

	return *this;
}


//
//  Assignments
//

template <class Real>
AABB2<Real> AABB2<Real>::from(const Vec2<Real>& point)
{
	AABB2<Real> result;
	result.inf = point;
	result.sup = point;
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::from(const Vec2<Real>& inf, const Vec2<Real>& sup)
{
	AABB2<Real> result;
	result.inf = inf;
	result.sup = sup;
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::from(const CAABB2<Real>& box)
{
	AABB2<Real> result;
	result.inf = box.inf();
	result.sup = box.sup();
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::from(int count, const Vec2<Real>* points)
{
	AABB2<Real> result;
	result.set(count, points);
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::from(int count, const Vec2<Real>* points, int stride)
{
	AABB2<Real> result;
	result.set(count, points, stride);
	return result;
}


//
//  Assignments
//

template <class Real>
AABB2<Real>& AABB2<Real>::operator+= (const Vec2<Real>& t)
{
	inf += t;
    sup += t;
	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::operator-= (const Vec2<Real>& t)
{
	inf -= t;
    sup -= t;
	return *this;
}

template <class Real>
AABB2<Real>& AABB2<Real>::operator*= (Real k)
{
	return scaleCentered(k);
}

template <class Real>
AABB2<Real>& AABB2<Real>::operator/= (Real k)
{
	assert(k != Real(0));
    return scaleCentered(Real(1) / k);
}


//
// Arithmetic operators
//

template <class Real>
AABB2<Real> AABB2<Real>::operator+ (const Vec2<Real>& t) const
{
	AABB2<Real> result;
	result.inf = inf + t;
	result.sup = sup + t;
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::operator- (const Vec2<Real>& t) const
{
	AABB2<Real> result;
    result.inf = inf - t;
    result.sup = sup - t;
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::operator* (Real k) const
{
	AABB2<Real> result(inf, sup);
    result.scaleCentered(k);
	return result;
}

template <class Real>
AABB2<Real> AABB2<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
    AABB2<Real> result(inf, sup);
    result.scaleCentered(Real(1) / k);
	return result;
}


//
// Comparison operators
//

template <class Real>
bool AABB2<Real>::operator==(const AABB2<Real>& rhs) const
{
	return inf == rhs.inf && sup == rhs.sup;
}

template <class Real>
bool AABB2<Real>::operator!=(const AABB2<Real>& rhs) const
{
	return inf != rhs.inf || sup != rhs.sup;
}


//
// Transformations
//

template <class Real>
AABB2<Real>& AABB2<Real>::scaleCentered(Real k)
{
    CAABB2<Real> box;
    box.center = (inf + sup) * Real(0.5);
    box.extents = (sup - inf) * Real(0.5) * k;
    return set(box);
}


//
// Functions
//

template <class Real>
Vec2<Real> AABB2<Real>::center() const
{
	return (inf + sup) * Real(0.5);
}

template <class Real>
Vec2<Real> AABB2<Real>::extents() const
{
	return (sup - inf) * Real(0.5);
}

template <class Real>
Vec2<Real> AABB2<Real>::size() const
{
	return sup - inf;
}

template <class Real>
Circle<Real> AABB2<Real>::innerCircle() const
{
    Vec2<Real> extents = (sup - inf) * Real(0.5);
    
	Circle<Real> result;
	result.center = center();
	result.radius = abs(extents[extents.minorCoord()]);
	return result;
}

template <class Real>
Circle<Real> AABB2<Real>::outerCircle() const
{
    Vec2<Real> extents = (sup - inf) * Real(0.5);
    
	Circle<Real> result;
	result.center = center();
	result.radius = extents.length();
	return result;
}

template <class Real>
Real AABB2<Real>::area() const
{
	return (sup.x - inf.x) * (sup.y - inf.y);
}

template <class Real>
bool AABB2<Real>::isNull() const
{
	return sup == inf;
}

template <class Real>
Vec2<Real> AABB2<Real>::pointAt(const Vec2<Real>& t) const
{
	Vec2<Real> result = inf;
	result.x += (sup.x - inf.x) * t.x;
	result.y += (sup.y - inf.y) * t.y;
	return result;
}

template <class Real>
bool AABB2<Real>::contains(const Vec2<Real>& point) const
{
	return (point.x >= inf.x && point.x <= sup.x)
		&& (point.y >= inf.y && point.y <= sup.y);
}

template <class Real>
bool AABB2<Real>::contains(const AABB2<Real>& box) const
{
	return (box.inf.x >= inf.x && box.sup.x <= sup.x)
		&& (box.inf.y >= inf.y && box.sup.y <= sup.y);
}

template <class Real>
bool AABB2<Real>::intersects(const AABB2<Real>& box) const
{
	if (box.inf.x > sup.x || box.sup.x < inf.x) return false;
	if (box.inf.y > sup.y || box.sup.y < inf.y) return false;
	return true;
}

template <class Real>
template <class CastReturnType>
AABB2<CastReturnType> AABB2<Real>::cast() const
{
	AABB2<CastReturnType> result;
	result.inf = inf.template cast<CastReturnType>();
	result.sup = sup.template cast<CastReturnType>();
	return result;
}

MATHLIB_NS_END
