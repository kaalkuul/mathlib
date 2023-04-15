#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Ray2", "")
    {
        // Create from

        SECTION("from(const Vec2<Real>& start, const Vec2<Real>& direction)")
        {
            Ray2f ray;

            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX);
            REQUIRE(ray.start == Vec2f::Zero);
            REQUIRE(ray.direction == Vec2f::OneX);

            ray = Ray2f::from(Vec2f::OneX, Vec2f::OneY);
            REQUIRE(ray.start == Vec2f::OneX);
            REQUIRE(ray.direction == Vec2f::OneY);

            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX * 2.0f);
            REQUIRE(ray.start == Vec2f::Zero);
            REQUIRE(ray.direction == Vec2f::OneX);
        }

        // Comparison operators

        SECTION("operator== (const Ray2 &rhs)")
        {
            Ray2f ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX);
            REQUIRE(ray == ray);
            REQUIRE(ray == Ray2f::from(Vec2f::Zero, Vec2f::OneX));
        }

        SECTION("operator!= (const Ray2 &rhs)")
        {
            Ray2f ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX);
            REQUIRE(!(ray != ray));
            REQUIRE(ray != Ray2f::from(Vec2f::Zero, Vec2f::Zero));
        }

        //  Functions

        SECTION("pointAt(Real dist)")
        {
            Ray2f ray;

            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX);
            REQUIRE_THAT(ray.pointAt(0.0f), Matches::WithinAbs(Vec2f::Zero, 1e-10));
            REQUIRE_THAT(ray.pointAt(1.0f), Matches::WithinAbs(Vec2f::OneX, 1e-10));
            REQUIRE_THAT(ray.pointAt(0.5f), Matches::WithinAbs(Vec2f::OneX * 0.5f, 1e-10));

            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneY);
            REQUIRE_THAT(ray.pointAt(0.0f), Matches::WithinAbs(Vec2f::Zero, 1e-10));
            REQUIRE_THAT(ray.pointAt(1.0f), Matches::WithinAbs(Vec2f::OneY, 1e-10));
            REQUIRE_THAT(ray.pointAt(0.5f), Matches::WithinAbs(Vec2f::OneY * 0.5f, 1e-10));
        }

        SECTION("distance(const Vec2<Real>& point)")
        {
            Ray2f ray;

            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneX);
            REQUIRE_THAT(ray.distance(Vec2f(10.0f, 3.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            ray = Ray2f::from(Vec2f::Zero, Vec2f::OneY);
            REQUIRE_THAT(ray.distance(Vec2f(3.0f, 10.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            ray = Ray2f::from(Vec2f::OneX, Vec2f::OneY - Vec2f::OneX);
            REQUIRE_THAT(ray.distance(Vec2f::Zero), Catch::Matchers::WithinAbs(sqrt(2.0f) / 2.0f, 1e-6));
        }

        SECTION("cast()")
        {
            REQUIRE(Ray2f::from(Vec2f::Zero, Vec2f::Zero).cast<double>() == Ray2d::from(Vec2d::Zero, Vec2d::Zero));
            REQUIRE(Ray2f::from(Vec2f::Zero, Vec2f::OneX).cast<double>() == Ray2d::from(Vec2d::Zero, Vec2d::OneX));
            REQUIRE(Ray2f::from(Vec2f::Zero, Vec2f::OneY).cast<double>() == Ray2d::from(Vec2d::Zero, Vec2d::OneY));

            REQUIRE(Ray2d::from(Vec2d::Zero, Vec2d::Zero).cast<float>() == Ray2f::from(Vec2f::Zero, Vec2f::Zero));
            REQUIRE(Ray2d::from(Vec2d::Zero, Vec2d::OneX).cast<float>() == Ray2f::from(Vec2f::Zero, Vec2f::OneX));
            REQUIRE(Ray2d::from(Vec2d::Zero, Vec2d::OneY).cast<float>() == Ray2f::from(Vec2f::Zero, Vec2f::OneY));
        }
    }
}
