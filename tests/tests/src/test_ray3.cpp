#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Ray3", "")
    {
        // Create from

        SECTION("from(const Vec3<Real>& start, const Vec3<Real>& direction)")
        {
            Ray3f ray;

            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(ray.start == Vec3f::Zero);
            REQUIRE(ray.direction == Vec3f::OneX);

            ray = Ray3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE(ray.start == Vec3f::OneX);
            REQUIRE(ray.direction == Vec3f::OneY);

            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX * 2.0f);
            REQUIRE(ray.start == Vec3f::Zero);
            REQUIRE(ray.direction == Vec3f::OneX);
        }

        // Comparison operators

        SECTION("operator== (const Ray3 &rhs)")
        {
            Ray3f ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(ray == ray);
            REQUIRE(ray == Ray3f::from(Vec3f::Zero, Vec3f::OneX));
        }

        SECTION("operator!= (const Ray3 &rhs)")
        {
            Ray3f ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(!(ray != ray));
            REQUIRE(ray != Ray3f::from(Vec3f::Zero, Vec3f::Zero));
        }

        //  Functions

        SECTION("pointAt(Real dist)")
        {
            Ray3f ray;

            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(ray.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(ray.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneX, 1e-10));
            REQUIRE_THAT(ray.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneX * 0.5f, 1e-10));

            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(ray.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(ray.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneY, 1e-10));
            REQUIRE_THAT(ray.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneY * 0.5f, 1e-10));

            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneZ);
            REQUIRE_THAT(ray.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(ray.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneZ, 1e-10));
            REQUIRE_THAT(ray.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneZ * 0.5f, 1e-10));
        }

        SECTION("distance(const Vec3<Real>& point)")
        {
            Ray3f ray;

            ray = Ray3f::from(Vec3f::OneX, Vec3f::OneX);
            REQUIRE_THAT(ray.distance(Vec3f::Zero), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(ray.distance(Vec3f(10.0f, 3.0f, 0.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            ray = Ray3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(ray.distance(Vec3f(3.0f, 10.0f, 0.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            ray = Ray3f::from(Vec3f::OneX, Vec3f::OneY - Vec3f::OneX);
            REQUIRE_THAT(ray.distance(Vec3f::Zero), Catch::Matchers::WithinAbs(sqrt(2.0f) / 2.0f, 1e-6));
        }

        SECTION("cast()")
        {
            REQUIRE(Ray3f::from(Vec3f::Zero, Vec3f::Zero).cast<double>() == Ray3d::from(Vec3d::Zero, Vec3d::Zero));
            REQUIRE(Ray3f::from(Vec3f::Zero, Vec3f::OneX).cast<double>() == Ray3d::from(Vec3d::Zero, Vec3d::OneX));
            REQUIRE(Ray3f::from(Vec3f::Zero, Vec3f::OneY).cast<double>() == Ray3d::from(Vec3d::Zero, Vec3d::OneY));

            REQUIRE(Ray3d::from(Vec3d::Zero, Vec3d::Zero).cast<float>() == Ray3f::from(Vec3f::Zero, Vec3f::Zero));
            REQUIRE(Ray3d::from(Vec3d::Zero, Vec3d::OneX).cast<float>() == Ray3f::from(Vec3f::Zero, Vec3f::OneX));
            REQUIRE(Ray3d::from(Vec3d::Zero, Vec3d::OneY).cast<float>() == Ray3f::from(Vec3f::Zero, Vec3f::OneY));
        }
    }
}
