#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Vec2<Real> Vec2<Real>::Zero = Vec2<Real>(Real(0), Real(0));

template <class Real>
const Vec2<Real> Vec2<Real>::OneX = Vec2<Real>(Real(1), Real(0));

template <class Real>
const Vec2<Real> Vec2<Real>::OneY = Vec2<Real>(Real(0), Real(1));

// Constructors

template <class Real>
Vec2<Real>::Vec2()
{
}

template <class Real>
Vec2<Real>::Vec2(Real k)
	: x(k), y(k)
{
}

template <class Real>
Vec2<Real>::Vec2(Real px, Real py)
	: x(px), y(py)
{
}

template <class Real>
Vec2<Real>::Vec2(const Vec3<Real>& u, Coord drop)
{
	switch (drop)
	{
	case Coord::X: x = u.y; y = u.z; break;
	case Coord::Y: x = u.x; y = u.z; break;
	case Coord::Z: x = u.x; y = u.y; break;
	default: assert(0);
	}
}

//
// Create from
//

template <class Real>
Vec2<Real> Vec2<Real>::fromAngle(Real angle, Real length)
{
	Vec2 w;
	w.setAngle(angle, length);
	return w;
}

template <class Real>
Vec2<Real> Vec2<Real>::fromClerp(const Vec2<Real>& u, const Vec2<Real>& v, Real ratio)
{
	Vec2 w;
	w.clerp(u, v, ratio);
	return w;
}

template <class Real>
Vec2<Real> Vec2<Real>::fromClerpMaxAngle(const Vec2<Real>& u, const Vec2<Real>& v, Real maxAngle)
{
	Vec2 w;
	w.clerpMaxAngle(u, v, maxAngle);
	return w;
}

//
// Setters
// 

template <class Real>
Vec2<Real>& Vec2<Real>::set(Real x, Real y)
{
	this->x = x;
	this->y = y;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::set(const Vec2& v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::setAngle(Real angle, Real length)
{
	x = length * cos(angle);
	y = length * sin(angle);
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::clerp(const Vec2<Real>& u, const Vec2<Real>& v, Real ratio)
{
	assert(ratio >= Real(0) && ratio <= Real(1));

	if (ratio == Real(0))
		return set(u);

	if (ratio == Real(1))
		return set(v);

	Real angle = ::MATHLIB_NS::clerp(u.angle(), v.angle(), ratio);
	Real l = ::MATHLIB_NS::lerp(u.length(), v.length(), ratio);

	Vec2 w;
	w.setAngle(angle, l);

	return set(w);
}

template <class Real>
Vec2<Real>& Vec2<Real>::clerpMaxAngle(const Vec2<Real>& u, const Vec2<Real>& v, Real maxAngle)
{
	assert(maxAngle >= Real(0));

	if (maxAngle == Real(0))
		return set(u);

	Real ratio;
	Real angle = ::MATHLIB_NS::clerpMaxAngle(u.angle(), v.angle(), maxAngle, ratio);
	Real l = ::MATHLIB_NS::lerp(u.length(), v.length(), ratio);

	Vec2 w;
	w.setAngle(angle, l);

	return set(w);
}


//
// Transformations
// 

template <class Real>
Real Vec2<Real>::normalize(Real k)
{
	Real l = length();
	if (l == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x *= k / l;
		y *= k / l;
	}
	return l;
}

template <class Real>
Vec2<Real>& Vec2<Real>::rotate(Real a)
{
	Real s = sin(a);
	Real c = cos(a);
	Real _x = x * c - y * s;
	Real _y = x * s + y * c;
	x = _x;
	y = _y;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::rotate90()
{
	Real tx = x;
	x = -y;
	y = tx;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::rotate180()
{
	x = -x;
	y = -y;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::rotate270()
{
	Real tx = x;
	x = y;
	y = -tx;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::mirror(Coord c)
{
	switch (c)
	{
	case Coord::X: x = -x; break;
	case Coord::Y: y = -y; break;
	default: /* nop */;
	}
	return *this;
}


//
//  Access operators
//

template <class Real>
Real & Vec2<Real>::operator[](Coord c)
{
	assert(c == Coord::X || c == Coord::Y);
	return c == Coord::X ? x : y;
}

template <class Real>
Real Vec2<Real>::operator()(Coord c) const
{
	assert(c == Coord::X || c == Coord::Y);
	return c == Coord::X ? x : y;
}


//
//  Assignments
//

template <class Real>
Vec2<Real> &Vec2<Real>::operator+=(const Vec2<Real> &u)
{
	x += u.x;
	y += u.y;
	return *this;
}

template <class Real>
Vec2<Real> &Vec2<Real>::operator-=(const Vec2<Real> &u)
{
	x -= u.x;
	y -= u.y;
	return *this;
}

template <class Real>
Vec2<Real> &Vec2<Real>::operator*=(Real k)
{
	x *= k;
	y *= k;
	return *this;
}


//
//                                                  |a  b|   |Xa + Yc|
//  Multiplication by a 2x2 matrix to itself.  [X Y]|    | = |       |
//                                                  |c  d|   |Xb + Yd|
//
template <class Real>
Vec2<Real>& Vec2<Real>::operator*=(const Mat2<Real>& m)
{
	Real tx = x * m.x.x + y * m.x.y;
	Real ty = x * m.y.x + y * m.y.y;
	x = tx;
	y = ty;
	return *this;
}

template <class Real>
Vec2<Real>& Vec2<Real>::operator/=(Real k)
{
	assert(k != Real(0));
	x /= k;
	y /= k;
	return *this;
}


//
//  Arithmetic operators
//

template <class Real>
Vec2<Real> Vec2<Real>::operator+(const Vec2<Real> &u) const
{
	return Vec2(x + u.x, y + u.y);
}

template <class Real>
Vec2<Real> Vec2<Real>::operator-() const
{
	return Vec2(-x, -y);
}

template <class Real>
Vec2<Real> Vec2<Real>::operator-(const Vec2<Real> &u) const
{
	return Vec2(x - u.x, y - u.y);
}

template <class Real>
Real Vec2<Real>::operator*(const Vec2<Real> &u) const
{
	return x * u.x + y * u.y;
}

template <class Real>
Real Vec2<Real>::operator%(const Vec2<Real> &u) const
{
	return x * u.y - y * u.x;
}

template <class Real>
Vec2<Real> Vec2<Real>::operator*(Real k) const
{
	return Vec2(x * k, y * k);
}

//
//       |a  b|   |Xa + Yc|
//  [X Y]|    | = |       |
//       |c  d|   |Xb + Yd|
//
template <class Real>
Vec2<Real> Vec2<Real>::operator*(const Mat2<Real>& m) const
{
	return Vec2(x * m.x.x + y * m.x.y, x * m.y.x + y * m.y.y);
}

template <class Real>
Vec2<Real> Vec2<Real>::operator/(Real k) const
{
	assert(k != 0.0);
	return Vec2(x / k, y / k);
}

//
// Comparison operators
//

template <class Real>
bool Vec2<Real>::operator==(const Vec2<Real> &u) const
{
  return x == u.x && y == u.y;
}

template <class Real>
bool Vec2<Real>::operator!=(const Vec2<Real> &u) const
{
	return x != u.x || y != u.y;
}


//
//  Functions
//

template <class Real>
Real Vec2<Real>::length() const
{
	return sqrt(x * x + y * y);
}

template <class Real>
Real Vec2<Real>::lengthSqr() const
{
	return x * x + y * y;
}

template <class Real>
Vec2<Real> Vec2<Real>::normalized(Real k) const
{
	Real l = length();
	return (l == Real(0)) ? Vec2(0, 0) : Vec2(x * k / l, y * k / l);
}

template <class Real>
Vec2<Real> Vec2<Real>::rotated(Real a) const
{
	Real s = sin(a);
	Real c = cos(a);
	return Vec2(x * c - y * s, x * s + y * c);
}

template <class Real>
Vec2<Real> Vec2<Real>::mirrored(Coord c) const
{
	switch (c)
	{
	case Coord::X: return Vec2(-x, y); break;
	case Coord::Y: return Vec2(x, -y); break;
	default: return Vec2(0, 0);
	}
}

template <class Real>
Real Vec2<Real>::angle() const
{
	return atan2(y, x);
}

template <class Real>
Vec2<Real> Vec2<Real>::rotated90() const
{
	return Vec2(-y, x);
}

template <class Real>
Vec2<Real> Vec2<Real>::rotated180() const
{
	return Vec2(-x, -y);
}

template <class Real>
Vec2<Real> Vec2<Real>::rotated270() const
{
	return Vec2(y, -x);
}

template <class Real>
Coord Vec2<Real>::majorCoord() const
{
	Real fx = (x >= Real(0)) ? x : -x;
	Real fy = (y >= Real(0)) ? y : -y;
	return (fx >= fy) ? Coord::X : Coord::Y;
}

template <class Real>
Coord Vec2<Real>::minorCoord() const
{
	Real fx = (x >= Real(0)) ? x : -x;
	Real fy = (y >= Real(0)) ? y : -y;
	return (fx < fy) ? Coord::X : Coord::Y;
}

template <class Real>
bool Vec2<Real>::isNull() const
{
	return (x == Real(0) && y == Real(0));
}

template <class Real>
const Real* Vec2<Real>::data() const
{
	return &x;
}

template <class Real>
Real* Vec2<Real>::data()
{
	return &x;
}

template <class Real>
template <class CastReturnType>
Vec2<CastReturnType> Vec2<Real>::cast() const
{
	return Vec2<CastReturnType>(
		static_cast<CastReturnType>(x),
		static_cast<CastReturnType>(y)
	);
}

template <class Real>
Vec2<Real> Vec2<Real>::randomUnitVector()
{
	Vec2<Real> n;
	Real l;
	do
	{
		n.x = rand(Real(1));
		n.y = rand(Real(1));

		l = n.normalize();

	} while (l == Real(0));
	return n;
}


//
// External functions
//

template <class Real>
int intersection(const Vec2<Real> &from, const Vec2<Real> &to,
	const Vec2<Real> &a, const Vec2<Real> &b,
	Real &ftp, Real &abp)
{
	ftp = abp = Real(0);

	Vec2<Real> ft = to - from;
	Vec2<Real> ab = b - a;
	Real det = ft.x * ab.y - ft.y * ab.x;

	if (det == Real(0))
		return 0;

	Vec2<Real> fa = a - from;
	Real num_lambda = fa.x * ab.y - fa.y * ab.x;
	Real num_gamma  = fa.x * ft.y - fa.y * ft.x;

	ftp = num_lambda / det;
	abp = num_gamma / det;

	return 1;
}

MATHLIB_NS_END
