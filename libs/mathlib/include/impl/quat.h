#pragma once

MATHLIB_NS_BEGIN

const double DELTA = 1e-6f;

template <class Real>
const Quat<Real> Quat<Real>::One = Quat<Real>(0, 0, 0, 1, false);

template <class Real>
Quat<Real>::Quat()
{
}

template <class Real>
Quat<Real>::Quat(Real px, Real py, Real pz, Real pw, bool autoNormalize)
:	x(px), y(py), z(pz), w(pw)
{
	if (autoNormalize)
	{
		normalize();
	}
}

template <class Real>
Quat<Real>& Quat<Real>::setIdentity()
{
	x = Real(0);
	y = Real(0);
	z = Real(0);
	w = Real(1);
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Quat& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Mat3<Real>& m)
{
	Real tr = m.trace();
	if (tr > Real(0))
	{
		Real s = sqrt(Real(1) + tr) * Real(2);
		w = s / Real(4);
		x = (m.y.z - m.z.y) / s;
		y = (m.z.x - m.x.z) / s;
		z = (m.x.y - m.y.x) / s;
	}
	else if (m.x.x > m.y.y && m.x.x > m.z.z)
	{
		Real s = sqrt(Real(1) + m.x.x - m.y.y - m.z.z) * Real(2);
		w = (m.y.z - m.z.y) / s;
		x = s / Real(4);
		y = (m.y.x + m.x.y) / s;
		z = (m.z.x + m.x.z) / s;
	}
	else if (m.y.y > m.z.z)
	{
		Real s = sqrt(Real(1) + m.y.y - m.x.x - m.z.z) * Real(2);
		w = (m.z.x - m.x.z) / s;
		x = (m.y.x + m.x.y) / s;
		y = s / Real(4);
		z = (m.z.y + m.y.z) / s;
	}
	else
	{
		Real s = sqrt(Real(1) + m.z.z - m.x.x - m.y.y) * Real(2);
		w = (m.x.y - m.y.x) / s;
		x = (m.z.x + m.x.z) / s;
		y = (m.z.y + m.y.z) / s;
		z = s / Real(4);
	}
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Mat4<Real>& m)
{
	Real tr = m.x.x + m.y.y + m.z.z;
	if (tr > Real(0))
	{
		Real s = sqrt(Real(1) + tr) * Real(2);
		w = s / Real(4);
		x = (m.y.z - m.z.y) / s;
		y = (m.z.x - m.x.z) / s;
		z = (m.x.y - m.y.x) / s;
	}
	else if (m.x.x > m.y.y && m.x.x > m.z.z)
	{
		Real s = sqrt(Real(1) + m.x.x - m.y.y - m.z.z) * Real(2);
		w = (m.y.z - m.z.y) / s;
		x = s / Real(4);
		y = (m.y.x + m.x.y) / s;
		z = (m.z.x + m.x.z) / s;
	}
	else if (m.y.y > m.z.z)
	{
		Real s = sqrt(Real(1) + m.y.y - m.x.x - m.z.z) * Real(2);
		w = (m.z.x - m.x.z) / s;
		x = (m.y.x + m.x.y) / s;
		y = s / Real(4);
		z = (m.z.y + m.y.z) / s;
	}
	else
	{
		Real s = sqrt(Real(1) + m.z.z - m.x.x - m.y.y) * Real(2);
		w = (m.x.y - m.y.x) / s;
		x = (m.z.x + m.x.z) / s;
		y = (m.z.y + m.y.z) / s;
		z = s / Real(4);
	}
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Vec3<Real> &axis, Real angle)
{
	Real vn = axis.length();
	if (vn == Real(0))
	{
		return setIdentity();
	}
	angle *= Real(0.5);
	Real s = sin(angle) / vn;
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	w = cos(angle);
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Vec3<Real>& from2, const Vec3<Real>& to2)
{
	Vec3<Real> from = from2.normalized();
	Vec3<Real> to = to2.normalized();

	Real cost = from * to;
	if (cost > Real(0.99999))
	{
		x = Real(0);
		y = Real(0);
		z = Real(0);
		w = Real(1);
		return *this;
	}
	if (cost < Real(-0.99999))
	{
		x = Real(0);
		y = Real(0);
		z = Real(0);
		w = Real(-1);
		return *this;
	}

	Vec3<Real> t = (from % to).normalized();

	Real s = sqrt(Real(0.5) * (Real(1) - cost));
	x = t.x * s;
	y = t.y * s;
	z = t.z * s;
	w = sqrt(Real(0.5) * (Real(1) + cost));
	return *this;
}

template <class Real>
Quat<Real>& Quat<Real>::lerp(const Quat& from, const Quat& to, Real weight)
{
	assert((weight >= Real(0)) && (weight <= Real(1)));
	x = from.x + (to.x - from.x) * weight;
	y = from.y + (to.y - from.y) * weight;
	z = from.z + (to.z - from.z) * weight;
	w = from.w + (to.w - from.w) * weight;
	return normalize();
}

template <class Real>
Quat<Real>& Quat<Real>::slerp(const Quat& from, const Quat& to, Real weight)
{
	assert(weight >= Real(0) && weight <= Real(1));

	Real dot = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;

	Quat q3;
	if (dot < Real(0))
	{
		dot = -dot;
		q3.x = -to.x;
		q3.y = -to.y;
		q3.z = -to.z;
		q3.w = -to.w;
	}
	else
	{
		q3 = to;
	}

	if (dot < Real(0.95))
	{
		Real angle = acos(dot);
		Real sina = sin(angle);
		Real sinat = sin(angle * weight);
		Real sinaomt = sin(angle * (Real(1) - weight));
		Real recipsina = Real(1) / sina;
		x = (from.x * sinaomt + q3.x * sinat) * recipsina;
		y = (from.y * sinaomt + q3.y * sinat) * recipsina;
		z = (from.z * sinaomt + q3.z * sinat) * recipsina;
		w = (from.w * sinaomt + q3.w * sinat) * recipsina;
		return *this;
	}
	else
	{
		return lerp(from, q3, weight);
	}
}

template <class Real>
Quat<Real>& Quat<Real>::slerpMaxAngle(const Quat& from, const Quat& to, Real maxAngle)
{
	assert(maxAngle >= Real(0));

	Quat fromto = from.inverse() * to;

	Vec3<Real> axis;
	Real angle;
	fromto.toAxisAngle(axis, angle);

	return set(axis, min(angle, maxAngle));
}

template <class Real>
Quat<Real>& Quat<Real>::slerpNoInvert(const Quat& from, const Quat& to, Real weight)
{
	assert(weight >= Real(0) && weight <= Real(1));

	Real dot = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;

	if (dot < 0.95f)
	{
		Real angle = (Real)(acos(dot));
		Real sina = sin(angle);
		Real sinat = sin(angle * weight);
		Real sinaomt = sin(angle * (Real(1) - weight));
		Real recipsina = Real(1) / sina;

		x = (from.x * sinaomt + to.x * sinat) * recipsina;
		y = (from.y * sinaomt + to.y * sinat) * recipsina;
		z = (from.z * sinaomt + to.z * sinat) * recipsina;
		w = (from.w * sinaomt + to.w * sinat) * recipsina;

		return *this;
	}
	else
	{
		return lerp(from, to, weight);
	}
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Quat& from, const Quat& to, const Quat& a, const Quat& b, Real weight)
{
	assert(weight >= Real(0) && weight <= Real(1));
	Quat tmp1, tmp2;
	tmp1.slerpNoInvert(from, to, weight);
	tmp2.slerpNoInvert(a, b, weight);
	return slerpNoInvert(tmp1, tmp2, Real(2) * weight * (Real(1) - weight));
}

template <class Real>
Quat<Real>& Quat<Real>::set(const Quat& from, const Quat& via, const Quat& to)
{
	Quat qni;
	qni.x = -via.x;
	qni.y = -via.y;
	qni.z = -via.z;
	qni.w = via.w;

	Quat tmp = log(qni * from) + log(qni * to);
	tmp.x *= -0.25f;
	tmp.y *= -0.25f;
	tmp.z *= -0.25f;
	tmp.w *= -0.25f;

	return set(via * exp(tmp));
}


//
// Transformations
//

template <class Real>
Quat<Real>& Quat<Real>::normalize()
{
	Real n = sqrt(x*x + y*y + z*z + w*w);
	if (n == Real(0))
	{
		return setIdentity();
	}
	Real oneover = Real(1) / n;
	x *= oneover;
	y *= oneover;
	z *= oneover;
	w *= oneover;
	return *this;
}


//
// Create from
//

template <class Real>
Quat<Real> Quat<Real>::from(const Quat& q)
{
	Quat r;
	r.set(q);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Mat3<Real>& m)
{
	Quat r;
	r.set(m);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Mat4<Real>& m)
{
	Quat r;
	r.set(m);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Vec3<Real>& axis, Real angle)
{
	Quat r;
	r.set(axis, angle);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Vec3<Real>& from, const Vec3<Real>& to)
{
	Quat r;
	r.set(from, to);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::fromLerp(const Quat& from, const Quat& to, Real weight)
{
	Quat r;
	r.lerp(from, to, weight);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::fromSlerp(const Quat& from, const Quat& to, Real weight)
{
	Quat r;
	r.slerp(from, to, weight);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::fromSlerpMaxAngle(const Quat& from, const Quat& to, Real maxAngle)
{
	Quat r;
	r.slerpMaxAngle(from, to, maxAngle);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::fromSlerpNoInvert(const Quat& from, const Quat& to, Real weight)
{
	Quat r;
	r.slerpNoInvert(from, to, weight);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Quat& from, const Quat& to, const Quat& a, const Quat& b, Real weight)
{
	Quat r;
	r.set(from, to, a, b, weight);
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::from(const Quat& from, const Quat& via, const Quat& to)
{
	Quat r;
	r.set(from, via, to);
	return r;
}


//
// Assignments
//

template <class Real>
Quat<Real>& Quat<Real>::operator = (const Quat &q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}


//
// Arithmetic operators
//

template <class Real>
Quat<Real> Quat<Real>::operator * (const Quat &q) const
{
	Quat r;
	r.x = w * q.x + x * q.w + y * q.z - z * q.y;
	r.y = w * q.y + y * q.w + z * q.x - x * q.z;
	r.z = w * q.z + z * q.w + x * q.y - y * q.x;
	r.w = w * q.w - x * q.x - y * q.y - z * q.z;
	return r;
}

template <class Real>
Vec3<Real> Quat<Real>::operator*(const Vec3<Real> &v) const
{
	Vec3<Real> r;
	r.x = w * v.x + y * v.z - z * v.y;
	r.y = w * v.y + z * v.x - x * v.z;
	r.z = w * v.z + x * v.y - y * v.x;
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::operator - () const
{
	Quat r;
	r.x = -x;
	r.y = -y;
	r.z = -z;
	r.w = -w;
	return r;
}

template <class Real>
Quat<Real> Quat<Real>::operator / (const Quat &q) const
{
	//invert q; r = q^(-1), assumes q is normalized
	Quat r = Quat(-q.x, -q.y, -q.z, q.w);
	Real s = Real(1) / (r.w * r.w - r.x * r.x - r.y * r.y - r.z * r.z);
	Quat p = *this * q;
	p.x *= s;
	p.y *= s;
	p.z *= s;
	p.w *= s;
	return p;
}


//
// Comparison operators
//

template <class Real>
bool Quat<Real>::operator == (const Quat& q) const
{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

template <class Real>
bool Quat<Real>::operator != (const Quat& q) const
{
	return x != q.x || y != q.y || z != q.z || w != q.w;
}


//
// Functions
//

template <class Real>
Vec3<Real> Quat<Real>::rotated(Coord c) const
{
	Vec3<Real> v;

	switch (c)
	{
	case Coord::X:
		{
			Real qyy = Real(2) * y * y;
			Real qzz = Real(2) * z * z;
			Real qxy = Real(2) * x * y;
			Real qzw = Real(2) * z * w;
			Real qxz = Real(2) * x * z;
			Real qyw = Real(2) * y * w;

			v.x = Real(1) - qyy - qzz;
			v.y = qxy + qzw;
			v.z = qxz - qyw;
		}
		break;
	case Coord::Y:
		{
			Real qxx = Real(2) * x * x;
			Real qzz = Real(2) * z * z;

			Real qxy = Real(2) * x * y;
			Real qxw = Real(2) * x * w;
			Real qyz = Real(2) * y * z;
			Real qzw = Real(2) * z * w;

			v.x = qxy - qzw;
			v.y = Real(1) - qxx - qzz;
			v.z = qyz + qxw;
		}
		break;
	case Coord::Z:
		{
			Real qxx = Real(2) * x * x;
			Real qyy = Real(2) * y * y;

			Real qxz = Real(2) * x * z;
			Real qxw = Real(2) * x * w;
			Real qyz = Real(2) * y * z;
			Real qyw = Real(2) * y * w;

			v.x = qxz + qyw;
			v.y = qyz - qxw;
			v.z = Real(1) - qxx - qyy;
		}
		break;
	default:
		assert(0);
	}

	return v;
}

template <class Real>
Vec3<Real> Quat<Real>::rotated(const Vec3<Real> &v) const
{
	Mat3<Real> m;
	m.set(*this);
	return m * v;
}

template <class Real>
Quat<Real> Quat<Real>::inverse() const
{
	Quat q;
	q.x = -x;
	q.y = -y;
	q.z = -z;
	q.w = w;
	return q;
}

template <class Real>
void Quat<Real>::toAxisAngle(Vec3<Real> &axis, Real &angle) const
{
	assert(w >= Real(-1) && w <= Real(1));

	Real s2 = Real(1) - w * w;
	Real len = (Real)(x * x + y * y + z * z);
    if (len > Real(DELTA) && s2 > Real(0))
	{
	    angle = (Real)(Real(2) * acos(w));
		Real recip = Real(1) / sqrt(s2);
		axis.x = x * recip;
		axis.y = y * recip;
		axis.z = z * recip;
		axis.normalize();
    }
    else
	{
		axis = Vec3<Real>::OneX;
	    angle = Real(0);
    }
}

template <class Real>
const Real* Quat<Real>::data() const
{
	return &x;
}

template <class Real>
Real* Quat<Real>::data()
{
	return &x;
}

template <class Real>
template <class CastReturnType>
Quat<CastReturnType> Quat<Real>::cast() const
{
	return Quat<CastReturnType>(
		static_cast<CastReturnType>(x),
		static_cast<CastReturnType>(y),
		static_cast<CastReturnType>(z),
		static_cast<CastReturnType>(w), false);
}

template <class Real>
Quat<Real> Quat<Real>::log(const Quat &q)
{
	Real a = acos(q.w);
	Real sina = sin(a);

	Quat ret;
	ret.w = Real(0);
	if (sina > Real(0))
	{
		ret.x = a * q.x / sina;
		ret.y = a * q.y / sina;
		ret.z = a * q.z / sina;
	}
	else
	{
		ret.x = ret.y = ret.z = Real(0);
	}
	return ret;
}

template <class Real>
Quat<Real> Quat<Real>::exp(const Quat &q)
{
	Real a = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	Real sina = sin(a);
	Real cosa = cos(a);

	Quat ret;
	ret.w = cosa;
	if (a > 0.0f)
	{
		ret.x = sina * q.x / a;
		ret.y = sina * q.y / a;
		ret.z = sina * q.z / a;
	}
	else
	{
		ret.x = ret.y = ret.z = 0.0f;
	}
	return ret;
}

MATHLIB_NS_END
