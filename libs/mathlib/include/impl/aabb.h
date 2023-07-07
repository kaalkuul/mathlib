#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const AABB<Real> AABB<Real>::One = AABB<Real>(
	Vec3<Real>(Real(0), Real(0), Real(0)),
	Vec3<Real>(Real(1), Real(1), Real(1)));

template <class Real>
AABB<Real>::AABB()
{
}

template <class Real>
AABB<Real>::AABB(const Vec3<Real>& _center, const Vec3<Real>& size)
: center(_center), extents(size * Real(0.5))
{
}


//
//  Setters
//

template <class Real>
AABB<Real>& AABB<Real>::set(const Vec3<Real>& point)
{
	center = point;
	extents = Vec3<Real>::Zero;
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::set(const Vec3<Real>& center, const Vec3<Real>& size)
{
	this->center = center;
	this->extents = size * Real(0.5);
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::setInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup)
{
	center = (inf + sup) * Real(0.5);
	extents = (sup - inf) * Real(0.5);
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::set(int count, const Vec3<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	const Vec3<Real>* p = points;

	Vec3<Real> inf = *p;
	Vec3<Real> sup = *p;

	p++;
	count--;

	while (count-- > 0)
	{
		if (p->x < inf.x) inf.x = p->x;
		if (p->y < inf.y) inf.y = p->y;
		if (p->z < inf.z) inf.z = p->z;

		if (p->x > sup.x) sup.x = p->x;
		if (p->y > sup.y) sup.y = p->y;
		if (p->z > sup.z) sup.z = p->z;

		p++;
	}

	return setInfSup(inf, sup);
}

template <class Real>
AABB<Real>& AABB<Real>::set(int count, const Vec3<Real>* points, int stride)
{
	assert(count > 0);
	assert(points != nullptr);

	const char* p = (const char*)(points);
	const Vec3<Real>* v = (const Vec3<Real>*)(p);

	Vec3<Real> inf = *v;
	Vec3<Real> sup = *v;

	p += stride;
	count--;

	while (count-- > 0)
	{
		v = (const Vec3<Real>*)(p);

		if (v->x < inf.x) inf.x = v->x;
		if (v->y < inf.y) inf.y = v->y;
		if (v->z < inf.z) inf.z = v->z;

		if (v->x > sup.x) sup.x = v->x;
		if (v->y > sup.y) sup.y = v->y;
		if (v->z > sup.z) sup.z = v->z;

		p += stride;
	}

	return setInfSup(inf, sup);
}

template <class Real>
AABB<Real>& AABB<Real>::add(const Vec3<Real>& point)
{
	Vec3<Real> inf = center - extents;
	Vec3<Real> sup = center + extents;

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
	if (point.z < inf.z)
	{
		inf.z = point.z;
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
	if (point.z > sup.z)
	{
		sup.z = point.z;
		outside = true;
	}

	return outside ? setInfSup(inf, sup) : *this;
}


//
//  Assignments
//

template <class Real>
AABB<Real> AABB<Real>::from(const Vec3<Real>& point)
{
	AABB<Real> result;
	result.center = point;
	result.extents = Vec3<Real>::Zero;
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::from(const Vec3<Real>& center, const Vec3<Real>& size)
{
	AABB<Real> result;
	result.center = center;
	result.extents = size * Real(0.5);
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::fromInfSup(const Vec3<Real>& inf, const Vec3<Real>& sup)
{
	AABB<Real> result;
	result.center = (inf + sup) * Real(0.5);
	result.extents = (sup - inf) * Real(0.5);
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::from(int count, const Vec3<Real>* points)
{
	AABB<Real> result;
	result.set(count, points);
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::from(int count, const Vec3<Real>* points, int stride)
{
	AABB<Real> result;
	result.set(count, points, stride);
	return result;
}


//
//  Assignments
//

template <class Real>
AABB<Real>& AABB<Real>::operator+= (const Vec3<Real>& t)
{
	center += t;
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::operator-= (const Vec3<Real>& t)
{
	center -= t;
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::operator*= (Real k)
{
	extents *= k;
	return *this;
}

template <class Real>
AABB<Real>& AABB<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	extents /= k;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
AABB<Real> AABB<Real>::operator+ (const Vec3<Real>& t) const
{
	AABB<Real> result;
	result.center = center + t;
	result.extents = extents;
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::operator- (const Vec3<Real>& t) const
{
	AABB<Real> result;
	result.center = center - t;
	result.extents = extents;
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::operator* (Real k) const
{
	AABB<Real> result;
	result.center = center;
	result.extents = extents * k;
	return result;
}

template <class Real>
AABB<Real> AABB<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	AABB<Real> result;
	result.center = center;
	result.extents = extents / k;
	return result;
}


//
// Comparison operators
//

template <class Real>
bool AABB<Real>::operator==(const AABB<Real>& rhs) const
{
	return center == rhs.center && extents == rhs.extents;
}

template <class Real>
bool AABB<Real>::operator!=(const AABB<Real>& rhs) const
{
	return center != rhs.center || extents != rhs.extents;
}

//
// Functions
//

template <class Real>
Vec3<Real> AABB<Real>::inf() const
{
	return center - extents;
}

template <class Real>
Vec3<Real> AABB<Real>::sup() const
{
	return center + extents;
}

template <class Real>
Vec3<Real> AABB<Real>::size() const
{
	return extents * Real(2);
}

template <class Real>
Sphere<Real> AABB<Real>::innerSphere() const
{
	Sphere<Real> result;
	result.center = center;
	result.radius = abs(extents[extents.minorCoord()]);
	return result;
}

template <class Real>
Sphere<Real> AABB<Real>::outerSphere() const
{
	Sphere<Real> result;
	result.center = center;
	result.radius = extents.length();
	return result;
}

template <class Real>
Real AABB<Real>::volume() const
{
	return extents.x * extents.y * extents.z * Real(8);
}

template <class Real>
bool AABB<Real>::isNull() const
{
	return extents.isNull();
}

template <class Real>
Vec3<Real> AABB<Real>::pointAt(const Vec3<Real>& t) const
{
	Vec3<Real> result = center;
	result.x += extents.x * t.x;
	result.y += extents.y * t.y;
	result.z += extents.z * t.z;
	return result;
}

template <class Real>
bool AABB<Real>::contains(const Vec3<Real>& point) const
{
	return (point.x >= center.x - extents.x && point.x <= center.x + extents.x)
		&& (point.y >= center.y - extents.y && point.y <= center.y + extents.y)
		&& (point.z >= center.z - extents.z && point.z <= center.z + extents.z);
}

template <class Real>
bool AABB<Real>::contains(const Sphere<Real>& sphere) const
{
	return (sphere.center.x - sphere.radius >= center.x - extents.x && sphere.center.x + sphere.radius <= center.x + extents.x)
		&& (sphere.center.y - sphere.radius >= center.y - extents.y && sphere.center.y + sphere.radius <= center.y + extents.y)
		&& (sphere.center.z - sphere.radius >= center.z - extents.z && sphere.center.z + sphere.radius <= center.z + extents.z);
}

template <class Real>
bool AABB<Real>::contains(const AABB<Real>& box) const
{
	const Vec3<Real>& c = box.center;
	const Vec3<Real>& e = box.extents;
	return (c.x - e.x >= center.x - extents.x && c.x + e.x <= center.x + extents.x)
		&& (c.y - e.y >= center.y - extents.y && c.y + e.y <= center.y + extents.y)
		&& (c.z - e.z >= center.z - extents.z && c.z + e.z <= center.z + extents.z);
}

template <class Real>
bool AABB<Real>::intersects(const AABB<Real>& box) const
{
	const Vec3<Real>& m1 = inf();
	const Vec3<Real>& M1 = sup();
	const Vec3<Real>& m2 = box.inf();
	const Vec3<Real>& M2 = box.sup();
	if (m2.x > M1.x || M2.x < m1.x) return false;
	if (m2.y > M1.y || M2.y < m1.y) return false;
	if (m2.z > M1.z || M2.z < m1.z) return false;
	return true;
}

/*

#define IR(x)	(*(unsigned int*)&x)

// http://www.codercorner.com/RayAABB.cpp

bool AABB<Real>::intersects(Vec3<Real>& hit, const Line3<Real>& line) const
{
	bool inside = true;
	Vec3<Real> MaxT;
	MaxT.x = MaxT.y = MaxT.z = -Real(1);
	int i;
	// Find candidate planes.
	for (i = 0; i < 3; i++)
	{
		Coord coord = (Coord)i;
		Real fDir = dir(coord);
		if (from(coord) < inf(coord))
		{
			hit[coord]	= inf(coord);
			inside		= false;
			
			// Calculate T distances to candidate planes
			if (IR(fDir))	
				MaxT[coord] = (inf(coord) - from(coord)) / dir(coord);
		}
		else if (from(coord) > sup(coord))
		{
			hit[coord]	= sup(coord);
			inside		= false;
			
			// Calculate T distances to candidate planes
			if (IR(fDir))
				MaxT[coord] = (sup(coord) - from(coord)) / dir(coord);
		}
	}
	
	// Ray origin inside bounding box
	if (inside)
	{
		hit = from;
		return true;
	}
	
	// Get largest of the maxT's for final choice of intersection
	Coord WhichPlane = FdVX;
	if (MaxT[FdVY] > MaxT[WhichPlane])	
		WhichPlane = FdVY;
	if (MaxT[FdVZ] > MaxT[WhichPlane])	
		WhichPlane = FdVZ;
	
	// Check final candidate actually inside box
	if (IR(MaxT[WhichPlane]) & 0x80000000) 
		return false;
	
	for (i = 0; i < 3; i++)
	{
		Coord coord = (Coord)i;
		if (i != WhichPlane)
		{
			hit[coord] = from(coord) + MaxT(WhichPlane) * dir(coord);
			if (hit(coord) < inf(coord) || hit(coord) > sup(coord))	
				return false;
		}
	}

	return true;	// ray hits box
}

*/
template <class Real>
template <class CastReturnType>
AABB<CastReturnType> AABB<Real>::cast() const
{
	AABB<CastReturnType> result;
	result.center = center.template cast<CastReturnType>();
	result.extents = extents.template cast<CastReturnType>();
	return result;
}

MATHLIB_NS_END
