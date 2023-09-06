#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Circle<Real> Circle<Real>::One = Circle<Real>(Vec2<Real>(Real(0), Real(0)), Real(1));

//
// Constructors
//

template <class Real>
Circle<Real>::Circle()
{
}

template <class Real>
Circle<Real>::Circle(const Vec2<Real>& p, Real r)
	: center(p),
	radius(r)
{
	assert(r >= Real(0));
}


//
// Setters
//

template <class Real>
Circle<Real>& Circle<Real>::set(const Vec2<Real>& p, Real r)
{
	assert(r >= Real(0));
	center = p;
	radius = r;
	return *this;
}

template <class Real>
Circle<Real>& Circle<Real>::set(int count, const Vec2<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	Vec2<Real> inf = points[0];
	Vec2<Real> sup = points[0];

	const Vec2<Real>* p = &points[1];
	
	for (int i = 1; i < count; i++, p++)
	{
		if (p->x < inf.x) inf.x = p->x;
		if (p->y < inf.y) inf.y = p->y;

		if (p->x > sup.x) sup.x = p->x;
		if (p->y > sup.y) sup.y = p->y;
	}

	Vec2<Real> c = (inf + sup) * Real(0.5);
	Real radius2 = Real(0);

	p = points;

	for (int i = 0; i < count; i++, p++)
	{
		Real r2 = (*p - c).lengthSqr();
		if (r2 > radius2)
		{
			radius2 = r2;
		}
	}

	return set(c, sqrt(radius2));
}

template <class Real>
Circle<Real>& Circle<Real>::set(int count, const Vec2<Real>* points, int stride)
{
	assert(count > 0);
	assert(points != nullptr);
	assert(stride > 0);

	const char* p = (const char*)points;
	const Vec2<Real>* v = (const Vec2<Real>*)p;

	Vec2<Real> inf = *v;
	Vec2<Real> sup = *v;

	p += stride;

	for (int i = 1; i < count; i++, p += stride)
	{
		v = (const Vec2<Real>*)p;

		if (v->x < inf.x) inf.x = v->x;
		if (v->y < inf.y) inf.y = v->y;

		if (v->x > sup.x) sup.x = v->x;
		if (v->y > sup.y) sup.y = v->y;
	}

	Vec2<Real> c = (inf + sup) * Real(0.5);
	Real radius2 = Real(0);

	p = (const char*)points;

	for (int i = 0; i < count; i++, p += stride)
	{
		v = (const Vec2<Real>*)p;

		Real r2 = (*v - c).lengthSqr();
		if (r2 > radius2)
		{
			radius2 = r2;
		}
	}

	return set(c, sqrt(radius2));
}


//
// Create from
//

template <class Real>
Circle<Real> Circle<Real>::from(const Vec2<Real>& p, Real r)
{
	assert(r >= Real(0));
	Circle<Real> sphere;
	sphere.center = p;
	sphere.radius = r;
	return sphere;
}

template <class Real>
Circle<Real> Circle<Real>::from(int count, const Vec2<Real>* points)
{
	Circle<Real> sphere;
	sphere.set(count, points);
	return sphere;
}

template <class Real>
Circle<Real> Circle<Real>::from(int count, const Vec2<Real>* points, int stride)
{
	Circle<Real> sphere;
	sphere.set(count, points, stride);
	return sphere;
}


//
//  Assignments
//

template <class Real>
Circle<Real>& Circle<Real>::operator+= (const Vec2<Real>& t)
{
	center += t;
	return *this;
}

template <class Real>
Circle<Real>& Circle<Real>::operator-= (const Vec2<Real>& t)
{
	center -= t;
	return *this;
}

template <class Real>
Circle<Real>& Circle<Real>::operator*= (Real k)
{
	radius *= k;
	return *this;
}

template <class Real>
Circle<Real>& Circle<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	radius /= k;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
Circle<Real> Circle<Real>::operator+ (const Vec2<Real>& t) const
{
	return Circle(center + t, radius);
}

template <class Real>
Circle<Real> Circle<Real>::operator- (const Vec2<Real>& t) const
{
	return Circle(center - t, radius);
}

template <class Real>
Circle<Real> Circle<Real>::operator* (Real k) const
{
	return Circle(center, radius * k);
}

template <class Real>
Circle<Real> Circle<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return Circle(center, radius / k);
}


//
// Comparison operators
//

template <class Real>
bool Circle<Real>::operator==(const Circle<Real>& rhs) const
{
  return center == rhs.center && radius == rhs.radius;
}

template <class Real>
bool Circle<Real>::operator!=(const Circle<Real>& rhs) const
{
	return center != rhs.center || radius != rhs.radius;
}

//
//  Functions
//

template <class Real>
bool Circle<Real>::contains(const Vec2<Real>& point) const
{
	return (distance(point, center) <= radius);
}

template <class Real>
bool Circle<Real>::contains(const Circle<Real>& sphere) const
{
	return (distance(sphere.center , center) <= radius - sphere.radius);
}

template <class Real>
bool Circle<Real>::hits(Vec2<Real>& hit, Real& t, const Line3<Real>& line) const
{
	return intersects(hit, t, line);
}

template <class Real>
bool Circle<Real>::intersects(const Circle<Real>& sphere) const
{
	Vec2<Real> delta = center - sphere.center;
	Real d2 = delta.lengthSqr();
	Real dmin = radius + sphere.radius;
	if (d2 > dmin * dmin)
		return false;

	return true;
}

template <class Real>
bool Circle<Real>::intersects(const Line3<Real>& line) const
{
	Vec2<Real> ft = line.end - line.start;
	Real ft2 = ft.lengthSqr();
	if (ft2 == Real(0))
		return false;

	Vec2<Real> cf = line.start - center;
	Real cf2 = cf.lengthSqr();

	Real ftcf = ft * cf;

	Real r2 = radius * radius;

	Real delta = ftcf * ftcf - ft2 * (cf2 - r2);
	if (delta < Real(0))
		return false;

	Real x = (-ftcf - sqrt(delta)) / ft2;

	if (x < Real(0) || x > Real(1))
		return false;

	return true;
}

template <class Real>
bool Circle<Real>::intersects(Vec2<Real>& hit, Real& t, const Circle<Real>& sphere) const
{
	Vec2<Real> delta = center - sphere.center;
	Real d2 = delta.lengthSqr();
	Real dmin = radius + sphere.radius;
	if (d2 > dmin*dmin)
		return false;

	hit = sphere.center + delta.normalized(sphere.radius);
	t = dmin - sqrt(d2);

	return true;
}

template <class Real>
bool Circle<Real>::intersects(Vec2<Real>& hit, Real& t, const Line3<Real>& line) const
{
	Vec2<Real> ft = line.end - line.start;
	Real ft2 = ft.lengthSqr();
	if (ft2 == Real(0))
		return false;

	Vec2<Real> cf = line.start - center;
	Real cf2 = cf.lengthSqr();

	Real ftcf = ft * cf;

	Real r2	= radius * radius;

	Real delta = ftcf * ftcf - ft2 * (cf2 - r2);
	if (delta < Real(0))
		return false;

	Real x = (-ftcf - sqrt(delta)) / ft2;

	if (x < Real(0) || x > Real(1))
		return false;

	hit = line.pointAt(x);
	t = x;

	return true;
}

template <class Real>
const Real* Circle<Real>::data() const
{
	return &center.x;
}

template <class Real>
Real* Circle<Real>::data()
{
	return &center.x;
}

template <class Real>
template <class CastReturnType>
Circle<CastReturnType> Circle<Real>::cast() const
{
	return Circle<CastReturnType>(
		center.template cast<CastReturnType>(),
		static_cast<CastReturnType>(radius)
	);
}

MATHLIB_NS_END
