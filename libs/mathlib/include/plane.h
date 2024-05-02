#pragma once

MATHLIB_NS_BEGIN

template <class RealT>
class Plane
{
public:
	typedef RealT Real;

public:
	// Constructors
	Plane();
	Plane(const Vec3<Real>& normal, Real distance);

	// Create from
	static Plane from(const Vec3<Real>& point, const Vec3<Real>& normal);
	static Plane fromPointAndTangents(const Vec3<Real>& point, const Vec3<Real>& u, const Vec3<Real>& v);
	static Plane from(const Vec3<Real>& a,
		const Vec3<Real>& b, const Vec3<Real>& c);
	static Plane from(const Plane& plane, Real distance);

	// Comparison operators
	bool operator== (const Plane& rhs) const;
	bool operator!= (const Plane& rhs) const;

    // Transformations
    Plane& move(Real distance);
    Plane& flip();

    // Functions
    Plane moved(Real distance) const;
    
    Plane flipped() const;
    
    bool contains(const Vec3<Real>& point, Real tolerance) const;

	Real distance(const Vec3<Real>& point) const;

	Real project(Vec3<Real>& projection, const Vec3<Real>& p) const;
	bool project(Vec3<Real>& projection, const Vec3<Real>& p, const Vec3<Real>& dir) const;

	bool hits(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray) const;
	bool hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;
	bool hits(Vec3<Real>& hit, Real &t, const Line3<Real>& line, Real radius) const;
	bool hits(Real& depth, const Sphere<Real>& pos) const;

	bool intersects(Vec3<Real>& hit, Real& t, const Ray3<Real>& ray) const;
	bool intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;
	bool intersects(Real& depth, const Sphere<Real>& pos) const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Plane<CastReturnType> cast() const;

	static bool intersectAtSinglePoint(Vec3<Real>& intersectionPoint, const Plane& p0, const Plane& p1, const Plane& p2);

	static const Plane XY;
	static const Plane YZ;
	static const Plane ZX;

public:
	Vec3<Real> normal;
	Real d;
};

MATHLIB_NS_END
