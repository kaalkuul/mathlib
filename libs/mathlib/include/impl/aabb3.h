#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const AABB3<Real> AABB3<Real>::Zero = AABB3<Real>(
    Vec3<Real>(Real(0), Real(0), Real(0)),
    Vec3<Real>(Real(0), Real(0), Real(0)));

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

template <class Real>
AABB3<Real> AABB3<Real>::fromIntersection(const AABB3<Real>& a, const AABB3<Real>& b)
{
    if (a.inf.x > b.sup.x || a.sup.x < b.inf.x) return Zero;
    if (a.inf.y > b.sup.y || a.sup.y < b.inf.y) return Zero;
    if (a.inf.z > b.sup.z || a.sup.z < b.inf.z) return Zero;
    return from(Vec3<Real>::max(a.inf, b.inf), Vec3<Real>::min(a.sup, b.sup));
}

template <class Real>
AABB3<Real> AABB3<Real>::fromUnion(const AABB3<Real>& a, const AABB3<Real>& b)
{
    return from(Vec3<Real>::min(a.inf, b.inf), Vec3<Real>::max(a.sup, b.sup));
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
bool AABB3<Real>::hits(Real& t, const Ray3<Real>& ray) const
{
    t = Real(0);

    if (ray.direction.x == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.x < inf.x || ray.start.x > sup.x)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.x;
        Real tinf = (inf.x - ray.start.x) * invD;
        Real tsup = (sup.x - ray.start.x) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    if (ray.direction.y == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.y < inf.y || ray.start.y > sup.y)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.y;
        Real tinf = (inf.y - ray.start.y) * invD;
        Real tsup = (sup.y - ray.start.y) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    if (ray.direction.z == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.z < inf.z || ray.start.z > sup.z)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.z;
        Real tinf = (inf.z - ray.start.z) * invD;
        Real tsup = (sup.z - ray.start.z) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    return true;
}

template <class Real>
bool AABB3<Real>::hits(Real& t, const Line3<Real>& line) const
{
    t = Real(0);

    Vec3<Real> delta = line.end - line.start;

    if (delta.x == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.x < inf.x || line.start.x > sup.x)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.x;
        Real tinf = (inf.x - line.start.x) * invD;
        Real tsup = (sup.x - line.start.x) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    if (delta.y == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.y < inf.y || line.start.y > sup.y)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.y;
        Real tinf = (inf.y - line.start.y) * invD;
        Real tsup = (sup.y - line.start.y) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    if (delta.z == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.z < inf.z || line.start.z > sup.z)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.z;
        Real tinf = (inf.z - line.start.z) * invD;
        Real tsup = (sup.z - line.start.z) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        if (tinf < Real(0))
            return false;

        t = std::max(t, tinf);
    }

    if (t > Real(1))
        return false;
    
    return true;
}

template <class Real>
bool AABB3<Real>::intersects(const AABB3<Real>& box) const
{
	if (box.inf.x > sup.x || box.sup.x < inf.x) return false;
	if (box.inf.y > sup.y || box.sup.y < inf.y) return false;
	if (box.inf.z > sup.z || box.sup.z < inf.z) return false;
	return true;
}

template <class Real>
bool AABB3<Real>::intersects(Real& t1, Real& t2, const Ray3<Real>& ray) const
{
    t1 = Real(0);
    t2 = std::numeric_limits<Real>::max();

    if (ray.direction.x == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.x < inf.x || ray.start.x > sup.x)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.x;
        Real tinf = (inf.x - ray.start.x) * invD;
        Real tsup = (sup.x - ray.start.x) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    if (ray.direction.y == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.y < inf.y || ray.start.y > sup.y)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.y;
        Real tinf = (inf.y - ray.start.y) * invD;
        Real tsup = (sup.y - ray.start.y) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    if (ray.direction.z == Real(0))
    {
        // Ray is parallel to the slab. Check if the start point is outside the slab.
        if (ray.start.z < inf.z || ray.start.z > sup.z)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / ray.direction.z;
        Real tinf = (inf.z - ray.start.z) * invD;
        Real tsup = (sup.z - ray.start.z) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    return true;
}

template <class Real>
bool AABB3<Real>::intersects(Real& t1, Real& t2, const Line3<Real>& line) const
{
    t1 = Real(0);
    t2 = std::numeric_limits<Real>::max();

    Vec3<Real> delta = line.end - line.start;

    if (delta.x == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.x < inf.x || line.start.x > sup.x)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.x;
        Real tinf = (inf.x - line.start.x) * invD;
        Real tsup = (sup.x - line.start.x) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    if (delta.y == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.y < inf.y || line.start.y > sup.y)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.y;
        Real tinf = (inf.y - line.start.y) * invD;
        Real tsup = (sup.y - line.start.y) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    if (delta.z == Real(0))
    {
        // Line is parallel to the slab. Check if the start point is outside the slab.
        if (line.start.z < inf.z || line.start.z > sup.z)
            return false;  // No intersection if outside the slab
    }
    else
    {
        // Compute intersection tinf and tsup with the near and far slabs
        Real invD = Real(1) / delta.z;
        Real tinf = (inf.z - line.start.z) * invD;
        Real tsup = (sup.z - line.start.z) * invD;
        
        if (tinf > tsup) std::swap(tinf, tsup);

        // Narrow down the intersection interval [t1, t2]
        t1 = std::max(t1, tinf);
        t2 = std::min(t2, tsup);

        if (t2 < t1)
            return false;
    }

    if (t1 < Real(0) && t2 < Real(0))
        return false;
    if (t1 > Real(1) && t2 > Real(1))
        return false;

    if (t1 < Real(0))
        t1 = Real(0);
    if (t2 > Real(1))
        t2 = Real(1);
    
    return true;
}

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
