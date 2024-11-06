#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const AABB3<Real> AABB3<Real>::One = AABB3<Real>(
	Vec3<Real>(Real(-0.5), Real(-0.5), Real(-0.5)),
	Vec3<Real>(Real(0.5), Real(0.5), Real(0.5)));

template <class Real>
AABB3<Real>::AABB3()
{
}

template <class Real>
AABB3<Real>::AABB3(const Vec3<Real>& _inf, const Vec3<Real>& _sup)
: inf(_inf), sup(_sup)
{
}


//
//  Setters
//

template <class Real>
AABB3<Real>& AABB3<Real>::set(const Vec3<Real>& point)
{
	inf = sup = point;
	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::set(const Vec3<Real>& inf, const Vec3<Real>& sup)
{
	this->inf = inf;
    this->sup = sup;
	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::set(const CAABB3<Real>& box)
{
	inf = box.center - box.extents;
    sup = box.center + box.extents;
	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::set(int count, const Vec3<Real>* points)
{
	assert(count > 0);
	assert(points != nullptr);

	const Vec3<Real>* p = points;

	inf = *p;
	sup = *p;

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

	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::set(int count, const Vec3<Real>* points, int stride)
{
	assert(count > 0);
	assert(points != nullptr);

	const char* p = (const char*)(points);
	const Vec3<Real>* v = (const Vec3<Real>*)(p);

	inf = *v;
	sup = *v;

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

	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::add(const Vec3<Real>& point)
{
	if (point.x < inf.x)
	{
		inf.x = point.x;
	}
	if (point.y < inf.y)
	{
		inf.y = point.y;
	}
	if (point.z < inf.z)
	{
		inf.z = point.z;
	}

	if (point.x > sup.x)
	{
		sup.x = point.x;
	}
	if (point.y > sup.y)
	{
		sup.y = point.y;
	}
	if (point.z > sup.z)
	{
		sup.z = point.z;
	}

	return *this;
}


//
//  Assignments
//

template <class Real>
AABB3<Real> AABB3<Real>::from(const Vec3<Real>& point)
{
	AABB3<Real> result;
	result.inf = result.sup = point;
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::from(const Vec3<Real>& inf, const Vec3<Real>& sup)
{
	AABB3<Real> result;
	result.inf = inf;
	result.sup = sup;
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::from(const CAABB3<Real>& box)
{
	AABB3<Real> result;
	result.inf = box.center - box.extents;
    result.sup = box.center + box.extents;
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::from(int count, const Vec3<Real>* points)
{
	AABB3<Real> result;
	result.set(count, points);
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::from(int count, const Vec3<Real>* points, int stride)
{
	AABB3<Real> result;
	result.set(count, points, stride);
	return result;
}


//
//  Assignments
//

template <class Real>
AABB3<Real>& AABB3<Real>::operator+= (const Vec3<Real>& t)
{
	inf += t;
    sup += t;
	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::operator-= (const Vec3<Real>& t)
{
    inf -= t;
    sup -= t;
	return *this;
}

template <class Real>
AABB3<Real>& AABB3<Real>::operator*= (Real k)
{
    return scaleCentered(k);
}

template <class Real>
AABB3<Real>& AABB3<Real>::operator/= (Real k)
{
	assert(k != Real(0));
    return scaleCentered(Real(1) / k);
}


//
// Arithmetic operators
//

template <class Real>
AABB3<Real> AABB3<Real>::operator+ (const Vec3<Real>& t) const
{
	AABB3<Real> result;
	result.inf = inf + t;
    result.sup = sup + t;
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::operator- (const Vec3<Real>& t) const
{
	AABB3<Real> result;
    result.inf = inf - t;
    result.sup = sup - t;
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::operator* (Real k) const
{
    AABB3<Real> result(inf, sup);
	result.scaleCentered(k);
	return result;
}

template <class Real>
AABB3<Real> AABB3<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
    AABB3<Real> result(inf, sup);
    result.scaleCentered(Real(1) / k);
	return result;
}


//
// Comparison operators
//

template <class Real>
bool AABB3<Real>::operator==(const AABB3<Real>& rhs) const
{
	return inf == rhs.inf && sup == rhs.sup;
}

template <class Real>
bool AABB3<Real>::operator!=(const AABB3<Real>& rhs) const
{
	return inf != rhs.inf || sup != rhs.sup;
}


//
// Transformations
//

template <class Real>
AABB3<Real>& AABB3<Real>::scaleCentered(Real k)
{
    CAABB3<Real> box;
    box.center = (inf + sup) * Real(0.5);
    box.extents = (sup - inf) * Real(0.5) * k;
    return set(box);
}


//
// Functions
//

template <class Real>
Vec3<Real> AABB3<Real>::center() const
{
	return (inf + sup) * Real(0.5);
}

template <class Real>
Vec3<Real> AABB3<Real>::extents() const
{
    return (sup - inf) * Real(0.5);
}

template <class Real>
Vec3<Real> AABB3<Real>::size() const
{
	return sup - inf;
}

template <class Real>
Sphere<Real> AABB3<Real>::innerSphere() const
{
    Vec3<Real> extents = (sup - inf) * Real(0.5);
	Sphere<Real> result;
    result.center = (inf + sup) * Real(0.5);
	result.radius = abs(extents[extents.minorCoord()]);
	return result;
}

template <class Real>
Sphere<Real> AABB3<Real>::outerSphere() const
{
    Vec3<Real> extents = (sup - inf) * Real(0.5);
    Sphere<Real> result;
    result.center = (inf + sup) * Real(0.5);
	result.radius = extents.length();
	return result;
}

template <class Real>
Real AABB3<Real>::volume() const
{
	return (sup.x - inf.x) * (sup.y - inf.y) * (sup.z - inf.z);
}

template <class Real>
bool AABB3<Real>::isNull() const
{
	return sup == inf;
}

template <class Real>
Vec3<Real> AABB3<Real>::pointAt(const Vec3<Real>& t) const
{
	Vec3<Real> result;
	result.x = inf.x + (sup.x - inf.x) * t.x;
	result.y = inf.y + (sup.y - inf.y) * t.y;
	result.z = inf.z + (sup.z - inf.z) * t.z;
	return result;
}

template <class Real>
bool AABB3<Real>::contains(const Vec3<Real>& point) const
{
	return (point.x >= inf.x && point.x <= sup.x)
		&& (point.y >= inf.y && point.y <= sup.y)
		&& (point.z >= inf.z && point.z <= sup.z);
}

template <class Real>
bool AABB3<Real>::contains(const Sphere<Real>& sphere) const
{
	return (sphere.center.x - sphere.radius >= inf.x && sphere.center.x + sphere.radius <= sup.x)
		&& (sphere.center.y - sphere.radius >= inf.y && sphere.center.y + sphere.radius <= sup.y)
		&& (sphere.center.z - sphere.radius >= inf.z && sphere.center.z + sphere.radius <= sup.z);
}

template <class Real>
bool AABB3<Real>::contains(const AABB3<Real>& box) const
{
	return (box.inf.x >= inf.x && box.sup.x <= sup.x)
		&& (box.inf.y >= inf.y && box.sup.y <= sup.y)
		&& (box.inf.z >= inf.z && box.sup.z <= sup.z);
}

template <class Real>
bool AABB3<Real>::intersects(const AABB3<Real>& box) const
{
	if (box.inf.x > sup.x || box.sup.x < inf.x) return false;
	if (box.inf.y > sup.y || box.sup.y < inf.y) return false;
	if (box.inf.z > sup.z || box.sup.z < inf.z) return false;
	return true;
}

/*

#define IR(x)	(*(unsigned int*)&x)

// http://www.codercorner.com/RayAABB3.cpp

bool AABB3<Real>::intersects(Vec3<Real>& hit, const Line3<Real>& line) const
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
AABB3<CastReturnType> AABB3<Real>::cast() const
{
	AABB3<CastReturnType> result;
	result.inf = inf.template cast<CastReturnType>();
	result.sup = sup.template cast<CastReturnType>();
	return result;
}

MATHLIB_NS_END
