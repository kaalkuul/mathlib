#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Sphere
{
public:
	typedef Real Real;

public:
	// Constructors
	Sphere();
	Sphere(const Vec3<Real>& center, Real radius);

	// Setters
	Sphere& set(const Vec3<Real>& center, Real radius);
	Sphere& set(int count, const Vec3<Real>* points);
	Sphere& set(int count, const Vec3<Real>* points, int stride);

	// Create from
	static Sphere from(const Vec3<Real>& center, Real radius);
	static Sphere from(int count, const Vec3<Real>* points);
	static Sphere from(int count, const Vec3<Real>* points, int stride);

	// Assignments
	Sphere& operator+=(const Vec3<Real>& t);
	Sphere& operator-=(const Vec3<Real>& t);
	Sphere& operator*=(Real k);
	Sphere& operator/=(Real k);

	// Arithmetic operators
	Sphere operator+ (const Vec3<Real>& t) const;
	Sphere operator- (const Vec3<Real>& t) const;
	Sphere operator* (Real k) const;
	Sphere operator/ (Real k) const;

	// Comparison operators
	bool operator== (const Sphere& rhs) const;
	bool operator!= (const Sphere& rhs) const;

	// Functions
	bool contains(const Vec3<Real>& point) const;
	bool contains(const Sphere<Real>& sphere) const;

	bool hits(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;

	bool intersects(const Sphere<Real>& sphere) const;
	bool intersects(const Line3<Real>& line) const;

	bool intersects(Vec3<Real>& hit, Real& t, const Sphere<Real>& sphere) const;
	bool intersects(Vec3<Real>& hit, Real& t, const Line3<Real>& line) const;

	const Real* data() const;
	Real* data();

	template <class CastReturnType>
	Sphere<CastReturnType> cast() const;

	static const Sphere One;

public:
	Vec3<Real> center;
	Real radius;
};

MATHLIB_NS_END
