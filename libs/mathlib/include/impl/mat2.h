#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Mat2<Real> Mat2<Real>::Zero = Mat2<Real>(Real(0));

template <class Real>
const Mat2<Real> Mat2<Real>::One = Mat2<Real>(Real(1));

template <class Real>
const typename Mat2<Real>::Tolerance Mat2<Real>::DefaultTolerance = { Real(0.001), Real(0.001), Real(0.001) };

//
//  Constructors
//

template <class Real>
Mat2<Real>::Mat2()
:	flags(Flags::Uninitialized)
{
}

template <class Real>
Mat2<Real>::Mat2(Real k)
{
	x.x = k;		y.x = Real(0);
	x.y = Real(0);	y.y = k;
	flags = Flags::Orthogonal;
	if (k == Real(1))
	{
		flags |= Flags::Normal | Flags::Identity;
	}
}

template <class Real>
Mat2<Real>::Mat2(const Vec2<Real> &x, const Vec2<Real> &y)
{
	set(x, y);
}

//
// Create from
//

template <class Real>
Mat2<Real> Mat2<Real>::from(const Vec2<Real>& x, const Vec2<Real>& y)
{
	Mat2<Real> r;
	r.set(x, y);
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::from(Real angle)
{
	Mat2<Real> r;
	r.set(angle);
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::fromSlerp(const Mat2& a, const Mat2& b, Real weight)
{
	Mat2<Real> r;
	r.slerp(a, b, weight);
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::fromSlerpMaxAngle(const Mat2& a, const Mat2& b, Real maxAngle)
{
	Mat2<Real> r;
	r.slerpMaxAngle(a, b, maxAngle);
	return r;
}


//
//  Assignments
//

template <class Real>
Mat2<Real>& Mat2<Real>::operator*=(Real k)
{
	if (k == Real(1))
		return *this;
	x *= k;
	y *= k;
	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::operator*=(const Mat2 &m)
{
	if (m.isIdentity())
		return *this;
	if (isIdentity())
		return set(m);
	Real ta = x.x, tb = y.x, td = x.y, te = y.y;
	x.x = ta * m.x.x + tb * m.x.y;
	y.x = ta * m.y.x + tb * m.y.y;
	x.y = td * m.x.x + te * m.x.y;
	y.y = td * m.y.x + te * m.y.y;
	flags &= m.flags;
	return *this;
}

template <class Real>
Mat2<Real> &Mat2<Real>::operator/=(Real k)
{
	assert(k != Real(0));
	if (k == Real(1))
		return *this;
	x /= k;
	y /= k;
	return optimize();
}


//
//  Arithmetic operators
//

template <class Real>
Mat2<Real> Mat2<Real>::operator-() const
{
	return Mat2(-x, -y);
}

template <class Real>
Mat2<Real> Mat2<Real>::operator*(const Mat2 &m) const
{
	Mat2 r;
	multiply(r, *this, m);
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::operator*(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	return Mat2(x * k, y * k);
}

template <class Real>
Vec2<Real> Mat2<Real>::operator*(const Vec2<Real> &u) const
{
	Vec2<Real> r;
	transform(r, u);
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::operator/(Real k) const
{
	if (k == Real(0))
		return Zero;
	if (k == Real(1))
		return *this;
	return Mat2(x / k, y / k);
}

//
// Comparison operators
//

template <class Real>
bool Mat2<Real>::operator==(const Mat2 &m) const
{
	return x == m.x && y == m.y;
}

template <class Real>
bool Mat2<Real>::operator!=(const Mat2 &m) const
{
	return x != m.x || y != m.y;
}

// Transformations

template <class Real>
Mat2<Real>& Mat2<Real>::setIdentity()
{
	x = Vec2<Real>::OneX;
	y = Vec2<Real>::OneY;
	flags = Flags::Mask | Flags::Identity;
	return *this;
}

template <class Real>
Mat2<Real>& Mat2<Real>::set(const Mat2<Real>& m)
{
	x = m.x;
	y = m.y;
	flags = m.flags;
	return *this;
}

template <class Real>
Mat2<Real>& Mat2<Real>::set(const Vec2<Real>& x, const Vec2<Real>& y)
{
	this->x = x;
	this->y = y;
	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::set(Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);

	x.x = c;
	x.y = s;
	y.x = -s;
	y.y = c;

	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::slerp(const Mat2& a, const Mat2& b, Real weight)
{
	Real angle = clerp(a.angle(), b.angle(), weight);
	return set(angle);
}

template <class Real>
Mat2<Real>& Mat2<Real>::slerpMaxAngle(const Mat2& a, const Mat2& b, Real maxAngle)
{
	Real angle = clerpMaxAngle(a.angle(), b.angle(), maxAngle);
	return set(angle);
}

template <class Real>
Mat2<Real>& Mat2<Real>::scale(const Vec2<Real>& coefficients)
{
	x *= coefficients.x;
	y *= coefficients.y;
	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::transpose()
{
	Real t = x.y; x.y = y.x; y.x = t;
	// flags unchanged by transposition
	return *this;
}

template <class Real>
Mat2<Real>& Mat2<Real>::rotate(Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	Real t;
	t = x.x;
	x.x = t * c - x.y * s;
	x.y = t * s + x.y * c;

	t = y.x;
	y.x = t * c - y.y * s;
	y.y = t * s + y.y * c;
	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::rotatePre(Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	Real t;
	t = x.x;
	x.x = t * c + y.x * s;
	y.x = -t * s + y.x * c;

	t = x.y;
	x.y = t * c + y.y * s;
	y.y = -t * s + y.y * c;
	return optimize();
}

template <class Real>
Mat2<Real>& Mat2<Real>::orthonormalise()
{
	Real a = angle();
	return set(a);
}

template <class Real>
Mat2<Real>& Mat2<Real>::optimize(const Tolerance *tolerance)
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


//
//  Functions
//

template <class Real>
Mat2<Real> Mat2<Real>::scaled(const Vec2<Real>& coefficients) const
{
	Mat2 r;
	r.x = x * coefficients.x;
	r.y = y * coefficients.y;
	r.optimize();
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::transposed() const
{
	Mat2 r;
	r.x.x = x.x;
	r.x.y = y.x;
	r.y.x = x.y;
	r.y.y = y.y;
	r.flags = flags;
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::cofactors() const
{
	Mat2 r;
	r.x.x = y.y;
	r.x.y = -y.x;
	r.y.x = -x.y;
	r.y.y = x.x;
	r.optimize();
	return r;
}

template <class Real>
Mat2<Real> Mat2<Real>::adjoint() const
{
	Mat2 r;
	r.x.x = y.y;
	r.x.y = -x.y;
	r.y.x = -y.x;
	r.y.y = x.x;
	r.optimize();
	return r;
}

template <class Real>
Real Mat2<Real>::trace() const
{
	return x.x + y.y;
}

template <class Real>
Real Mat2<Real>::determinant() const
{
	return x.x * y.y - x.y * y.x;
}

template <class Real>
Mat2<Real> Mat2<Real>::inversed() const
{
	Real det = determinant();
	return (det == Real(0)) ? Zero : adjoint() / det;
}

template <class Real>
Real Mat2<Real>::angle() const
{
	return ::atan2(x.y, x.x);
}

template <class Real>
Real Mat2<Real>::normalError() const
{
	Real cx = (x * x) - Real(1);
	Real cy = (y * y) - Real(1);
	return cx * cx + cy * cy;
}

template <class Real>
Real Mat2<Real>::orthogonalError() const
{
	Real xy = x * y;
	return xy * xy;
}

template <class Real>
Real Mat2<Real>::identityError() const
{
	Vec2<Real> rx = { x.x - Real(1), x.y };
	Vec2<Real> ry = { y.x, y.y - Real(1) };
	return rx.lengthSqr() + ry.lengthSqr();
}

template <class Real>
bool Mat2<Real>::isNormal() const
{
	return (flags & Flags::Normal);
}

template <class Real>
bool Mat2<Real>::isOrthogonal() const
{
	return (flags & Flags::Orthogonal);
}

template <class Real>
bool Mat2<Real>::isOrthonormal() const
{
	return (flags & Flags::Mask) == Flags::Mask;
}

template <class Real>
bool Mat2<Real>::isIdentity() const
{
	return (flags & Flags::Identity);
}

template <class Real>
bool Mat2<Real>::isInitialized() const
{
	return !(flags & Flags::Uninitialized);
}

template <class Real>
template <class CastReturnType>
Mat2<CastReturnType> Mat2<Real>::cast() const
{
	return Mat2<CastReturnType>::from(x.cast<CastReturnType>(), y.cast<CastReturnType>());
}

template <class Real>
void Mat2<Real>::transform(Vec2<Real>& dest, const Vec2<Real>& src) const
{
	dest.x = src.x * x.x + src.y * y.x;
	dest.y = src.x * x.y + src.y * y.y;
}

template <class Real>
void Mat2<Real>::transform(Vec2<Real>* dest, const Vec2<Real>* src, size_t count) const
{
	for (size_t i = 0; i < count; i++)
	{
		transform(*dest++, *src++);
	}
}

template <class Real>
void Mat2<Real>::transform(Vec2<Real>* dest, const Vec2<Real>* src, size_t count,
	size_t destStride, size_t srcStride) const
{
	const char* d = (const char*)dest;
	const char* s = (const char*)src;
	for (size_t i = 0; i < count; i++)
	{
		transform(*((Vec2<Real>*)d), *((const Vec2<Real>*)s));
		d += destStride;
		s += srcStride;
	}
}

template <class Real>
void Mat2<Real>::multiply(Mat2& dest, const Mat2& a, const Mat2& b)
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
		dest.x.x = a.x.x * b.x.x + a.y.x * b.x.y;
		dest.y.x = a.x.x * b.y.x + a.y.x * b.y.y;
		dest.x.y = a.x.y * b.x.x + a.y.y * b.x.y;
		dest.y.y = a.x.y * b.y.x + a.y.y * b.y.y;
		dest.flags = a.flags & b.flags;
	}
}

MATHLIB_NS_END
