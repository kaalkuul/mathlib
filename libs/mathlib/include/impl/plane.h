#pragma once

MATHLIB_NS_BEGIN


template <class Real>
const Plane<Real> Plane<Real>::XY = Plane<Real>(Vec3<Real>(Real(0), Real(0), Real(1)), Real(0));

template <class Real>
const Plane<Real> Plane<Real>::YZ = Plane<Real>(Vec3<Real>(Real(1), Real(0), Real(0)), Real(0));

template <class Real>
const Plane<Real> Plane<Real>::ZX = Plane<Real>(Vec3<Real>(Real(0), Real(1), Real(1)), Real(0));


template <class Real>
Plane<Real>::Plane()
{
}

template <class Real>
Plane<Real>::Plane(const Vec3<Real>& n, Real distance)
:	normal(n),
	d(distance)
{
}

// Creates a plane from a point and a normal
template <class Real>
Plane<Real> Plane<Real>::from(const Vec3<Real>& point, const Vec3<Real>& normal)
{
	Plane<Real> plane;
	plane.normal = normal.normalized();
	plane.d = -(plane.normal * point);
	return plane;
}

// Creates a plane going through the points a, b and c
template <class Real>
Plane<Real> Plane<Real>::from(const Vec3<Real>& a, const Vec3<Real>& b, const Vec3<Real>& c)
{
	Vec3<Real> ab = b - a;
	Vec3<Real> ac = c - a;

	Vec3<Real> n = ab % ac;

	return from(a, n);
}

// Creates a plane // to another, at a distance
template <class Real>
Plane<Real> Plane<Real>::from(const Plane& plane, Real distance)
{
	Plane<Real> result;
	result.normal = plane.normal;
	result.d = plane.d + distance;
	return result;
}

//
// Comparison operators
//

template <class Real>
bool Plane<Real>::operator==(const Plane<Real>& rhs) const
{
	return normal == rhs.normal && d == rhs.d;
}

template <class Real>
bool Plane<Real>::operator!=(const Plane<Real>& rhs) const
{
	return normal != rhs.normal || d != rhs.d;
}

//
//  Functions
//

template <class Real>
bool Plane<Real>::contains(const Vec3<Real>& p, Real tolerance) const
{
	Real d = distance(p);
	return MATHLIB_NS::abs(d) <= tolerance;
}

template <class Real>
Real Plane<Real>::distance(const Vec3<Real>& point) const
{
	return point * normal + d;
}

template <class Real>
Real Plane<Real>::project(Vec3<Real>& projection, const Vec3<Real>& point) const
{
	Real t = point * normal + d;

	projection.x = point.x - normal.x * t;
	projection.y = point.y - normal.y * t;
	projection.z = point.z - normal.z * t;

	return t;
}

template <class Real>
bool Plane<Real>::project(Vec3<Real>& projection, const Vec3<Real>& point, const Vec3<Real>& direction) const
{
	Real f = direction * normal;

	if (f == Real(0))
		return false;

	projection = point - direction * ((point * normal) / f);

	return true;
}

template <class Real>
bool Plane<Real>::hits(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray) const
{
	Real startDist = ray.start * normal + d;

	Real normalDotDir = normal * ray.direction;
	if (normalDotDir >= Real(0))
		return false;

	Real dist = - startDist / normalDotDir;
	if (dist < Real(0))
		return false;

	hit = ray.pointAt(dist);
	t = dist;

	return true;
}

template <class Real>
bool Plane<Real>::hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const
{
	Real startDist = line.start * normal + d;
	Real endDist = line.end * normal + d;

	if (startDist < Real(0))
		return false;

	if (endDist >= Real(0))
		return false;

	t = startDist / (startDist - endDist);

	hit = line.pointAt(t);

	return true;
}

template <class Real>
bool Plane<Real>::hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line, Real radius) const
{
	Real startDist = line.start * normal + d - radius;
	Real endDist = line.end * normal + d - radius;

	if (startDist < Real(0))
		return false;

	if (endDist >= Real(0))
		return false;

	t = startDist / (startDist - endDist);

	hit = line.pointAt(t);

	return true;
}

template <class Real>
bool Plane<Real>::hits(Real& depth, const Sphere<Real>& sphere) const
{
	Real dist = sphere.center * normal + d;

	if (dist > sphere.radius)
		return false;

	if (dist < Real(0))
		return false;

	depth = sphere.radius - dist;

	return true;
}

template <class Real>
bool Plane<Real>::intersects(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray) const
{
	Real startDist = ray.start * normal + d;

	Real normalDotDir = normal * ray.direction;
	if (normalDotDir == Real(0))
		return false;

	Real dist = -startDist / normalDotDir;
	if (dist < Real(0))
		return false;

	hit = ray.pointAt(dist);
	t = dist;

	return true;
}

template <class Real>
bool Plane<Real>::intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const
{
	Real startDist = line.start * normal + d;
	Real endDist = line.end * normal + d;

	if (startDist == endDist)
		return false;

	if (startDist < Real(0) && endDist < Real(0))
		return false;

	if (startDist > Real(0) && endDist > Real(0))
		return false;

	t = startDist / (startDist - endDist);

	hit = line.pointAt(t);

	return true;
}

template <class Real>
bool Plane<Real>::intersects(Real& depth, const Sphere<Real>& sphere) const
{
	Real dist = sphere.center * normal + d;

	if (dist > sphere.radius)
		return false;

	if (dist < -sphere.radius)
		return false;

	depth = sphere.radius - dist;

	return true;
}

template <class Real>
const Real* Plane<Real>::data() const
{
	return &normal.x;
}

template <class Real>
Real* Plane<Real>::data()
{
	return &normal.x;
}

template <class Real>
template <class CastReturnType>
Plane<CastReturnType> Plane<Real>::cast() const
{
	return Plane<CastReturnType>(
		normal.template cast<CastReturnType>(),
		static_cast<CastReturnType>(d)
	);
}

template <class Real>
bool Plane<Real>::intersectAtSinglePoint(Vec3<Real>& point, const Plane& p0, const Plane& p1, const Plane& p2)
{
	const Real EPSILON = Real(1e-4);

	Real det = (p0.normal % p1.normal) * p2.normal;
	if (MATHLIB_NS::abs(det) < EPSILON)
	{
		point = Vec3<Real>::Zero;
		return false;
	}

	point = (
		((p1.normal % p2.normal) * p0.d) +
		((p2.normal % p0.normal) * p1.d) +
		((p0.normal % p1.normal) * p2.d)
	) / det;

	return true;
}

MATHLIB_NS_END
