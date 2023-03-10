#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Mat34<Real> Mat34<Real>::Zero = Mat34<Real>(Mat3<Real>(0), Vec3<Real>(0));

template <class Real>
const Mat34<Real> Mat34<Real>::One = Mat34<Real>(Mat3<Real>(1), Vec3<Real>(0));

//
//  Constructors
//

template <class Real>
Mat34<Real>::Mat34()
{
}

template <class Real>
Mat34<Real>::Mat34(Real k)
	: rs(k), t(Real(0))
{
}

template <class Real>
Mat34<Real>::Mat34(const Mat3<Real> &rs, const Vec3<Real> &t)
{
	this->rs = rs;
	this->t = t;
}

template <class Real>
Mat34<Real>::Mat34(const Vec3<Real> &x, const Vec3<Real> &y,
                   const Vec3<Real> &z, const Vec3<Real> &t)
{
	this->rs.x = x;
	this->rs.y = y;
	this->rs.z = z;
	this->t = t;
	optimize();
}

//
// Setters
//

template <class Real>
Mat34<Real>& Mat34<Real>::setIdentity()
{
	rs.setIdentity();
	t.set(Vec3<Real>::Zero);
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(const Mat34& m)
{
	this->rs = m.rs;
	this->t = m.t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(const Mat3<Real> &rs, const Vec3<Real> &t)
{
	this->rs = rs;
	this->t = t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(const Vec3<Real> &x, const Vec3<Real> &y,
                              const Vec3<Real> &z, const Vec3<Real> &t)
{
	this->rs.set(x, y, z);
	this->t = t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
{
	this->rs.set(ecoord, exact, acoord, approx);
	this->t = Vec3<Real>::Zero;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(const Vec3<Real> &axis, Real angle, const Vec3<Real>& t)
{
	this->rs.set(axis, angle);
	this->t = t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(Coord axis, Real angle, const Vec3<Real>& t)
{
	this->rs.set(axis, angle);
	this->t = t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::set(const Quat<Real> &q, const Vec3<Real>& t)
{
	this->rs.set(q);
	this->t = t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::slerp(const Mat34& a, const Mat34& b, Real weight)
{
	this->rs.slerp(a.rs, b.rs, weight);
	this->t = Vec3<Real>::Zero;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::slerpMaxAngle(const Mat34& a, const Mat34& b, Real maxAngle)
{
	this->rs.slerpMaxAngle(a.rs, b.rs, maxAngle);
	this->t = Vec3<Real>::Zero;
	return *this;
}


//
// Create from
//

template <class Real>
Mat34<Real> Mat34<Real>::from(const Quat<Real>& q, const Vec3<Real>& t)
{
	Mat34<Real> r;
	r.set(q, t);
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::from(const Vec3<Real>& x, const Vec3<Real>& y, const Vec3<Real>& z, const Vec3<Real>& t)
{
	Mat34<Real> r;
	r.set(x, y, z, t);
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)
{
	Mat34<Real> r;
	r.set(ecoord, exact, acoord, approx);
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::from(const Vec3<Real>& axis, Real angle, const Vec3<Real>& t)
{
	Mat34<Real> r;
	r.set(axis, angle, t);
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::fromSlerp(const Mat34& a, const Mat34& b, Real weight)
{
	Mat34<Real> r;
	r.slerp(a, b, weight);
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::fromSlerpMaxAngle(const Mat34& a, const Mat34& b, Real maxAngle)
{
	Mat34<Real> r;
	r.slerpMaxAngle(a, b, maxAngle);
	return r;
}


//
//  Assignments
//

template <class Real>
Mat34<Real>& Mat34<Real>::operator*=(const Mat3<Real>& m)
{
	return transformPre(m);
}

template <class Real>
Mat34<Real>& Mat34<Real>::operator*=(const Mat34& m)
{
	return transformPre(m);
}


//
//  Arithmetic operators
//

template <class Real>
Mat34<Real> Mat34<Real>::operator-() const
{
	return Mat34(-rs, -t);
}

template <class Real>
Mat34<Real> Mat34<Real>::operator*(const Mat3<Real>& m) const
{
	Mat34 r;
	Mat3<Real>::multiply(r.rs, rs, m);
	r.t = t;
	return r;
}

template <class Real>
Mat34<Real> Mat34<Real>::operator*(const Mat34& m) const
{
	// r * v = rs * (m.rs * v + m.t) + t
	//       = (rs * m.rs) * v + (rs * m.t + t)
	Mat34 r;
	Mat3<Real>::multiply(r.rs, rs, m.rs);
	r.t = t + rs * m.t;
	return r;
}

template <class Real>
Vec3<Real> Mat34<Real>::operator*(const Vec3<Real>& u) const
{
	Vec3<Real> r;
	transform(r, u);
	return r;
}


//
// Comparison operators
//

template <class Real>
bool Mat34<Real>::operator==(const Mat34& m) const
{
	return rs == m.rs && t == m.t;
}

template <class Real>
bool Mat34<Real>::operator!=(const Mat34& m) const
{
	return rs != m.rs || t != m.t;
}


//
// Transformations
//

template <class Real>
Mat34<Real>& Mat34<Real>::rotate(const Quat<Real> &q)
{
	Mat3<Real> rot;
	rot.set(q);
	return transform(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::rotate(const Vec3<Real>& axis, Real angle)
{
	Mat3<Real> rot;
	rot.set(axis, angle);
	return transform(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::rotate(Coord axis, Real angle)
{
	Mat3<Real> rot;
	rot.set(axis, angle);
	return transform(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::translate(const Vec3<Real>& translation)
{
	t += translation;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::scale(const Vec3<Real>& coefficients)
{
	// r * v = scale * (rs * v + t)
	//       = (scale * rs) * v + (scale * t)
	rs.scale(coefficients);
	t.x *= coefficients.x;
	t.y *= coefficients.y;
	t.z *= coefficients.z;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::transform(const Mat3<Real>& m)
{
	// r * v = m * (rs * v + t)
	//       = (m * rs) * v + (m * t)
	rs.rotate(m);
	t = m * t;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::transform(const Mat34& m)
{
	// r * v = m.rs * (rs * v + t) + m.t
	//       = (m.rs * rs) * v + (m.rs * t + m.t)
	t = m * t;
	rs.rotate(m.rs);
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::rotatePre(const Quat<Real>& q)
{
	Mat3<Real> rot;
	rot.set(q);
	return transformPre(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::rotatePre(const Vec3<Real>& axis, Real angle)
{
	Mat3<Real> rot;
	rot.set(axis, angle);
	return transformPre(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::rotatePre(Coord axis, Real angle)
{
	Mat3<Real> rot;
	rot.set(axis, angle);
	return transformPre(rot);
}

template <class Real>
Mat34<Real>& Mat34<Real>::translatePre(const Vec3<Real>& translation)
{
	// r * v = rs * (v + translation) + t
	//       = (rs) * v + (rs * translation + t)
	t += rs * translation;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::scalePre(const Vec3<Real>& coefficients)
{
	// r * v = rs * (scale * v) + t
	//       = (rs * scale) * v + (t)
	rs.scale(coefficients);
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::transformPre(const Mat3<Real>& m)
{
	rs *= m;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::transformPre(const Mat34& m)
{
	// r * v = rs * (m.rs * v + m.t) + t
	//       = (rs * m.rs) * v + (rs * m.t + t)
	t += rs * m.t;
	rs *= m.rs;
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::optimize(const Tolerance* tolerance)
{
	rs.optimize(tolerance);
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::invert()
{
	if (isIdentity())
		return *this;
	if (isOrthonormal())
	{
		t = -t * rs;
		rs.transpose();
	}
	else
	{
		//t = -t * rs;
		rs.invert();
		t = -(rs * t);
	}
	return *this;
}

template <class Real>
Mat34<Real>& Mat34<Real>::transpose()
{
	rs.transpose();
	return *this;
}

//
// Functions
//

template <class Real>
bool Mat34<Real>::isNormal() const
{
	return rs.isNormal();
}

template <class Real>
bool Mat34<Real>::isOrthogonal() const
{
	return rs.isOrthogonal();
}

template <class Real>
bool Mat34<Real>::isOrthonormal() const
{
	return rs.isOrthonormal();
}

template <class Real>
bool Mat34<Real>::isIdentity() const
{
	return rs.isIdentity() && t.isNull();
}

template <class Real>
bool Mat34<Real>::isInitialized() const
{
	return rs.isInitialized();
}

template <class Real>
template <class CastReturnType>
Mat34<CastReturnType> Mat34<Real>::cast() const
{
	return Mat34<CastReturnType>(rs.cast<CastReturnType>(),
		t.cast<CastReturnType>());
}

template <class Real>
void Mat34<Real>::transform(Vec3<Real>& dest, const Vec3<Real>& src) const
{
	dest.x = src.x * rs.x.x + src.y * rs.y.x + src.z * rs.z.x + t.x;
	dest.y = src.x * rs.x.y + src.y * rs.y.y + src.z * rs.z.y + t.y;
	dest.z = src.x * rs.x.z + src.y * rs.y.z + src.z * rs.z.z + t.z;
}

template <class Real>
void Mat34<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count) const
{
	for (size_t i = 0; i < count; i++)
	{
		transform(*dest++, *src++);
	}
}

template <class Real>
void Mat34<Real>::transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count,
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
void Mat34<Real>::multiply(Mat34& dest, const Mat34& a, const Mat34& b)
{
	assert(&dest != &a && &dest != &b);
	Mat3<Real>::multiply(dest.rs, a.rs, b.rs);
	dest.t = a.t + a.rs * b.t;
}

MATHLIB_NS_END
