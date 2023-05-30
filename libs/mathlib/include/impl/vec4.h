#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Vec4<Real> Vec4<Real>::Zero = Vec4<Real>(Real(0));

template <class Real>
const Vec4<Real> Vec4<Real>::OneX = Vec4<Real>(Real(1), Real(0), Real(0), Real(1));

template <class Real>
const Vec4<Real> Vec4<Real>::OneY = Vec4<Real>(Real(0), Real(1), Real(0), Real(1));

template <class Real>
const Vec4<Real> Vec4<Real>::OneZ = Vec4<Real>(Real(0), Real(0), Real(1), Real(1));

template <class Real>
const Vec4<Real> Vec4<Real>::OneW = Vec4<Real>(Real(0), Real(0), Real(0), Real(1));

//
// Constructors
//

template <class Real>
Vec4<Real>::Vec4()
{
}

template <class Real>
Vec4<Real>::Vec4(Real k)
	: x(k), y(k), z(k), w(k)
{
}

template <class Real>
Vec4<Real>::Vec4(Real px, Real py, Real pz, Real pw)
	: x(px), y(py), z(pz), w(pw)
{
}

template <class Real>
Vec4<Real>::Vec4(const Vec3<Real> &u, Real pw)
	: x(u.x), y(u.y), z(u.z), w(pw)
{
}

//
// Setters
// 

template <class Real>
Vec4<Real>& Vec4<Real>::set(Real x, Real y, Real z, Real w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::set(const Vec3<Real>& v, Real w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::set(const Vec4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
	return *this;
}


//
//  Assignments
//

template <class Real>
Vec4<Real>& Vec4<Real>::operator+= (const Vec3<Real>& u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::operator-= (const Vec3<Real>& u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::operator+= (const Vec4& u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	w += u.w;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::operator-= (const Vec4& u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	w -= u.w;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::operator*= (Real k)
{
	x *= k;
	y *= k;
	z *= k;
	w *= k;
	return *this;
}

template <class Real>
Vec4<Real>& Vec4<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	x /= k;
	y /= k;
	z /= k;
	w /= k;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
Vec4<Real> Vec4<Real>::operator+ (const Vec4 &u) const
{
	return Vec4(x + u.x, y + u.y, z + u.z, w + u.w);
}

template <class Real>
Vec4<Real> Vec4<Real>::operator- () const
{
	return Vec4(-x, -y, -z, -w);
}

template <class Real>
Vec4<Real> Vec4<Real>::operator- (const Vec4 &u) const
{
	return Vec4(x - u.x, y - u.y, z - u.z, w - u.w);
}

template <class Real>
Real Vec4<Real>::operator* (const Vec4 &u) const
{
	return x * u.x + y * u.y + z * u.z + w * u.w;
}

template <class Real>
Vec4<Real> Vec4<Real>::operator* (Real k) const
{
	return Vec4(x * k, y * k, z * k, w * k);
}

template <class Real>
Vec4<Real> Vec4<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return Vec4(x / k, y / k, z / k, w / k);
}


//
// Comparison operators
//

template <class Real>
bool Vec4<Real>::operator== (const Vec4& u) const
{
	return x == u.x && y == u.y && z == u.z && w == u.w;
}

template <class Real>
bool Vec4<Real>::operator!= (const Vec4& u) const
{
	return x != u.x || y != u.y || z != u.z || w != u.w;
}


//
//  Functions
//

template <class Real>
Real Vec4<Real>::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

template <class Real>
Real Vec4<Real>::lengthSqr() const
{
	return x * x + y * y + z * z + w * w;
}

template <class Real>
Vec3<Real> Vec4<Real>::toVec3() const
{
	return Vec3<Real>(x, y, z);
}

template <class Real>
bool Vec4<Real>::isNull() const
{
	return x == Real(0) && y == Real(0) && z == Real(0) && w == Real(0);
}

template <class Real>
const Real* Vec4<Real>::data() const
{
	return &x;
}

template <class Real>
Real* Vec4<Real>::data()
{
	return &x;
}

template <class Real>
template <class CastReturnType>
Vec4<CastReturnType> Vec4<Real>::cast() const
{
	return Vec4<CastReturnType>(
		static_cast<CastReturnType>(x),
		static_cast<CastReturnType>(y), 
		static_cast<CastReturnType>(z), 
		static_cast<CastReturnType>(w)
	);
}

MATHLIB_NS_END
