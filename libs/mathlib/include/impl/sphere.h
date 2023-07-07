#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Sphere<Real> Sphere<Real>::One = Sphere<Real>(Vec3<Real>(Real(0), Real(0), Real(0)), Real(1));

//
// Constructors
//

template <class Real>
Sphere<Real>::Sphere()
{
}

template <class Real>
Sphere<Real>::Sphere(const Vec3<Real>& p, Real r)
	: center(p),
	radius(r)
{
	assert(r >= Real(0));
}


//
// Setters
//

template <class Real>
Sphere<Real>& Sphere<Real>::set(const Vec3<Real>& p, Real r)
{
	assert(r >= Real(0));
	center = p;
	radius = r;
	return *this;
}

template <class Real>
Sphere<Real>& Sphere<Real>::set(int count, const Vec3<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	Vec3<Real> inf = points[0];
	Vec3<Real> sup = points[0];

	const Vec3<Real>* p = &points[1];
	
	for (int i = 1; i < count; i++, p++)
	{
		if (p->x < inf.x) inf.x = p->x;
		if (p->y < inf.y) inf.y = p->y;
		if (p->z < inf.z) inf.z = p->z;

		if (p->x > sup.x) sup.x = p->x;
		if (p->y > sup.y) sup.y = p->y;
		if (p->z > sup.z) sup.z = p->z;
	}

	Vec3<Real> c = (inf + sup) * Real(0.5);
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


//
// Create from
//

template <class Real>
Sphere<Real> Sphere<Real>::from(const Vec3<Real>& p, Real r)
{
	assert(r >= Real(0));
	Sphere<Real> sphere;
	sphere.center = p;
	sphere.radius = r;
	return sphere;
}

template <class Real>
Sphere<Real> Sphere<Real>::from(int count, const Vec3<Real>* points)
{
	Sphere<Real> sphere;
	sphere.set(count, points);
	return sphere;
}


//
//  Assignments
//

template <class Real>
Sphere<Real>& Sphere<Real>::operator+= (const Vec3<Real>& t)
{
	center += t;
	return *this;
}

template <class Real>
Sphere<Real>& Sphere<Real>::operator-= (const Vec3<Real>& t)
{
	center -= t;
	return *this;
}

template <class Real>
Sphere<Real>& Sphere<Real>::operator*= (Real k)
{
	radius *= k;
	return *this;
}

template <class Real>
Sphere<Real>& Sphere<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	radius /= k;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
Sphere<Real> Sphere<Real>::operator+ (const Vec3<Real>& t) const
{
	return Sphere(center + t, radius);
}

template <class Real>
Sphere<Real> Sphere<Real>::operator- (const Vec3<Real>& t) const
{
	return Sphere(center - t, radius);
}

template <class Real>
Sphere<Real> Sphere<Real>::operator* (Real k) const
{
	return Sphere(center, radius * k);
}

template <class Real>
Sphere<Real> Sphere<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return Sphere(center, radius / k);
}


//
// Comparison operators
//

template <class Real>
bool Sphere<Real>::operator==(const Sphere<Real>& rhs) const
{
  return center == rhs.center && radius == rhs.radius;
}

template <class Real>
bool Sphere<Real>::operator!=(const Sphere<Real>& rhs) const
{
	return center != rhs.center || radius != rhs.radius;
}

//
//  Functions
//

template <class Real>
bool Sphere<Real>::contains(const Vec3<Real>& point) const
{
	return (distance(point, center) <= radius);
}

template <class Real>
bool Sphere<Real>::contains(const Sphere<Real>& sphere) const
{
	return (distance(sphere.center , center) <= radius - sphere.radius);
}

template <class Real>
bool Sphere<Real>::hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const
{
	return intersects(hit, t, line);
}

template <class Real>
bool Sphere<Real>::intersects(const Sphere<Real>& sphere) const
{
	Vec3<Real> delta = center - sphere.center;
	Real d2 = delta.lengthSqr();
	Real dmin = radius + sphere.radius;
	if (d2 > dmin * dmin)
		return false;

	return true;
}

template <class Real>
bool Sphere<Real>::intersects(const Line3<Real>& line) const
{
	Vec3<Real> ft = line.end - line.start;
	Real ft2 = ft.lengthSqr();
	if (ft2 == Real(0))
		return false;

	Vec3<Real> cf = line.start - center;
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
bool Sphere<Real>::intersects(Vec3<Real>& hit, Real& t, const Sphere<Real>& sphere) const
{
	Vec3<Real> delta = center - sphere.center;
	Real d2 = delta.lengthSqr();
	Real dmin = radius + sphere.radius;
	if (d2 > dmin*dmin)
		return false;

	hit = sphere.center + delta.normalized(sphere.radius);
	t = dmin - sqrt(d2);

	return true;
}

template <class Real>
bool Sphere<Real>::intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const
{
	Vec3<Real> ft = line.end - line.start;
	Real ft2 = ft.lengthSqr();
	if (ft2 == Real(0))
		return false;

	Vec3<Real> cf = line.start - center;
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
const Real* Sphere<Real>::data() const
{
	return &center.x;
}

template <class Real>
Real* Sphere<Real>::data()
{
	return &center.x;
}

template <class Real>
template <class CastReturnType>
Sphere<CastReturnType> Sphere<Real>::cast() const
{
	return Sphere<CastReturnType>(
		center.template cast<CastReturnType>(),
		static_cast<CastReturnType>(radius)
	);
}

MATHLIB_NS_END
