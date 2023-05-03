#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Mat4<Real> Mat4<Real>::Zero = Mat4<Real>(Real(0));

template <class Real>
const Mat4<Real> Mat4<Real>::One = Mat4<Real>(Real(1));

template <class Real>
const typename Mat4<Real>::Tolerance Mat4<Real>::DefaultTolerance = { Real(0.001), Real(0.001), Real(0.001) };

//
//  Constructors
//

template <class Real>
Mat4<Real>::Mat4()
	: flags(Flags::Uninitialized)
{
}

template <class Real>
Mat4<Real>::Mat4(Real k)
{
	x.x = k;		y.x = Real(0);	z.x = Real(0);	t.x = Real(0);
	x.y = Real(0);	y.y = k;		z.y = Real(0);	t.y = Real(0);
	x.z = Real(0);	y.z = Real(0);	z.z = k;		t.z = Real(0);
	x.w = Real(0);	y.w = Real(0);	z.w = Real(0);	t.w = Real(1);
	flags = Flags::Orthogonal;
	if (k == Real(1))
	{
		flags |= Flags::Normal | Flags::Identity;
	}
}

template <class Real>
Mat4<Real>::Mat4(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t)
{
	set(x, y, z, t);
}

template <class Real>
Mat4<Real>::Mat4(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t)
{
	set(x, y, z, t);
}


//
// Setters
//

template <class Real>
Mat4<Real>& Mat4<Real>::setIdentity()
{
	x = Vec4<Real>::OneX;
	y = Vec4<Real>::OneY;
	z = Vec4<Real>::OneZ;
	t = Vec4<Real>::OneW;
	flags = Flags::Orthonormal | Flags::Identity;
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(const Mat4<Real>& m)
{
	x = m.x;
	y = m.y;
	z = m.z;
	t = m.t;
	flags = m.flags;
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(const Quat<Real>& q, const Vec3<Real>& t)
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
	x.w = Real(0);

	y.x = Real(2) * (xy - wz);
	y.y = Real(1) - Real(2) * (xx + zz);
	y.z = Real(2) * (yz + wx);
	y.w = Real(0);

	z.x = Real(2) * (zx + wy);
	z.y = Real(2) * (yz - wx);
	z.z = Real(1) - Real(2) * (xx + yy);
	z.w = Real(0);

	this->t = Vec4<Real>(t, Real(1));

	return optimize();
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = Vec4<Real>(t, Real(1));
	return optimize();
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
	return optimize();
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
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
Mat4<Real>& Mat4<Real>::set(const Vec3<Real>& axis, Real angle)
{
	Vec3<Real> v = axis.normalized();

	Real s = sin(angle);
	Real c = cos(angle);
	Real f = Real(1) - c;

	x.x = c + v.x * v.x * f;
	x.y = v.x * v.y * f + v.z * s;
	x.z = v.z * v.x * f - v.y * s;

	y.x = v.x * v.y * f - v.z * s;
	y.y = c + v.y * v.y * f;
	y.z = v.y * v.z * f + v.x * s;

	z.x = v.z * v.x * f + v.y * s;
	z.y = v.y * v.z * f - v.x * s;
	z.z = c + v.z * v.z * f;

	t.x = t.y = t.z = x.w = y.w = z.w = Real(0);
	t.w = Real(1);

	return optimize();
}

template <class Real>
Mat4<Real>& Mat4<Real>::set(Coord axis, Real angle)
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

	t.x = t.y = t.z = x.w = y.w = z.w = Real(0);
	t.w = Real(1);

	return optimize();
}


//
// Create from
//

template <class Real>
Mat4<Real> Mat4<Real>::from(const Quat<Real>& q, const Vec3<Real>& t)
{
	Mat4<Real> r;
	r.set(q, t);
	return r;
}

template <class Real>
Mat4<Real> Mat4<Real>::from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t)
{
	Mat4<Real> r;
	r.set(x, y, z, t);
	return r;
}

template <class Real>
Mat4<Real> Mat4<Real>::from(const Vec4<Real>& x, const Vec4<Real>& y, const Vec4<Real>& z, const Vec4<Real>& t)
{
	Mat4<Real> r;
	r.set(x, y, z, t);
	return r;
}

template <class Real>
Mat4<Real> Mat4<Real>::from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
{
	Mat4<Real> r;
	r.set(ecoord, exact, acoord, approx);
	return r;
}

template <class Real>
Mat4<Real> Mat4<Real>::from(const Vec3<Real>& axis, Real angle)
{
	Mat4<Real> r;
	r.set(axis, angle);
	return r;
}

template <class Real>
Mat4<Real> Mat4<Real>::from(Coord axis, Real angle)
{
	Mat4<Real> r;
	r.set(axis, angle);
	return r;
}


//
//  Assignments
//

template <class Real>
Mat4<Real>& Mat4<Real>::operator*=(Real k)
{
	if (k == Real(1))
		return *this;
	x *= k;
	y *= k;
	z *= k;
	t *= k;
	return optimize();
}

template <class Real>
Mat4<Real>& Mat4<Real>::operator/=(Real k)
{
	assert(k != Real(0));
	if (k == Real(1))
		return *this;
	Real invk = Real(1) / k;
	x *= invk;
	y *= invk;
	z *= invk;
	t *= invk;
	return optimize();
}


//
//  Arithmetic operators
//

template <class Real>
Mat4<Real> Mat4<Real>::operator-() const
{
	return Mat4(-x, -y, -z, -t);
}

template <class Real>
Mat4<Real> Mat4<Real>::operator*(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	return Mat4(x * k, y * k, z * k, t * k);
}

template <class Real>
Mat4<Real> Mat4<Real>::operator/(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	Real invk = Real(1) / k;
	return Mat4(x * invk, y * invk, z * invk, t * invk);
}

template <class Real>
Mat4<Real> Mat4<Real>::operator*(const Mat4& m) const
{
	Mat4 r;
	multiply(r, *this, m);
	return r;
}

template <class Real>
Vec3<Real> Mat4<Real>::operator*(const Vec3<Real>& u) const
{
	Vec3<Real> r;
	transform(r, u);
	return r;
}


//
// Comparison operators
//

template <class Real>
bool Mat4<Real>::operator==(const Mat4& m) const
{
	return x == m.x && y == m.y && z == m.z && t == m.t;
}

template <class Real>
bool Mat4<Real>::operator!=(const Mat4& m) const
{
	return x != m.x || y != m.y || z != m.z || t != m.t;
}

// Transformations

template <class Real>
Mat4<Real>& Mat4<Real>::rotate(const Quat<Real>& q)
{
	Mat4 rot;
	rot.set(q);
	return transform(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::rotate(const Vec3<Real>& axis, Real angle)
{
	Mat4 rot;
	rot.set(axis, angle);
	return transform(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::rotate(Coord axis, Real angle)
{
	Mat4 rot;
	rot.set(axis, angle);
	return transform(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::translate(const Vec3<Real>& translation)
{
	t += translation;
	if (!translation.isNull())
	{
		flags &= ~Flags::Identity;
	}
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::scale(const Vec3<Real>& coefficients)
{
	// r * v = scale * (rs * v + t)
	//       = (scale * rs) * v + (scale * t)
	x *= coefficients.x;
	y *= coefficients.y;
	z *= coefficients.z;
	t.x *= coefficients.x;
	t.y *= coefficients.y;
	t.z *= coefficients.z;
	if (coefficients.x != Real(1) || coefficients.y != Real(1) || coefficients.z != Real(1))
	{
		flags &= ~Flags::Identity;
	}
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::transform(const Mat4& m)
{
	if (m.isIdentity())
		return *this;

	if (isIdentity())
		return set(m);

	Mat4 d;
	multiply(d, m, *this);

	return set(d);
}

template <class Real>
Mat4<Real>& Mat4<Real>::rotatePre(const Quat<Real>& q)
{
	Mat4 rot;
	rot.set(q);
	return transformPre(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::rotatePre(const Vec3<Real>& axis, Real angle)
{
	Mat4 rot;
	rot.set(axis, angle);
	return transformPre(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::rotatePre(Coord axis, Real angle)
{
	Mat4 rot;
	rot.set(axis, angle);
	return transformPre(rot);
}

template <class Real>
Mat4<Real>& Mat4<Real>::translatePre(const Vec3<Real>& translation)
{
	// r * v = rs * (v + translation) + t
	//       = (rs) * v + (rs * translation + t)
	Vec3<Real> delta;
	transformVector(delta, translation);
	t += delta;
	if (!translation.isNull())
	{
		flags &= ~Flags::Identity;
	}
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::scalePre(const Vec3<Real>& coefficients)
{
	// r * v = rs * (scale * v) + t
	//       = (rs * scale) * v + (t)
	x *= coefficients.x;
	y *= coefficients.y;
	z *= coefficients.z;
	if (coefficients.x != Real(1) || coefficients.y != Real(1) || coefficients.z != Real(1))
	{
		flags &= ~Flags::Identity;
	}
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::transformPre(const Mat4& m)
{
	if (m.isIdentity())
		return *this;

	if (isIdentity())
		return set(m);

	Mat4 d;
	multiply(d, *this, m);

	return set(d);
}

template <class Real>
Mat4<Real>& Mat4<Real>::orthonormalise()
{
	Quat<Real> q;
	q.set(*this);
	q.normalize();
	return set(q);
}

template <class Real>
Mat4<Real>& Mat4<Real>::optimize(const Tolerance* tolerance)
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
Mat4<Real>& Mat4<Real>::transpose()
{
	Real r;
	r = x.y; x.y = y.x; y.x = r;
	r = x.z; x.z = z.x; z.x = r;
	r = x.w; x.w = t.x; t.x = r;
	r = y.z; y.z = z.y; z.y = r;
	r = y.w; y.w = t.y; t.y = r;
	r = z.w; z.w = t.z; t.z = r;
	// flags unchanged by transposition
	return *this;
}

template <class Real>
Mat4<Real>& Mat4<Real>::invert()
{
	if (isOrthonormal())
	{
		Real r;
		r = x.y; x.y = y.x; y.x = r;
		r = x.z; x.z = z.x; z.x = r;
		r = y.z; y.z = z.y; z.y = r;

		Real tx = x.x * t.x + y.x * t.y + z.x * t.z;
		Real ty = x.y * t.x + y.y * t.y + z.y * t.z;
		Real tz = x.z * t.x + y.z * t.y + z.z * t.z;

		t.x = -tx;
		t.y = -ty;
		t.z = -tz;

		// flags unchanged by transposition

		return *this;
	}

	Real CF00 = (z.z * t.w - z.w * t.z);
	Real CF01 = (y.z * t.w - y.w * t.z);
	Real CF02 = (y.z * z.w - y.w * z.z);
	Real CF03 = (z.y * t.w - z.w * t.y);
	Real CF04 = (y.y * t.w - y.w * t.y);
	Real CF05 = (y.y * z.w - y.w * z.y);
	Real CF06 = (z.y * t.z - z.z * t.y);
	Real CF07 = (y.y * t.z - y.z * t.y);
	Real CF08 = (y.y * z.z - y.z * z.y);
	Real CF09 = (x.z * t.w - x.w * t.z);
	Real CF10 = (x.z * z.w - x.w * z.z);
	Real CF11 = (x.y * t.w - x.w * t.y);
	Real CF12 = (x.y * z.w - x.w * z.y);
	Real CF13 = (x.y * t.z - x.z * t.y);
	Real CF14 = (x.y * z.z - x.z * z.y);
	Real CF15 = (y.z * t.w - y.w * t.z);
	Real CF16 = (x.z * y.w - x.w * y.z);
	Real CF17 = (x.y * y.w - x.w * y.y);
	Real CF18 = (x.y * y.z - x.z * y.y);
	Real CF19 = (y.z * z.w - y.w * z.z);

	Mat4 inv;

	inv.x.x = y.y * CF00 - z.y * CF01 + t.y * CF02;
	inv.y.x = -y.x * CF00 + z.x * CF01 - t.x * CF02;
	inv.z.x = y.x * CF03 - z.x * CF04 + t.x * CF05;
	inv.t.x = -y.x * CF06 + z.x * CF07 - t.x * CF08;
	inv.x.y = -x.y * CF00 + z.y * CF09 - t.y * CF10;
	inv.y.y = x.x * CF00 - z.x * CF09 + t.x * CF10;
	inv.z.y = -x.x * CF03 + z.x * CF11 - t.x * CF12;
	inv.t.y = x.x * CF06 - z.x * CF13 + t.x * CF14;
	inv.x.z = x.y * CF15 - y.y * CF09 + t.y * CF16;
	inv.y.z = -x.x * CF15 + y.x * CF09 - t.x * CF16;
	inv.z.z = x.x * CF04 - y.x * CF11 + t.x * CF17;
	inv.t.z = -x.x * CF07 + y.x * CF13 - t.x * CF18;
	inv.x.w = -x.y * CF19 + y.y * CF10 - z.y * CF16;
	inv.y.w = x.x * CF19 - y.x * CF10 + z.x * CF16;
	inv.z.w = -x.x * CF05 + y.x * CF12 - z.x * CF17;
	inv.t.w = x.x * CF08 - y.x * CF14 + z.x * CF18;

	Real det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x + x.w * inv.t.x;

	return (det == Real(0)) ? set(Zero) : set(inv / det);
}


//
//  Functions
//

template <class Real>
Mat4<Real> Mat4<Real>::transposed() const
{
	Mat4 r;

	r.x.x = x.x;
	r.x.y = y.x;
	r.x.z = z.x;
	r.x.w = t.x;

	r.y.x = x.y;
	r.y.y = y.y;
	r.y.z = z.y;
	r.y.w = t.y;

	r.z.x = x.z;
	r.z.y = y.z;
	r.z.z = z.z;
	r.z.w = t.z;

	r.t.x = x.w;
	r.t.y = y.w;
	r.t.z = z.w;
	r.t.w = t.w;

	r.flags = flags;

	return r;
}

template <class Real>
Real Mat4<Real>::trace() const
{
	return x.x + y.y + z.z + t.w;
}

template <class Real>
Real Mat4<Real>::determinant() const
{
	Real CF00 = (z.z * t.w - z.w * t.z);
	Real CF01 = (y.z * t.w - y.w * t.z);
	Real CF02 = (y.z * z.w - y.w * z.z);
	Real CF03 = (z.y * t.w - z.w * t.y);
	Real CF04 = (y.y * t.w - y.w * t.y);
	Real CF05 = (y.y * z.w - y.w * z.y);
	Real CF06 = (z.y * t.z - z.z * t.y);
	Real CF07 = (y.y * t.z - y.z * t.y);
	Real CF08 = (y.y * z.z - y.z * z.y);

	Real inv_x_x = y.y * CF00 - z.y * CF01 + t.y * CF02;
	Real inv_y_x = -y.x * CF00 + z.x * CF01 - t.x * CF02;
	Real inv_z_x = y.x * CF03 - z.x * CF04 + t.x * CF05;
	Real inv_t_x = -y.x * CF06 + z.x * CF07 - t.x * CF08;

	Real det = x.x * inv_x_x + x.y * inv_y_x + x.z * inv_z_x + x.w * inv_t_x;

	return det;
}

template <class Real>
Mat4<Real> Mat4<Real>::inversed() const
{
	if (isOrthonormal())
		return transposed();

	Real CF00 = (z.z * t.w - z.w * t.z);
	Real CF01 = (y.z * t.w - y.w * t.z);
	Real CF02 = (y.z * z.w - y.w * z.z);
	Real CF03 = (z.y * t.w - z.w * t.y);
	Real CF04 = (y.y * t.w - y.w * t.y);
	Real CF05 = (y.y * z.w - y.w * z.y);
	Real CF06 = (z.y * t.z - z.z * t.y);
	Real CF07 = (y.y * t.z - y.z * t.y);
	Real CF08 = (y.y * z.z - y.z * z.y);
	Real CF09 = (x.z * t.w - x.w * t.z);
	Real CF10 = (x.z * z.w - x.w * z.z);
	Real CF11 = (x.y * t.w - x.w * t.y);
	Real CF12 = (x.y * z.w - x.w * z.y);
	Real CF13 = (x.y * t.z - x.z * t.y);
	Real CF14 = (x.y * z.z - x.z * z.y);
	Real CF15 = (y.z * t.w - y.w * t.z);
	Real CF16 = (x.z * y.w - x.w * y.z);
	Real CF17 = (x.y * y.w - x.w * y.y);
	Real CF18 = (x.y * y.z - x.z * y.y);
	Real CF19 = (y.z * z.w - y.w * z.z);

	Mat4 inv;

	inv.x.x = y.y * CF00 - z.y * CF01 + t.y * CF02;
	inv.y.x = -y.x * CF00 + z.x * CF01 - t.x * CF02;
	inv.z.x = y.x * CF03 - z.x * CF04 + t.x * CF05;
	inv.t.x = -y.x * CF06 + z.x * CF07 - t.x * CF08;
	inv.x.y = -x.y * CF00 + z.y * CF09 - t.y * CF10;
	inv.y.y = x.x * CF00 - z.x * CF09 + t.x * CF10;
	inv.z.y = -x.x * CF03 + z.x * CF11 - t.x * CF12;
	inv.t.y = x.x * CF06 - z.x * CF13 + t.x * CF14;
	inv.x.z = x.y * CF15 - y.y * CF09 + t.y * CF16;
	inv.y.z = -x.x * CF15 + y.x * CF09 - t.x * CF16;
	inv.z.z = x.x * CF04 - y.x * CF11 + t.x * CF17;
	inv.t.z = -x.x * CF07 + y.x * CF13 - t.x * CF18;
	inv.x.w = -x.y * CF19 + y.y * CF10 - z.y * CF16;
	inv.y.w = x.x * CF19 - y.x * CF10 + z.x * CF16;
	inv.z.w = -x.x * CF05 + y.x * CF12 - z.x * CF17;
	inv.t.w = x.x * CF08 - y.x * CF14 + z.x * CF18;

	Real det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x + x.w * inv.t.x;

	if (det == Real(0))
		return Zero;

	inv /= det;

	inv.optimize();

	return inv;
}

template <class Real>
Real Mat4<Real>::normalError() const
{
	Real cx = (x * x) - Real(1);
	Real cy = (y * y) - Real(1);
	Real cz = (z * z) - Real(1);
	Real ct = (t * t) - Real(1);
	return cx * cx + cy * cy + cz * cz + ct * ct;
}

template <class Real>
Real Mat4<Real>::orthogonalError() const
{
	Real xy = x * y;
	Real xz = x * z;
	Real yz = y * z;
	return xy * xy + xz * xz + yz * yz;
}

template <class Real>
Real Mat4<Real>::identityError() const
{
	Vec4<Real> rx = { x.x - Real(1), x.y, x.z, x.w };
	Vec4<Real> ry = { y.x, y.y - Real(1), y.z, y.w };
	Vec4<Real> rz = { z.x, z.y, z.z - Real(1), z.w };
	Vec4<Real> rt = { t.x, t.y, t.z, t.w - Real(1) };
	return rx.lengthSqr() + ry.lengthSqr() + rz.lengthSqr() + rt.lengthSqr();
}

template <class Real>
bool Mat4<Real>::isNormal() const
{
	return (flags & Flags::Normal);
}

template <class Real>
bool Mat4<Real>::isOrthogonal() const
{
	return (flags & Flags::Orthogonal);
}

template <class Real>
bool Mat4<Real>::isOrthonormal() const
{
	return (flags & Flags::Orthonormal) == Flags::Orthonormal;
}

template <class Real>
bool Mat4<Real>::isIdentity() const
{
	return (flags & Flags::Identity);
}

template <class Real>
bool Mat4<Real>::isInitialized() const
{
	return !(flags & Flags::Uninitialized);
}

template <class Real>
const Real* Mat4<Real>::data() const
{
	return x.data();
}

template <class Real>
Real* Mat4<Real>::data()
{
	return x.data();
}

template <class Real>
template <class CastReturnType>
Mat4<CastReturnType> Mat4<Real>::cast() const
{
	return Mat4<CastReturnType>::from(
		x.template cast<CastReturnType>(),
		y.template cast<CastReturnType>(),
		z.template cast<CastReturnType>(),
		t.template cast<CastReturnType>()
	);
}

template <class Real>
void Mat4<Real>::transform(Vec3<Real>& dest, const Vec3<Real>& src) const
{
	dest.x = src.x * x.x + src.y * y.x + src.z * z.x + t.x;
	dest.y = src.x * x.y + src.y * y.y + src.z * z.y + t.y;
	dest.z = src.x * x.z + src.y * y.z + src.z * z.z + t.z;
}

template <class Real>
void Mat4<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const
{
	for (size_t i = 0; i < count; i++)
	{
		transform(*dest++, *src++);
	}
}

template <class Real>
void Mat4<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
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
void Mat4<Real>::transformVector(Vec3<Real>& dest, const Vec3<Real>& src) const
{
	dest.x = src.x * x.x + src.y * y.x + src.z * z.x;
	dest.y = src.x * x.y + src.y * y.y + src.z * z.y;
	dest.z = src.x * x.z + src.y * y.z + src.z * z.z;
}

template <class Real>
void Mat4<Real>::transformVector(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const
{
	for (size_t i = 0; i < count; i++)
	{
		transformVector(*dest++, *src++);
	}
}

template <class Real>
void Mat4<Real>::transformVector(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
	size_t destStride, size_t srcStride) const
{
	const char* d = (const char*)dest;
	const char* s = (const char*)src;
	for (size_t i = 0; i < count; i++)
	{
		transformVector(*((Vec3<Real>*)d), *((const Vec3<Real>*)s));
		d += destStride;
		s += srcStride;
	}
}

template <class Real>
void Mat4<Real>::multiply(Mat4& dest, const Mat4& a, const Mat4& b)
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
		dest.x.x = a.x.x * b.x.x + a.y.x * b.x.y + a.z.x * b.x.z + a.t.x * b.x.w;
		dest.y.x = a.x.x * b.y.x + a.y.x * b.y.y + a.z.x * b.y.z + a.t.x * b.y.w;
		dest.z.x = a.x.x * b.z.x + a.y.x * b.z.y + a.z.x * b.z.z + a.t.x * b.z.w;
		dest.t.x = a.x.x * b.t.x + a.y.x * b.t.y + a.z.x * b.t.z + a.t.x * b.t.w;

		dest.x.y = a.x.y * b.x.x + a.y.y * b.x.y + a.z.y * b.x.z + a.t.y * b.x.w;
		dest.y.y = a.x.y * b.y.x + a.y.y * b.y.y + a.z.y * b.y.z + a.t.y * b.y.w;
		dest.z.y = a.x.y * b.z.x + a.y.y * b.z.y + a.z.y * b.z.z + a.t.y * b.z.w;
		dest.t.y = a.x.y * b.t.x + a.y.y * b.t.y + a.z.y * b.t.z + a.t.y * b.t.w;

		dest.x.z = a.x.z * b.x.x + a.y.z * b.x.y + a.z.z * b.x.z + a.t.z * b.x.w;
		dest.y.z = a.x.z * b.y.x + a.y.z * b.y.y + a.z.z * b.y.z + a.t.z * b.y.w;
		dest.z.z = a.x.z * b.z.x + a.y.z * b.z.y + a.z.z * b.z.z + a.t.z * b.z.w;
		dest.t.z = a.x.z * b.t.x + a.y.z * b.t.y + a.z.z * b.t.z + a.t.z * b.t.w;

		dest.x.w = a.x.w * b.x.x + a.y.w * b.x.y + a.z.w * b.x.z + a.t.w * b.x.w;
		dest.y.w = a.x.w * b.y.x + a.y.w * b.y.y + a.z.w * b.y.z + a.t.w * b.y.w;
		dest.z.w = a.x.w * b.z.x + a.y.w * b.z.y + a.z.w * b.z.z + a.t.w * b.z.w;
		dest.t.w = a.x.w * b.t.x + a.y.w * b.t.y + a.z.w * b.t.z + a.t.w * b.t.w;

		dest.flags = a.flags & b.flags;
	}
}

MATHLIB_NS_END
