#pragma once

MATHLIB_NS_BEGIN

//
// Constructors
//

template <class Real>
Frustum<Real>::Frustum()
{
}

template <class Real>
Frustum<Real>::Frustum(const Vec3<Real>* corners)
{
	set(corners);
}

//
//  Setters
//	

template <class Real>
void Frustum<Real>::set(const Vec3<Real>* corners)
{
	for (int i = 0; i < 8; i++)
	{
		this->corners[i] = corners[i];
	}
    computePlanes();
}

template <class Real>
void Frustum<Real>::set(const Mat34<Real>& ltw, const Vec3<Real>* corners)
{
    ltw.transform(this->corners, corners, 8);
    computePlanes();
}

template <class Real>
void Frustum<Real>::set(const Mat4<Real>& ltw, const Vec3<Real>* corners)
{
    ltw.transform(this->corners, corners, 8);
    computePlanes();
}

//
//  Functions
//

template <class Real>
bool Frustum<Real>::contains(const Vec3<Real>& point) const
{
	for (int i = 0; i < 6; i++)
    {
		float distance = planes[i].distance(point);

        if (distance > 0.0f)
        {
			return false;
        }
    }

	return true;
}

template <class Real>
bool Frustum<Real>::contains(const Vec4<Real>& point) const
{
	return contains(point.toVec3());
}

template <class Real>
bool Frustum<Real>::contains(const Sphere<Real>& sphere) const
{
    for (int i = 0; i < 6; i++)
    {
        float distance = planes[i].distance(sphere.center);

        if (distance > -sphere.radius)
        {
            return false;
        }
    }

    return true;
}

template <class Real>
bool Frustum<Real>::intersects(const Sphere<Real>& sphere) const
{
    for (int i = 0; i < 6; i++)
    {
        float distance = planes[i].distance(sphere.center);

        if (distance > sphere.radius)
        {
            return false;
        }
    }

    return true;
}

template <class Real>
template <class CastReturnType>
Frustum<CastReturnType> Frustum<Real>::cast() const
{
	Frustum<CastReturnType> result;
    for (int i = 0; i < 8; i++)
    {
        result.corners[i] = corners[i].template cast<CastReturnType>();
    }
    for (int i = 0; i < 6; i++)
    {
        result.planes[i] = planes[i].template cast<CastReturnType>();
    }
	return result;
}

template <class Real>
void Frustum<Real>::computePlanes()
{
    // Far clipping plane
    planes[0] = Plane<Real>::from(corners[4], corners[5], corners[6]);

    // Near clipping plane
    planes[1] = Plane<Real>::from(corners[0], -planes[0].normal);

    // Left plane
    planes[2] = Plane<Real>::from(corners[3], corners[7], corners[6]);

    // Top plane
    planes[3] = Plane<Real>::from(corners[3], corners[4], corners[7]);

    // Right plane
    planes[4] = Plane<Real>::from(corners[1], corners[5], corners[4]);

    // Bottom plane
    planes[5] = Plane<Real>::from(corners[1], corners[6], corners[5]);
}

MATHLIB_NS_END
