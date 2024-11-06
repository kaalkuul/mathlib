#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("CAABB3", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(CAABB3f::Real) == sizeof(float));
            REQUIRE(sizeof(CAABB3d::Real) == sizeof(double));
        }

        // Constants

        SECTION("Vec3f::Zero")
        {
            REQUIRE(Vec3f::Zero.x == 0.0f);
            REQUIRE(Vec3f::Zero.y == 0.0f);
            REQUIRE(Vec3f::Zero.z == 0.0f);
        }

        SECTION("CAABB3f::One")
        {
            REQUIRE(CAABB3f::One.center == Vec3f::Zero);
            REQUIRE(CAABB3f::One.extents.x == 0.5f);
            REQUIRE(CAABB3f::One.extents.y == 0.5f);
            REQUIRE(CAABB3f::One.extents.z == 0.5f);
        }

        // Constructors

        SECTION("CAABB3()")
        {
            CAABB3f box;
        }

        SECTION("CAABB3(const Vec3<Real>& center, const Vec3<Real>& extents)")
        {
            CAABB3f box;
            box = CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        // Setters

        SECTION("set(const Vec3<Real>& point)")
        {
            CAABB3f box;
            box.set(Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f(1, 2, 3));
            REQUIRE(box.extents == Vec3f::Zero);
        }

        SECTION("set(const Vec3<Real>& center, const Vec3<Real>& size)")
        {
            CAABB3f box;
            box.set(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("set(const AABB3<Real>& box)")
        {
            CAABB3f box;
            box.set(AABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(box.center == Vec3f(0.5f, 1.0f, 1.5f));
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("set(int count, const Vec3<Real>* points)")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            CAABB3f box;
            box.set(4, points);
            REQUIRE(box.center == Vec3f(0, 0, 0));
            REQUIRE(box.extents == Vec3f(10, 10, 10));
        }

        SECTION("set(int count, const Vec3<Real>* points, int stride)")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(-10, -10, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
                Vec3f(10, 10, 10),
                Vec3f::OneX * 1000,
            };

            CAABB3f box;
            box.set(4, &points[1], sizeof(Vec3f)*2);
            REQUIRE(box.center == Vec3f(0, 0, 0));
            REQUIRE(box.extents == Vec3f(10, 10, 10));
        }

        SECTION("add(const Vec3<Real>& point)")
        {
            CAABB3f box;
            box.set(Vec3f::Zero)
                .add(Vec3f(1, 1, 1))
                .add(Vec3f(-1, -1, -1))
                .add(Vec3f::Zero);
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(1, 1, 1));
        }

        // Create from

        SECTION("from(const Vec3<Real>& point)")
        {
            CAABB3f box = CAABB3f::from(Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f(1, 2, 3));
            REQUIRE(box.extents == Vec3f::Zero);
        }

        SECTION("from(const Vec3<Real>& center, const Vec3<Real>& size)")
        {
            CAABB3f box = CAABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("from(const AABB3<Real>& box)")
        {
            CAABB3f box = CAABB3f::from(AABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(box.center == Vec3f(0.5f, 1.0f, 1.5f));
            REQUIRE(box.extents == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("from(int count, const Vec3<Real>* points)")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            CAABB3f box = CAABB3f::from(4, points);
            REQUIRE(box.center == Vec3f(0, 0, 0));
            REQUIRE(box.extents == Vec3f(10, 10, 10));
        }

        SECTION("from(int count, const Vec3<Real>* points, int stride)")
        {
            Vec3f points[] = {
                Vec3f::OneX * 1000,
                Vec3f(-10, -10, -10),
                Vec3f::OneX * 1000,
                Vec3f(-1, -1, -1),
                Vec3f::OneX * 1000,
                Vec3f(1, 1, 1),
                Vec3f::OneX * 1000,
                Vec3f(10, 10, 10),
                Vec3f::OneX * 1000,
            };

            CAABB3f box = CAABB3f::from(4, &points[1], sizeof(Vec3f) * 2);
            REQUIRE(box.center == Vec3f(0, 0, 0));
            REQUIRE(box.extents == Vec3f(10, 10, 10));
        }

        // Assignment operators

        SECTION("operator+= (const Vec3& t)")
        {
            CAABB3f box = CAABB3f::One;
            box += Vec3f(1, 2, 3);
            REQUIRE(box.center == Vec3f(1, 2, 3));
            REQUIRE(box.extents == Vec3f(0.5f, 0.5f, 0.5f));
        }

        SECTION("operator-= (const Vec3& t)")
        {
            CAABB3f box = CAABB3f::One;
            box -= Vec3f(1, 2, 3);
            REQUIRE(box.center == Vec3f(-1, -2, -3));
            REQUIRE(box.extents == Vec3f(0.5f, 0.5f, 0.5f));
        }

        SECTION("operator*= (Real k)")
        {
            CAABB3f box = CAABB3f::One;
            box *= 2.0f;
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(1, 1, 1));
        }

        SECTION("operator/= (Real k)")
        {
            CAABB3f box = CAABB3f::One;
            box /= 2.0f;
            REQUIRE(box.center == Vec3f::Zero);
            REQUIRE(box.extents == Vec3f(0.25f, 0.25f, 0.25f));
        }

        // Comparison operators

        SECTION("operator== (const Line3 &rhs)")
        {
            CAABB3f box = CAABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box == box);
            REQUIRE(box == CAABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(!(box == CAABB3f::One));
        }

        SECTION("operator!= (const Line3 &rhs)")
        {
            CAABB3f box = CAABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(!(box != box));
            REQUIRE(box != CAABB3f::from(Vec3f::OneX, Vec3f(1, 2, 3)));
            REQUIRE(box != CAABB3f::from(Vec3f::Zero, Vec3f(3, 2, 1)));
        }

        //  Functions

        SECTION("inf() const")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE_THAT(box.inf(), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, -0.5f), 1e-10));
        }

        SECTION("sup() const")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE_THAT(box.sup(), Matches::WithinAbs(Vec3f(0.5f, 0.5f, 0.5f), 1e-10));
        }

        SECTION("size() const")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
        }

        SECTION("innerSphere() const")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE_THAT(box.innerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.5f), 1e-10));
        }

        SECTION("outerSphere() const")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE_THAT(box.outerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.866025f), 1e-6));
        }

        SECTION("volume()")
        {
            CAABB3f box;
            
            box = CAABB3f::One;
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            box = CAABB3f(Vec3f::Zero, Vec3f(2, 2, 2));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(8.0f, 1e-10));
            box = CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(6.0f, 1e-10));
        }

        SECTION("isNull()")
        {
            CAABB3f box;

            box = CAABB3f::One;
            REQUIRE(!box.isNull());
            box = CAABB3f(Vec3f::Zero, Vec3f::Zero);
            REQUIRE(box.isNull());
        }

        SECTION("pointAt(Real t)")
        {
            CAABB3f box;

            box = CAABB3f::One;

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
            CAABB3f box = CAABB3f::One;

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
            CAABB3f box = CAABB3f::One;
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

        SECTION("contains(const CAABB3<Real>& box)")
        {
            CAABB3f box = CAABB3f::One;
            CAABB3f box2 = CAABB3f::One * 0.1f;

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

        SECTION("intersects(const CAABB3<Real>& box)")
        {
            CAABB3f box = CAABB3f::One;
            CAABB3f box2 = CAABB3f::One * 0.1f;

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
            REQUIRE(CAABB3f::One.cast<double>() == CAABB3d::One);

            REQUIRE(CAABB3d::One.cast<float>() == CAABB3f::One);
        }

        SECTION("Matches::WithinAbs")
        {
            REQUIRE_THAT(CAABB3f::One, Matches::WithinAbs(CAABB3f::One));
        }
    }
}
