#pragma once

MATHLIB_NS_BEGIN

template <class Real>
class Quat  
{
public:
	//Constructors
	Quat();
	Quat(Real px, Real py, Real pz, Real pw, bool autoNormalize = true);

	// Setters
	Quat& setIdentity();
	Quat& set(const Quat &q);
	Quat& set(const Mat3<Real> &m);
	Quat& set(const Vec3<Real> &axis, Real angle);
	Quat& set(const Vec3<Real> &from, const Vec3<Real> &to);
	Quat& lerp(const Quat &from, const Quat &to, Real weight);
	Quat& slerp(const Quat &from, const Quat &to, Real weight);
	Quat& slerpMaxAngle(const Quat &from, const Quat &to, Real maxAngle);
	Quat& slerpNoInvert(const Quat &from, const Quat &to, Real weight);
	Quat& set(const Quat &from, const Quat &to, const Quat &a, const Quat &b, Real weight);
	Quat& set(const Quat &from, const Quat &via, const Quat &to);

	// Transformations
	Quat& normalize();

	// Create from
	static Quat from(const Quat& q);
	static Quat from(const Mat3<Real>& m);
	static Quat from(const Vec3<Real>& axis, Real angle);
	static Quat from(const Vec3<Real>& from, const Vec3<Real>& to);
	static Quat fromLerp(const Quat& from, const Quat& to, Real weight);
	static Quat fromSlerp(const Quat& from, const Quat& to, Real weight);
	static Quat fromSlerpMaxAngle(const Quat& from, const Quat& to, Real maxAngle);
	static Quat fromSlerpNoInvert(const Quat& from, const Quat& to, Real weight);
	static Quat from(const Quat& from, const Quat& to, const Quat& a, const Quat& b, Real weight);
	static Quat from(const Quat& from, const Quat& via, const Quat& to);

	// Assignments
	Quat &operator = (const Quat &q);

	// Arithmetic operators
	Quat operator * (const Quat &q) const;
	Vec3<Real> operator * (const Vec3<Real> &v) const;
	Quat operator - () const;
	Quat operator / (const Quat &q) const;

	// Comparison operators
	bool operator == (const Quat& q) const;
	bool operator != (const Quat& q) const;

	// Functions
	Vec3<Real> rotated(Coord c) const;
	Vec3<Real> rotated(const Vec3<Real> &v) const;
	Quat inverse() const;
	void toAxisAngle(Vec3<Real> &v, Real &a) const;

	static Quat log(const Quat &q);
	static Quat exp(const Quat &q);

public:
	Real x;
	Real y;
	Real z;
	Real w;

    static const Quat One;
};

MATHLIB_NS_END
