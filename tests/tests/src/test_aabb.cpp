#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("AABB", "")
    {
        // Constants

        SECTION("Vec3f::Zero")
        {
            REQUIRE(Vec3f::Zero.x == 0.0f);
            REQUIRE(Vec3f::Zero.y == 0.0f);
            REQUIRE(Vec3f::Zero.z == 0.0f);
        }

        SECTION("AABBf::One")
        {
            REQUIRE(AABBf::One.center == Vec3f::Zero);
            REQUIRE(AABBf::One.extents.x == 0.5f);
            REQUIRE(AABBf::One.extents.y == 0.5f);
            REQUIRE(AABBf::One.extents.z == 0.5f);
        }

        // Constructors

        SECTION("AABB()")
        {
            AABBf box;
        }

        SECTION("AABB(const Vec3<Real>& center, const Vec3<Real>& extents)")
        {
            AABBf box;

            box = AABBf(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        // Create from

        SECTION("from(const Vec3<Real>& min, const Vec3<Real>& max)")
        {
            AABBf box;

            box = AABBf::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f(0.5f, 1.0f, 1.5f));
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        // Assignment operators

        SECTION("operator+= (const Vec3& t)")
        {
            AABBf box = AABBf::One;
            box += Vec3f(1, 2, 3);
            REQUIRE(box.center == Vec3f(1, 2, 3));
            REQUIRE(box.extents == Vec3f(0.5f, 0.5f, 0.5f));
        }

        SECTION("operator-= (const Vec3& t)")
        {
            AABBf box = AABBf::One;
            box -= Vec3f(1, 2, 3);
            REQUIRE(box.center == Vec3f(-1, -2, -3));
            REQUIRE(box.extents == Vec3f(0.5f, 0.5f, 0.5f));
        }

        SECTION("operator*= (Real k)")
        {
            AABBf box = AABBf::One;
            box *= 2.0f;
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(1, 1, 1));
        }

        SECTION("operator/= (Real k)")
        {
            AABBf box = AABBf::One;
            box /= 2.0f;
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.25f, 0.25f, 0.25f));
        }

        // Comparison operators

        SECTION("operator== (const Line3 &rhs)")
        {
            AABBf box = AABBf::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box == box);
            REQUIRE(box == AABBf::from(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(!(box == AABBf::One));
        }

        SECTION("operator!= (const Line3 &rhs)")
        {
            AABBf box = AABBf::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(!(box != box));
            REQUIRE(box != AABBf::from(Vec3f::OneX, Vec3f(1, 2, 3)));
            REQUIRE(box != AABBf::from(Vec3f::Zero, Vec3f(3, 2, 1)));
        }

        //  Functions

        SECTION("min() const")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE_THAT(box.min(), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, -0.5f), 1e-10));
        }

        SECTION("max() const")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE_THAT(box.max(), Matches::WithinAbs(Vec3f(0.5f, 0.5f, 0.5f), 1e-10));
        }

        SECTION("size() const")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
        }

        SECTION("innerSphere() const")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE_THAT(box.innerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.5f), 1e-10));
        }

        SECTION("outerSphere() const")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE_THAT(box.outerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.866025f), 1e-6));
        }

        SECTION("volume()")
        {
            AABBf box;
            
            box = AABBf::One;
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            box = AABBf(Vec3f::Zero, Vec3f(2, 2, 2));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(8.0f, 1e-10));
            box = AABBf(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(6.0f, 1e-10));
        }

        SECTION("isNull()")
        {
            AABBf box;

            box = AABBf::One;
            REQUIRE(!box.isNull());
            box = AABBf(Vec3f::Zero, Vec3f::Zero);
            REQUIRE(box.isNull());
        }

        SECTION("pointAt(Real t)")
        {
            AABBf box;

            box = AABBf::One;

            REQUIRE_THAT(box.pointAt(Vec3f(0, 0, 0)), Matches::WithinAbs(Vec3f::Zero, 1e-10));

            REQUIRE_THAT(box.pointAt(Vec3f(+1, +1, +1)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1, -1, +1)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(-1, -1, +1)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(-1, +1, +1)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1, +1, -1)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1, -1, -1)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(-1, -1, -1)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(-1, +1, -1)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, -0.5f), 1e-10));
        }

        SECTION("contains(const Vec3<Real>& point)")
        {
            AABBf box = AABBf::One;

            REQUIRE(box.contains(Vec3f::Zero));

            REQUIRE(box.contains(Vec3f(+0.5f, +0.5f, +0.5f)));
            REQUIRE(box.contains(Vec3f(+0.5f, -0.5f, +0.5f)));
            REQUIRE(box.contains(Vec3f(-0.5f, -0.5f, +0.5f)));
            REQUIRE(box.contains(Vec3f(-0.5f, +0.5f, +0.5f)));
            REQUIRE(box.contains(Vec3f(+0.5f, +0.5f, -0.5f)));
            REQUIRE(box.contains(Vec3f(+0.5f, -0.5f, -0.5f)));
            REQUIRE(box.contains(Vec3f(-0.5f, -0.5f, -0.5f)));
            REQUIRE(box.contains(Vec3f(-0.5f, +0.5f, -0.5f)));

            REQUIRE(!box.contains(Vec3f(+0.51f, +0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec3f(+0.51f, -0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec3f(-0.51f, -0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec3f(-0.51f, +0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec3f(+0.51f, +0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec3f(+0.51f, -0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec3f(-0.51f, -0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec3f(-0.51f, +0.51f, -0.51f)));
        }

        SECTION("contains(const Sphere<Real>& sphere)")
        {
            AABBf box = AABBf::One;
            Spheref sphere = Spheref::One * 0.1f;

            REQUIRE(box.contains(sphere));

            REQUIRE(box.contains(sphere + Vec3f(+0.4f, +0.4f, +0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(+0.4f, -0.4f, +0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(-0.4f, -0.4f, +0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(-0.4f, +0.4f, +0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(+0.4f, +0.4f, -0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(+0.4f, -0.4f, -0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(-0.4f, -0.4f, -0.4f)));
            REQUIRE(box.contains(sphere + Vec3f(-0.4f, +0.4f, -0.4f)));

            REQUIRE(!box.contains(sphere + Vec3f(+0.41f, +0.41f, +0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(+0.41f, -0.41f, +0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(-0.41f, -0.41f, +0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(-0.41f, +0.41f, +0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(+0.41f, +0.41f, -0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(+0.41f, -0.41f, -0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(-0.41f, -0.41f, -0.41f)));
            REQUIRE(!box.contains(sphere + Vec3f(-0.41f, +0.41f, -0.41f)));
        }

        SECTION("contains(const AABB<Real>& box)")
        {
            AABBf box = AABBf::One;
            AABBf box2 = AABBf::One * 0.1f;

            REQUIRE(box.contains(box2));

            REQUIRE(box.contains(box2 + Vec3f(+0.45f, +0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(+0.45f, -0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(-0.45f, -0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(-0.45f, +0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(+0.45f, +0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(+0.45f, -0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(-0.45f, -0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec3f(-0.45f, +0.45f, -0.45f)));

            REQUIRE(!box.contains(box2 + Vec3f(+0.46f, +0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(+0.46f, -0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(-0.46f, -0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(-0.46f, +0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(+0.46f, +0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(+0.46f, -0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(-0.46f, -0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec3f(-0.46f, +0.46f, -0.46f)));
        }

        SECTION("intersects(const AABB<Real>& box)")
        {
            AABBf box = AABBf::One;
            AABBf box2 = AABBf::One * 0.1f;

            REQUIRE(box.intersects(box2));

            REQUIRE(box.intersects(box2 + Vec3f(+0.45f, +0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.45f, -0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.45f, -0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.45f, +0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.45f, +0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.45f, -0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.45f, -0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.45f, +0.45f, -0.45f)));

            REQUIRE(box.intersects(box2 + Vec3f(+0.46f, +0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.46f, -0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.46f, -0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.46f, +0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.46f, +0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(+0.46f, -0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.46f, -0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec3f(-0.46f, +0.46f, -0.46f)));

            REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, +0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, -0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, -0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, +0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, +0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, -0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, -0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, +0.56f, -0.56f)));
        }

        SECTION("cast()")
        {
            REQUIRE(AABBf::One.cast<double>() == AABBd::One);

            REQUIRE(AABBd::One.cast<float>() == AABBf::One);
        }
    }
}
