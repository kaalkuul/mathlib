#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("AABB3", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(AABB3f::Real) == sizeof(float));
            REQUIRE(sizeof(AABB3d::Real) == sizeof(double));
        }

        // Constants

        SECTION("AABB3f::One")
        {
            REQUIRE(AABB3f::One.inf.x == -0.5f);
            REQUIRE(AABB3f::One.inf.y == -0.5f);
            REQUIRE(AABB3f::One.inf.z == -0.5f);
            REQUIRE(AABB3f::One.sup.x == 0.5f);
            REQUIRE(AABB3f::One.sup.y == 0.5f);
            REQUIRE(AABB3f::One.sup.z == 0.5f);
        }

        // Constructors

        SECTION("AABB3()")
        {
            AABB3f box;
        }

        SECTION("AABB3(const Vec3<Real>& inf, const Vec3<Real>& sup)")
        {
            AABB3f box;
            box = AABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.inf == Vec3f::Zero);
            REQUIRE(box.sup == Vec3f(1, 2, 3));
        }

        // Setters

        SECTION("set(const Vec3<Real>& point)")
        {
            AABB3f box;
            box.set(Vec3f(1, 2, 3));
            REQUIRE(box.inf == Vec3f(1, 2, 3));
            REQUIRE(box.sup == Vec3f(1, 2, 3));
        }

        SECTION("set(const Vec3<Real>& inf, const Vec3<Real>& sup)")
        {
            AABB3f box;
            box.set(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.inf == Vec3f::Zero);
            REQUIRE(box.sup == Vec3f(1, 2, 3));
        }

        SECTION("set(const CAABB3<Real>& box)")
        {
            AABB3f box;
            box.set(CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(box.inf == Vec3f(-0.5f, -1.0f, -1.5f));
            REQUIRE(box.sup == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("set(int count, const Vec3<Real>* points)")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            AABB3f box;
            box.set(4, points);
            REQUIRE(box.inf == Vec3f(-10, -10, -10));
            REQUIRE(box.sup == Vec3f(10, 10, 10));
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

            AABB3f box;
            box.set(4, &points[1], sizeof(Vec3f)*2);
            REQUIRE(box.inf == Vec3f(-10, -10, -10));
            REQUIRE(box.sup == Vec3f(10, 10, 10));
        }

        SECTION("add(const Vec3<Real>& point)")
        {
            AABB3f box;
            box.set(Vec3f::Zero)
                .add(Vec3f(1, 1, 1))
                .add(Vec3f(-1, -1, -1))
                .add(Vec3f::Zero);
            REQUIRE(box.inf == Vec3f(-1, -1, -1));
            REQUIRE(box.sup == Vec3f(1, 1, 1));
        }

        // Create from

        SECTION("from(const Vec3<Real>& point)")
        {
            AABB3f box = AABB3f::from(Vec3f(1, 2, 3));
            REQUIRE(box.inf == Vec3f(1, 2, 3));
            REQUIRE(box.sup == Vec3f(1, 2, 3));
        }

        SECTION("from(const Vec3<Real>& inf, const Vec3<Real>& sup)")
        {
            AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box.inf == Vec3f::Zero);
            REQUIRE(box.sup == Vec3f(1, 2, 3));
        }

        SECTION("from(const CAABB3<Real>& box)")
        {
            AABB3f box = AABB3f::from(CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(box.inf == Vec3f(-0.5f, -1.0f, -1.5f));
            REQUIRE(box.sup == Vec3f(0.5f, 1.0f, 1.5f));
        }

        SECTION("from(int count, const Vec3<Real>* points)")
        {
            Vec3f points[] = {
                Vec3f(-10, -10, -10),
                Vec3f(-1, -1, -1),
                Vec3f(1, 1, 1),
                Vec3f(10, 10, 10)
            };

            AABB3f box = AABB3f::from(4, points);
            REQUIRE(box.inf == Vec3f(-10, -10, -10));
            REQUIRE(box.sup == Vec3f(10, 10, 10));
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

            AABB3f box = AABB3f::from(4, &points[1], sizeof(Vec3f) * 2);
            REQUIRE(box.inf == Vec3f(-10, -10, -10));
            REQUIRE(box.sup == Vec3f(10, 10, 10));
        }

        // Assignment operators

        SECTION("operator+= (const Vec3& t)")
        {
            AABB3f box = AABB3f::One;
            box += Vec3f(1, 2, 3);
            REQUIRE(box.inf == Vec3f(0.5f, 1.5f, 2.5f));
            REQUIRE(box.sup == Vec3f(1.5f, 2.5f, 3.5f));
        }

        SECTION("operator-= (const Vec3& t)")
        {
            AABB3f box = AABB3f::One;
            box -= Vec3f(1, 2, 3);
            REQUIRE(box.inf == Vec3f(-1.5f, -2.5f, -3.5f));
            REQUIRE(box.sup == Vec3f(-0.5f, -1.5f, -2.5f));
        }

        SECTION("operator*= (Real k)")
        {
            AABB3f box = AABB3f::One;
            box *= 2.0f;
            REQUIRE(box.inf == Vec3f(-1, -1, -1));
            REQUIRE(box.sup == Vec3f(1, 1, 1));
        }

        SECTION("operator/= (Real k)")
        {
            AABB3f box = AABB3f::One;
            box /= 2.0f;
            REQUIRE(box.inf == Vec3f(-0.25f, -0.25f, -0.25f));
            REQUIRE(box.sup == Vec3f(0.25f, 0.25f, 0.25f));
        }

        // Comparison operators

        SECTION("operator== (const Line3 &rhs)")
        {
            AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(box == box);
            REQUIRE(box == AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3)));
            REQUIRE(!(box == AABB3f::One));
        }

        SECTION("operator!= (const Line3 &rhs)")
        {
            AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE(!(box != box));
            REQUIRE(box != AABB3f::from(Vec3f::OneX, Vec3f(1, 2, 3)));
            REQUIRE(box != AABB3f::from(Vec3f::Zero, Vec3f(3, 2, 1)));
        }

        //  Functions

        SECTION("center() const")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE_THAT(box.center(), Matches::WithinAbs(Vec3f::Zero, 1e-10));
        }

        SECTION("extents() const")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE_THAT(box.extents(), Matches::WithinAbs(Vec3f(0.5f, 0.5f, 0.5f), 1e-10));
        }

        SECTION("size() const")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
        }

        SECTION("innerSphere() const")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE_THAT(box.innerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.5f), 1e-10));
        }

        SECTION("outerSphere() const")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE_THAT(box.outerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.866025f), 1e-6));
        }

        SECTION("volume()")
        {
            AABB3f box;
            
            box = AABB3f::One;
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            box = AABB3f(Vec3f::Zero, Vec3f(2, 2, 2));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(8.0f, 1e-10));
            box = AABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
            REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(6.0f, 1e-10));
        }

        SECTION("isNull()")
        {
            AABB3f box;

            box = AABB3f::One;
            REQUIRE(!box.isNull());
            box = AABB3f(Vec3f::Zero, Vec3f::Zero);
            REQUIRE(box.isNull());
        }

        SECTION("pointAt(Real t)")
        {
            AABB3f box;

            box = AABB3f::One;

            REQUIRE_THAT(box.pointAt(Vec3f(0.5f, 0.5f, 0.5f)), Matches::WithinAbs(Vec3f::Zero, 1e-10));

            REQUIRE_THAT(box.pointAt(Vec3f(+1, +1, +1)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1,  0, +1)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f( 0,  0, +1)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f( 0, +1, +1)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1, +1,  0)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f(+1,  0,  0)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f( 0,  0,  0)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec3f( 0, +1,  0)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, -0.5f), 1e-10));
        }

        SECTION("contains(const Vec3<Real>& point)")
        {
            AABB3f box = AABB3f::One;

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
            AABB3f box = AABB3f::One;
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

        SECTION("contains(const AABB3<Real>& box)")
        {
            AABB3f box = AABB3f::One;
            AABB3f box2 = AABB3f::One * 0.1f;

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

        SECTION("intersects(const AABB3<Real>& box)")
        {
            AABB3f box = AABB3f::One;
            AABB3f box2 = AABB3f::One * 0.1f;

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
            REQUIRE(AABB3f::One.cast<double>() == AABB3d::One);

            REQUIRE(AABB3d::One.cast<float>() == AABB3f::One);
        }

        SECTION("Matches::WithinAbs")
        {
            REQUIRE_THAT(AABB3f::One, Matches::WithinAbs(AABB3f::One));
        }
    }
}
