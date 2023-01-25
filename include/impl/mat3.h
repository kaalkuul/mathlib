#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Mat3<Real> Mat3<Real>::Zero = Mat3<Real>(Real(0));

template <class Real>
const Mat3<Real> Mat3<Real>::One = Mat3<Real>(Real(1));

template <class Real>
const typename Mat3<Real>::Tolerance Mat3<Real>::DefaultTolerance = { Real(0.001), Real(0.001), Real(0.001) };

//
//  Constructors
//

template <class Real>
Mat3<Real>::Mat3()
:	flags(Flags::Uninitialized)
{
}

template <class Real>
Mat3<Real>::Mat3(Real k)
{
	x.x = k;		y.x = Real(0);	z.x = Real(0);
	x.y = Real(0);	y.y = k;		z.y = Real(0);
	x.z = Real(0);	y.z = Real(0);	z.z = k;
	flags = Flags::Orthogonal;
	if (k == Real(1))
	{
		flags |= Flags::Normal | Flags::Identity;
	}
}

template <class Real>
Mat3<Real>::Mat3(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z)
{
	set(x, y, z);
}


//
// Setters
//

template <class Real>
Mat3<Real>& Mat3<Real>::setIdentity()
{
	x = Vec3<Real>::OneX;
	y = Vec3<Real>::OneY;
	z = Vec3<Real>::OneZ;
	flags = Flags::Mask | Flags::Identity;
	return *this;
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(const Mat3<Real>& m)
{
	x = m.x;
	y = m.y;
	z = m.z;
	flags = m.flags;
	return *this;
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(const Quat<Real>& q)
{
	Real xx = q.x * q.x;
	Real yy = q.y * q.y;
	Real zz = q.z * q.z;
	Real yz = q.y * q.z;
	Real zx = q.z * q.x;
	Real xy = q.x * q.y;
	Real wx = q.w * q.x;
	Real wy = q.w * q.y;
	Real wz = q.w * q.z;

	x.x = Real(1) - Real(2) * (yy + zz);
	x.y = Real(2) * (xy + wz);
	x.z = Real(2) * (zx - wy);
	y.x = Real(2) * (xy - wz);
	y.y = Real(1) - Real(2) * (xx + zz);
	y.z = Real(2) * (yz + wx);
	z.x = Real(2) * (zx + wy);
	z.y = Real(2) * (yz - wx);
	z.z = Real(1) - Real(2) * (xx + yy);

	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
{
	if (exact.x == 0 && exact.y == 0 && exact.z == 0)
		return setIdentity();

	Vec3<Real> u = exact.normalized();
	Vec3<Real> v = approx % u;

	if (v.x == 0 && v.y == 0 && v.z == 0)
		return setIdentity();

	v.normalize();

	Vec3<Real> w = u % v;

	switch (ecoord)
	{
	case Coord::X:
		switch (acoord)
		{
		case Coord::Y: return set(u, w, -v);
		case Coord::Z: return set(u, v, w);
		default: assert(0); return setIdentity();
		}
	case Coord::Y:
		switch (acoord)
		{
		case Coord::X: return set(w, u, v);
		case Coord::Z: return set(-v, u, w);
		default: assert(0); return setIdentity();
		}
	case Coord::Z:
		switch (acoord)
		{
		case Coord::X: return set(w, -v, u);
		case Coord::Y: return set(v, w, u);
		default: assert(0); return setIdentity();
		}
	default:
		assert(0);
		return setIdentity();
	}
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(const Vec3<Real>& axis, Real angle)
{
	Vec3<Real> v = axis.normalized();

	Real s = sin(angle);
	Real c = cos(angle);
	Real t = Real(1) - c;

	x.x = c + v.x * v.x * t;
	x.y = v.x * v.y * t + v.z * s;
	x.z = v.z * v.x * t - v.y * s;

	y.x = v.x * v.y * t - v.z * s;
	y.y = c + v.y * v.y * t;
	y.z = v.y * v.z * t + v.x * s;

	z.x = v.z * v.x * t + v.y * s;
	z.y = v.y * v.z * t - v.x * s;
	z.z = c + v.z * v.z * t;

	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::set(Coord axis, Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	switch (axis)
	{
	case Coord::X:
		x.x = Real(1);
		x.y = Real(0);
		x.z = Real(0);

		y.x = Real(0);
		y.y = c;
		y.z = s;

		z.x = Real(0);
		z.y = -s;
		z.z = c;
		break;
	case Coord::Y:
		x.x = c;
		x.y = Real(0);
		x.z = -s;

		y.x = Real(0);
		y.y = Real(1);
		y.z = Real(0);

		z.x = s;
		z.y = Real(0);
		z.z = c;
		break;
	case Coord::Z:
		x.x = c;
		x.y = s;
		x.z = Real(0);

		y.x = -s;
		y.y = c;
		y.z = Real(0);

		z.x = Real(0);
		z.y = Real(0);
		z.z = Real(1);
		break;
	default:
		assert(0);
	}
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::slerp(const Mat3& a, const Mat3& b, Real weight)
{
	Quat<Real> qa, qb, qr;
	qa.set(a);
	qb.set(b);
	qr.slerp(qa, qb, weight);
	return set(qr);
}

template <class Real>
Mat3<Real>& Mat3<Real>::slerpMaxAngle(const Mat3& a, const Mat3& b, Real maxAngle)
{
	Quat<Real> qa, qb, qr;
	qa.set(a);
	qb.set(b);
	qr.slerpMaxAngle(qa, qb, maxAngle);
	return set(qr);
}


//
// Create from
//

template <class Real>
Mat3<Real> Mat3<Real>::from(const Quat<Real>& q)
{
	Mat3<Real> r;
	r.set(q);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z)
{
	Mat3<Real> r;
	r.set(x, y, z);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
{
	Mat3<Real> r;
	r.set(ecoord, exact, acoord, approx);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::from(const Vec3<Real>& axis, Real angle)
{
	Mat3<Real> r;
	r.set(axis, angle);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::from(Coord axis, Real angle)
{
	Mat3<Real> r;
	r.set(axis, angle);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::fromSlerp(const Mat3& a, const Mat3& b, Real weight)
{
	Mat3<Real> r;
	r.slerp(a, b, weight);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::fromSlerpMaxAngle(const Mat3& a, const Mat3& b, Real maxAngle)
{
	Mat3<Real> r;
	r.slerpMaxAngle(a, b, maxAngle);
	return r;
}


//
//  Assignments
//

template <class Real>
Mat3<Real>& Mat3<Real>::operator*=(Real k)
{
	if (k == Real(1))
		return *this;
	x *= k;
	y *= k;
	z *= k;
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::operator*=(const Mat3 &m)
{
	if (m.isIdentity())
		return *this;
	if (isIdentity())
		return set(m);
	Real ta = x.x, tb = y.x, td = x.y, te = y.y, tg = x.z, th = y.z;
	x.x = ta * m.x.x + tb * m.x.y + z.x * m.x.z;
	y.x = ta * m.y.x + tb * m.y.y + z.x * m.y.z;
	z.x = ta * m.z.x + tb * m.z.y + z.x * m.z.z;
	x.y = td * m.x.x + te * m.x.y + z.y * m.x.z;
	y.y = td * m.y.x + te * m.y.y + z.y * m.y.z;
	z.y = td * m.z.x + te * m.z.y + z.y * m.z.z;
	x.z = tg * m.x.x + th * m.x.y + z.z * m.x.z;
	y.z = tg * m.y.x + th * m.y.y + z.z * m.y.z;
	z.z = tg * m.z.x + th * m.z.y + z.z * m.z.z;
	flags &= m.flags;
	return *this;
}

template <class Real>
Mat3<Real> &Mat3<Real>::operator/=(Real k)
{
	assert(k != Real(0));
	if (k == Real(1))
		return *this;
	x /= k;
	y /= k;
	z /= k;
	return optimize();
}


//
//  Arithmetic operators
//

template <class Real>
Mat3<Real> Mat3<Real>::operator-() const
{
	return Mat3(-x, -y, -z);
}

template <class Real>
Mat3<Real> Mat3<Real>::operator*(const Mat3 &m) const
{
	Mat3 r;
	multiply(r, *this, m);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::operator*(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	return Mat3(x * k, y * k, z * k);
}

template <class Real>
Vec3<Real> Mat3<Real>::operator*(const Vec3<Real> &u) const
{
	Vec3<Real> r;
	transform(r, u);
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::operator/(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	return Mat3(x / k, y / k, z / k);
}


//
// Comparison operators
//

template <class Real>
bool Mat3<Real>::operator==(const Mat3 &m) const
{
	return x == m.x && y == m.y && z == m.z;
}

template <class Real>
bool Mat3<Real>::operator!=(const Mat3 &m) const
{
	return x != m.x || y != m.y || z != m.z;
}

// Transformations

template <class Real>
Mat3<Real>& Mat3<Real>::scale(const Vec3<Real>& coefficients)
{
	x *= coefficients.x;
	y *= coefficients.y;
	z *= coefficients.z;
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotate(const Mat3& m)
{
	if (m.isIdentity())
		return *this;

	if (isIdentity())
		return set(m);

	Real x_x = x.x, y_x = y.x, z_x = z.x, x_y = x.y, y_y = y.y, z_y = z.y;

	x.x = m.x.x * x_x + m.y.x * x_y + m.z.x * x.z;
	y.x = m.x.x * y_x + m.y.x * y_y + m.z.x * y.z;
	z.x = m.x.x * z_x + m.y.x * z_y + m.z.x * z.z;
	x.y = m.x.y * x_x + m.y.y * x_y + m.z.y * x.z;
	y.y = m.x.y * y_x + m.y.y * y_y + m.z.y * y.z;
	z.y = m.x.y * z_x + m.y.y * z_y + m.z.y * z.z;
	x.z = m.x.z * x_x + m.y.z * x_y + m.z.z * x.z;
	y.z = m.x.z * y_x + m.y.z * y_y + m.z.z * y.z;
	z.z = m.x.z * z_x + m.y.z * z_y + m.z.z * z.z;

	flags &= m.flags;

	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotate(const Quat<Real>& q)
{
	Mat3 m;
	m.set(q);
	return rotate(m);
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotate(const Vec3<Real>& axis, Real angle)
{
	Mat3 m;
	m.set(axis, angle);
	return rotate(m);
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotate(Coord axis, Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	Real t;
	switch (axis)
	{
	case Coord::X:
		t = x.y;
		x.y = t * c - x.z * s;
		x.z = t * s + x.z * c;

		t = y.y;
		y.y = t * c - y.z * s;
		y.z = t * s + y.z * c;

		t = z.y;
		z.y = t * c - z.z * s;
		z.z = t * s + z.z * c;
		break;
	case Coord::Y:
		t = x.x;
		x.x = t * c + x.z * s;
		x.z = -t * s + x.z * c;

		t = y.x;
		y.x = t * c + y.z * s;
		y.z = -t * s + y.z * c;

		t = z.x;
		z.x = t * c + z.z * s;
		z.z = -t * s + z.z * c;
		break;
	case Coord::Z:
		t = x.x;
		x.x = t * c - x.y * s;
		x.y = t * s + x.y * c;

		t = y.x;
		y.x = t * c - y.y * s;
		y.y = t * s + y.y * c;

		t = z.x;
		z.x = t * c - z.y * s;
		z.y = t * s + z.y * c;
		break;
	default:
		assert(0);
	}
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotatePre(const Mat3& m)
{
	if (m.isIdentity())
		return *this;

	if (isIdentity())
		return set(m);

	Real x_x = x.x, x_y = x.y, x_z = x.z, y_x = y.x, y_y = y.y, y_z = y.z;

	x.x = x_x * m.x.x + y_x * m.x.y + z.x * m.x.z;
	y.x = x_x * m.y.x + y_x * m.y.y + z.x * m.y.z;
	z.x = x_x * m.z.x + y_x * m.z.y + z.x * m.z.z;
	x.y = x_y * m.x.x + y_y * m.x.y + z.y * m.x.z;
	y.y = x_y * m.y.x + y_y * m.y.y + z.y * m.y.z;
	z.y = x_y * m.z.x + y_y * m.z.y + z.y * m.z.z;
	x.z = x_z * m.x.x + y_z * m.x.y + z.z * m.x.z;
	y.z = x_z * m.y.x + y_z * m.y.y + z.z * m.y.z;
	z.z = x_z * m.z.x + y_z * m.z.y + z.z * m.z.z;

	flags &= m.flags;

	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotatePre(const Quat<Real>& q)
{
	Mat3 m;
	m.set(q);
	return rotatePre(m);
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotatePre(const Vec3<Real>& axis, Real angle)
{
	Mat3 m;
	m.set(axis, angle);
	return rotatePre(m);
}

template <class Real>
Mat3<Real>& Mat3<Real>::rotatePre(Coord axis, Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	Real t;
	switch (axis)
	{
	case Coord::X:
		t = y.x;
		y.x = t * c + z.x * s;
		z.x = -t * s + z.x * c;

		t = y.y;
		y.y = t * c + z.y * s;
		z.y = -t * s + z.y * c;

		t = y.z;
		y.z = t * c + z.z * s;
		z.z = -t * s + z.z * c;
		break;
	case Coord::Y:
		t = x.x;
		x.x = t * c - z.x * s;
		z.x = t * s + z.x * c;

		t = x.y;
		x.y = t * c - z.y * s;
		z.y = t * s + z.y * c;

		t = x.z;
		x.z = t * c - z.z * s;
		z.z = t * s + z.z * c;
		break;
	case Coord::Z:
		t = x.x;
		x.x = t * c + y.x * s;
		y.x = -t * s + y.x * c;

		t = x.y;
		x.y = t * c + y.y * s;
		y.y = -t * s + y.y * c;

		t = x.z;
		x.z = t * c + y.z * s;
		y.z = -t * s + y.z * c;
		break;
	default:
		assert(0);
	}
	return optimize();
}

template <class Real>
Mat3<Real>& Mat3<Real>::orthonormalise()
{
	Quat<Real> q;
	q.set(*this);
	q.normalize();
	return set(q);
}

template <class Real>
Mat3<Real>& Mat3<Real>::optimize(const Tolerance *tolerance)
{
	if (tolerance == nullptr)
		tolerance = &DefaultTolerance;

	bool isnormal = normalError() <= tolerance->normal;
	bool isorthogonal = orthogonalError() <= tolerance->orthogonal;
	bool isidentity = isnormal && isorthogonal && identityError() <= tolerance->identity;

	if (isnormal)
		flags |= Flags::Normal;
	else
		flags &= ~Flags::Normal;

	if (isorthogonal)
		flags |= Flags::Orthogonal;
	else
		flags &= ~Flags::Orthogonal;

	if (isidentity)
		flags |= Flags::Identity;
	else
		flags &= ~Flags::Identity;

	flags &= ~Flags::Uninitialized;

	return *this;
}

template <class Real>
Mat3<Real>& Mat3<Real>::transpose()
{
	Real t;
	t = x.y; x.y = y.x; y.x = t;
	t = x.z; x.z = z.x; z.x = t;
	t = y.z; y.z = z.y; z.y = t;
	// flags unchanged by transposition
	return *this;
}

template <class Real>
Mat3<Real>& Mat3<Real>::invert()
{
	if (isOrthonormal())
		return transpose();

	Real det = determinant();
	return (det == Real(0)) ? set(Zero) : set(adjoint() / det);
}


//
//  Functions
//

template <class Real>
Mat3<Real> Mat3<Real>::scaled(const Vec3<Real>& coefficients) const
{
	Mat3 r;
	r.x = x * coefficients.x;
	r.y = y * coefficients.y;
	r.z = z * coefficients.z;
	r.optimize();
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::transposed() const
{
	Mat3 r;
	r.x.x = x.x;
	r.x.y = y.x;
	r.x.z = z.x;
	r.y.x = x.y;
	r.y.y = y.y;
	r.y.z = z.y;
	r.z.x = x.z;
	r.z.y = y.z;
	r.z.z = z.z;
	r.flags = flags;
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::cofactors() const
{
	Mat3 r;
	r.x.x = y.y * z.z - z.y * y.z;
	r.x.y = z.x * y.z - y.x * z.z;
	r.x.z = y.x * z.y - z.x * y.y;
	r.y.x = z.y * x.z - x.y * z.z;
	r.y.y = x.x * z.z - z.x * x.z;
	r.y.z = z.x * x.y - x.x * z.y;
	r.z.x = x.y * y.z - y.y * x.z;
	r.z.y = y.x * x.z - x.x * y.z;
	r.z.z = x.x * y.y - y.x * x.y;
	r.optimize();
	return r;
}

template <class Real>
Mat3<Real> Mat3<Real>::adjoint() const
{
	Mat3 r;
	r.x.x = y.y * z.z - z.y * y.z;
	r.x.y = z.y * x.z - x.y * z.z;
	r.x.z = x.y * y.z - y.y * x.z;
	r.y.x = z.x * y.z - y.x * z.z; 
	r.y.y = x.x * z.z - z.x * x.z;
	r.y.z = y.x * x.z - x.x * y.z;
	r.z.x = y.x * z.y - z.x * y.y; 
	r.z.y = z.x * x.y - x.x * z.y; 
	r.z.z = x.x * y.y - y.x * x.y;
	r.optimize();
	return r;
}

template <class Real>
Real Mat3<Real>::trace() const
{
	return x.x + y.y + z.z;
}

template <class Real>
Real Mat3<Real>::determinant() const
{
	return	x.x * (y.y * z.z - z.y * y.z) -
			y.x * (x.y * z.z - z.y * x.z) +
			z.x * (x.y * y.z - y.y * x.z);
}

template <class Real>
Mat3<Real> Mat3<Real>::inversed() const
{
	Real det = determinant();
	return (det == Real(0)) ? Zero : adjoint() / det;
}

template <class Real>
Real Mat3<Real>::normalError() const
{
	Real cx = (x * x) - Real(1);
	Real cy = (y * y) - Real(1);
	Real cz = (z * z) - Real(1);
	return cx * cx + cy * cy + cz * cz;
}

template <class Real>
Real Mat3<Real>::orthogonalError() const
{
	Real xy = x * y;
	Real xz = x * z;
	Real yz = y * z;
	return xy * xy + xz * xz + yz * yz;
}

template <class Real>
Real Mat3<Real>::identityError() const
{
	Vec3<Real> rx = { x.x - Real(1), x.y, x.z };
	Vec3<Real> ry = { y.x, y.y - Real(1), y.z };
	Vec3<Real> rz = { z.x, z.y, z.z - Real(1) };
	return rx.lengthSqr() + ry.lengthSqr() + rz.lengthSqr();
}

template <class Real>
bool Mat3<Real>::isNormal() const
{
	return (flags & Flags::Normal);
}

template <class Real>
bool Mat3<Real>::isOrthogonal() const
{
	return (flags & Flags::Orthogonal);
}

template <class Real>
bool Mat3<Real>::isOrthonormal() const
{
	return (flags & Flags::Mask) == Flags::Mask;
}

template <class Real>
bool Mat3<Real>::isIdentity() const
{
	return (flags & Flags::Identity);
}

template <class Real>
bool Mat3<Real>::isInitialized() const
{
	return !(flags & Flags::Uninitialized);
}

template <class Real>
void Mat3<Real>::transform(Vec3<Real>& dest, const Vec3<Real>& src) const
{
	dest.x = src.x * x.x + src.y * y.x + src.z * z.x;
	dest.y = src.x * x.y + src.y * y.y + src.z * z.y;
	dest.z = src.x * x.z + src.y * y.z + src.z * z.z;
}

template <class Real>
void Mat3<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const
{
	for (size_t i = 0; i < count; i++)
	{
		transform(*dest++, *src++);
	}
}

template <class Real>
void Mat3<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
	size_t destStride, size_t srcStride) const
{
	const char* d = (const char*)dest;
	const char* s = (const char*)src;
	for (size_t i = 0; i < count; i++)
	{
		transform(*((Vec3<Real>*)d), *((const Vec3<Real>*)s));
		d += destStride;
		s += srcStride;
	}
}

template <class Real>
void Mat3<Real>::multiply(Mat3& dest, const Mat3& a, const Mat3& b)
{
	assert(&dest != &a && &dest != &b);

	if (a.isIdentity())
	{
		dest.set(b);
	}
	else if (b.isIdentity())
	{
		dest.set(a);
	}
	else
	{
		dest.x.x = a.x.x * b.x.x + a.y.x * b.x.y + a.z.x * b.x.z;
		dest.y.x = a.x.x * b.y.x + a.y.x * b.y.y + a.z.x * b.y.z;
		dest.z.x = a.x.x * b.z.x + a.y.x * b.z.y + a.z.x * b.z.z;
		dest.x.y = a.x.y * b.x.x + a.y.y * b.x.y + a.z.y * b.x.z;
		dest.y.y = a.x.y * b.y.x + a.y.y * b.y.y + a.z.y * b.y.z;
		dest.z.y = a.x.y * b.z.x + a.y.y * b.z.y + a.z.y * b.z.z;
		dest.x.z = a.x.z * b.x.x + a.y.z * b.x.y + a.z.z * b.x.z;
		dest.y.z = a.x.z * b.y.x + a.y.z * b.y.y + a.z.z * b.y.z;
		dest.z.z = a.x.z * b.z.x + a.y.z * b.z.y + a.z.z * b.z.z;
		dest.flags = a.flags & b.flags;
	}
}

MATHLIB_NS_END
