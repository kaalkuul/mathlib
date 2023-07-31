#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Frustum
{
public:
	typedef Real Real;

public:
	// Constructors
	Frustum();
	Frustum(const Vec3<Real>* corners);

	// Setters
	void set(const Vec3<Real>* corners);
	void set(const Mat34<Real>& ltw, const Vec3<Real>* corners);
	void set(const Mat4<Real>& ltw, const Vec3<Real>* corners);

	// Functions
	bool contains(const Vec3<Real>& point) const;
	bool contains(const Vec4<Real>& point) const;
	bool contains(const Sphere<Real>& sphere) const;

	bool intersects(const Sphere<Real>& sphere) const;

	template <class CastReturnType>
	Frustum<CastReturnType> cast() const;

private:
	void computePlanes();

public:
	Vec3<Real> corners[8];
	Plane<Real> planes[6];
};

MATHLIB_NS_END
