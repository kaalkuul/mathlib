#pragma once

MATHLIB_NS_BEGIN

template <class Real>
const Vec3<Real> Vec3<Real>::Zero = Vec3<Real>(Real(0));

template <class Real>
const Vec3<Real> Vec3<Real>::OneX = Vec3<Real>(Real(1), Real(0), Real(0));

template <class Real>
const Vec3<Real> Vec3<Real>::OneY = Vec3<Real>(Real(0), Real(1), Real(0));

template <class Real>
const Vec3<Real> Vec3<Real>::OneZ = Vec3<Real>(Real(0), Real(0), Real(1));

//
// Constructors
//

template <class Real>
Vec3<Real>::Vec3()
{
}

template <class Real>
Vec3<Real>::Vec3(Real k)
	: x(k), y(k), z(k)
{
}

template <class Real>
Vec3<Real>::Vec3(Real px, Real py, Real pz)
	: x(px), y(py), z(pz)
{
}

template <class Real>
Vec3<Real>::Vec3(const Vec2<Real> &u, Coord c)
{
	switch (c)
	{
	case Coord::X: x = Real(0);	y = u.x;	z = u.y;	break;
	case Coord::Y: x = u.x;		y = Real(0);	z = u.y;	break;
	case Coord::Z: x = u.x;		y = u.y;	z = Real(0);	break;
	default: assert(0);
	}
}

//
// Create from
//

template <class Real>
Vec3<Real> Vec3<Real>::fromSlerp(const Vec3<Real>& u, const Vec3<Real>& v, Real ratio)
{
	Vec3 w;
	w.slerp(u, v, ratio);
	return w;
}

template <class Real>
Vec3<Real> Vec3<Real>::fromSlerpMaxAngle(const Vec3<Real>& u, const Vec3<Real>& v, Real maxAngle)
{
	Vec3 w;
	w.slerpMaxAngle(u, v, maxAngle);
	return w;
}

//
// Setters
// 

template <class Real>
Vec3<Real>& Vec3<Real>::set(Real x, Real y, Real z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

template <class Real>
Vec3<Real>& Vec3<Real>::set(const Vec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

template <class Real>
Vec3<Real>& Vec3<Real>::slerp(const Vec3<Real>& u, const Vec3<Real>& v, Real ratio)
{
	if (ratio == Real(0))
		return set(u);

	if (ratio == Real(1))
		return set(v);

	Real lengthU = u.length();
	Real lengthV = v.length();

	if (lengthU == Real(0) || lengthV == Real(0))
	{
		x = u.x + (v.x - u.x) * ratio;
		y = u.y + (v.y - u.y) * ratio;
		z = u.z + (v.z - u.z) * ratio;
		return *this;
	}
	else
	{
		Vec3<Real> n = (u % v) / (lengthU * lengthV);
		Real sinAngle = n * n.normalized();

		if (abs(sinAngle) < 0.05f)
		{
			x = u.x + (v.x - u.x) * ratio;
			y = u.y + (v.y - u.y) * ratio;
			z = u.z + (v.z - u.z) * ratio;
			return *this;
		}
		else
		{
			Real angle = asin(sinAngle);

			Quat<Real> q;
			q.set(n, angle * ratio);

			Vec3<Real> w = q.rotated(u);
			w.normalize(lengthU + (lengthV - lengthU) * ratio);

			return set(w);
		}
	}
}

template <class Real>
Vec3<Real>& Vec3<Real>::slerpMaxAngle(const Vec3<Real>& u, const Vec3<Real>& v, Real maxAngle)
{
	assert(maxAngle >= Real(0));

	if (maxAngle == Real(0))
		return set(u);

	Real lengthU = u.length();
	Real lengthV = v.length();

	if (lengthU == Real(0))
	{
		return set(v);
	}
	else if (lengthV == Real(0))
	{
		return set(u);
	}
	else
	{
		Vec3<Real> n = (u % v) / (lengthU * lengthV);
		Real sinAngle = n * n.normalized();

		Real angle = asin(sinAngle);

		if (angle == Real(0))
			return set(v);

		Real actualAngle = (angle >= Real(0))
			? ((angle > maxAngle) ? maxAngle : angle)
			: ((angle < -maxAngle) ? -maxAngle : angle);

		Real ratio = actualAngle / angle;

		Quat<Real> q;
		q.set(n, actualAngle);

		Vec3 w = q.rotated(u);

		w.normalize(lengthU + (lengthV - lengthU) * ratio);

		return set(w);
	}
}


//
// Transformations
//

// This function normalizes the vector
template <class Real>
Real Vec3<Real>::normalize(Real k)
{
	Real l = length();
	if (l == Real(0))
	{
		x = y = z = Real(0);
	}
	else
	{
		Real coeff = k / l;
		x *= coeff;
		y *= coeff;
		z *= coeff;
	}
	return l;
}

template <class Real>
Vec3<Real>& Vec3<Real>::rotate(Coord axis, Real angle)
{
	Real s = sin(angle);
	Real c = cos(angle);
	Real _x, _y, _z;
	switch (axis)
	{
	case Coord::X:
		_x = x;
		_y = y*c - z*s;
		_z = y*s + z*c;
		break;
	case Coord::Y:
		_x = x*c + z*s;
		_y = y;
		_z = -x*s + z*c;
		break;
	case Coord::Z:
		_x = x*c - y*s;
		_y = x*s + y*c;
		_z = z;
		break;
	default:
		_x = _y = _z = Real(0);
		break;
	}
	x = _x;
	y = _y;
	z = _z;
	return *this;
}

template <class Real>
Vec3<Real>& Vec3<Real>::mirror(Coord plane)
{
	switch (plane)
	{
	case Coord::X: x = -x; break;
	case Coord::Y: y = -y; break;
	case Coord::Z: z = -z; break;
    default: /* nop */;
    }
	return *this;
}

//
// Access operators
//

template <class Real>
Real & Vec3<Real>::operator[](Coord c)
{
	switch (c)
	{
	case Coord::X: return x;
	case Coord::Y: return y;
	case Coord::Z: return z;
	default: assert(0); return x;
	}
}

template <class Real>
Real Vec3<Real>::operator()(Coord c) const
{
	switch (c)
	{
	case Coord::X: return x;
	case Coord::Y: return y;
	case Coord::Z: return z;
	default: assert(0); return 0;
	}
}


//
//  Assignments
//

template <class Real>
Vec3<Real> & Vec3<Real>::operator+= (const Vec3 &u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

template <class Real>
Vec3<Real> & Vec3<Real>::operator-= (const Vec3 &u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

template <class Real>
Vec3<Real> & Vec3<Real>::operator*= (Real k)
{
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

//
//                                             |a b c|   |_xa + _yd + _zg|t
//  Multiplication by a 3x3 matrix.  [_x _y _z]|d e f| = |_xb + _ye + _zh|
//                                             |g h i|   |_xg + _yh + _zi|
//
template <class Real>
Vec3<Real> & Vec3<Real>::operator*=(const Mat3<Real> &m)
{
	Real tx = x * m.x.x + y * m.x.y + z * m.x.z;
	Real ty = x * m.y.x + y * m.y.y + z * m.y.z;
	Real tz = x * m.z.x + y * m.z.y + z * m.z.z;
	x = tx;
	y = ty;
	z = tz;
	return *this;
}

template <class Real>
Vec3<Real> & Vec3<Real>::operator/= (Real k)
{
	assert(k != Real(0));
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

template <class Real>
Vec3<Real> & Vec3<Real>::operator%= (const Vec3 &u)
{
	Real _x, _y, _z;
	_x = y * u.z - z * u.y;
	_y = z * u.x - x * u.z;
	_z = x * u.y - y * u.x;
	x = _x;
	y = _y;
	z = _z;
	return *this;
}

template <class Real>
Vec3<Real> & Vec3<Real>::operator%= (Coord v)
{
	Real _x, _y, _z;
	switch (v)
	{
	case Coord::X:		// 1 0 0
		_x = Real(0);
		_y = z;
		_z = -y;
		break;
	case Coord::Y:		// 0 1 0
		_x = -z;
		_y = Real(0);
		_z = x;
		break;
	case Coord::Z:		// 0 0 1
		_x = y;
		_y = -x;
		_z = Real(0);
		break;
	case Coord::NX:	// -1 0 0
		_x = Real(0);
		_y = -z;
		_z = y;
		break;
	case Coord::NY:	// 0 -1 0
		_x = z;
		_y = Real(0);
		_z = -x;
		break;
	case Coord::NZ:	// 0 0 -1
		_x = -y;
		_y = x;
		_z = Real(0);
		break;
	default:
		_x = Real(0);
		_y = Real(0);
		_z = Real(0);
		assert(0);
	}
	x = _x;
	y = _y;
	z = _z;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
Vec3<Real> Vec3<Real>::operator+ (const Vec3 &u) const
{
	return Vec3(x + u.x, y + u.y, z + u.z);
}

template <class Real>
Vec3<Real> Vec3<Real>::operator- () const
{
	return Vec3(-x, -y, -z);
}

template <class Real>
Vec3<Real> Vec3<Real>::operator- (const Vec3 &u) const
{
	return Vec3(x - u.x, y - u.y, z - u.z);
}

template <class Real>
Real Vec3<Real>::operator* (const Vec3 &u) const
{
	return x * u.x + y * u.y + z * u.z;
}

template <class Real>
Vec3<Real> Vec3<Real>::operator% (const Vec3 &u) const
{
	return Vec3(y * u.z - z * u.y,
		z * u.x - x * u.z,
		x * u.y - y * u.x);
}

template <class Real>
Vec3<Real> Vec3<Real>::operator% (Coord v) const
{
	Vec3 r;
	switch (v)
	{
	case Coord::X:		// 1 0 0
		r.x = Real(0);
		r.y = z;
		r.z = -y;
		break;
	case Coord::Y:		// 0 1 0
		r.x = -z;
		r.y = Real(0);
		r.z = x;
		break;
	case Coord::Z:		// 0 0 1
		r.x = y;
		r.y = -x;
		r.z = Real(0);
		break;
	case Coord::NX:	// -1 0 0
		r.x = Real(0);
		r.y = -z;
		r.z = y;
		break;
	case Coord::NY:	// 0 -1 0
		r.x = z;
		r.y = Real(0);
		r.z = -x;
		break;
	case Coord::NZ:	// 0 0 -1
		r.x = -y;
		r.y = x;
		r.z = Real(0);
		break;
	default: assert(0);
	}
	return r;
}

template <class Real>
Vec3<Real> Vec3<Real>::operator* (Real k) const
{
	return Vec3(x * k, y * k, z * k);
}

//
//            |a b c|   |_xa + _yd + _zg|t
//  [_x _y _z]|d e f| = |_xd + _ye + _zh|
//            |g h i|   |_xg + _yh + _zi|
//
template <class Real>
Vec3<Real> Vec3<Real>::operator*(const Mat3<Real> &m) const
{
	return Vec3<Real>(
		x * m.x.x + y * m.x.y + z * m.x.z,
		x * m.y.x + y * m.y.y + z * m.y.z,
		x * m.z.x + y * m.z.y + z * m.z.z
	);
}

template <class Real>
Vec3<Real> Vec3<Real>::operator/ (Real k) const
{
	assert(k != Real(0));
	return Vec3(x / k, y / k, z / k);
}


//
// Comparison operators
//

template <class Real>
bool Vec3<Real>::operator== (const Vec3 &u) const
{
	return x == u.x && y == u.y && z == u.z;
}

template <class Real>
bool Vec3<Real>::operator!= (const Vec3 &u) const
{
	return x != u.x || y != u.y || z != u.z;
}


//
//  Functions
//

template <class Real>
Real Vec3<Real>::length() const
{
	return sqrt(x * x + y * y + z * z);
}

template <class Real>
Real Vec3<Real>::lengthSqr() const
{
	return x * x + y * y + z * z;
}

template <class Real>
Vec3<Real> Vec3<Real>::normalized(Real k) const
{
	Real l = length();
	if (l == Real(0))
	{
		return Vec3<Real>::Zero;
	}
	else
	{
		Real coeff = k / l;
		return Vec3<Real>(x * coeff, y * coeff, z * coeff);
	}
}

template <class Real>
Vec3<Real> Vec3<Real>::rotated(Coord axis, Real angle) const
{
	Real s = sin(angle);
	Real c = cos(angle);
	switch (axis)
	{
	case Coord::X: return Vec3<Real>(x, y*c - z*s, y*s + z*c);
	case Coord::Y: return Vec3<Real>(x*c + z*s, y, -x*s + z*c);
	case Coord::Z: return Vec3<Real>(x*c - y*s, x*s + y*c, z);
	default: return Vec3::Zero;
	}
}

template <class Real>
Vec3<Real> Vec3<Real>::mirrored(Coord c) const
{
	switch (c)
	{
	case Coord::X: return Vec3<Real>(-x, y, z); break;
	case Coord::Y: return Vec3<Real>(x, -y, z); break;
	case Coord::Z: return Vec3<Real>(x, y, -z); break;
	default: return Vec3<Real>(0.0f, Real(0), Real(0));
	}
}

template <class Real>
Coord Vec3<Real>::majorCoord() const
{
	Real fx = (x >= Real(0)) ? x : -x;
	Real fy = (y >= Real(0)) ? y : -y;
	Real fz = (z >= Real(0)) ? z : -z;
	return (fx >= fy)
		?	((fx >= fz) ? Coord::X : Coord::Z)
		:	((fy >= fz) ? Coord::Y : Coord::Z);
}

template <class Real>
Coord Vec3<Real>::minorCoord() const
{
	Real fx = (x >= Real(0)) ? x : -x;
	Real fy = (y >= Real(0)) ? y : -y;
	Real fz = (z >= Real(0)) ? z : -z;
	return (fx < fy)
		?	((fx < fz) ? Coord::X : Coord::Z)
		:	((fy < fz) ? Coord::Y : Coord::Z);
}

template <class Real>
bool Vec3<Real>::isNull() const
{
	return (x == Real(0) && y == Real(0) && z == Real(0));
}

template <class Real>
template <class CastReturnType>
Vec3<CastReturnType> Vec3<Real>::cast() const
{
	return Vec3<CastReturnType>(
		static_cast<CastReturnType>(x),
		static_cast<CastReturnType>(y), 
		static_cast<CastReturnType>(z)
	);
}

template <class Real>
Vec3<Real> Vec3<Real>::randomUnitVector()
{
	Vec3<Real> n;
	Real l;
	do
	{
		n.x = rand(Real(1));
		n.y = rand(Real(1));
		n.z = rand(Real(1));

		l = n.normalize();

	} while (l == Real(0));
	return n;
}

MATHLIB_NS_END
