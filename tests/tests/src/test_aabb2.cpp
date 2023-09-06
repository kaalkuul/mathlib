#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("AABB2", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(AABB2f::Real) == sizeof(float));
            REQUIRE(sizeof(AABB2d::Real) == sizeof(double));
        }

        // Constants

        SECTION("Vec2f::Zero")
        {
            REQUIRE(Vec2f::Zero.x == 0.0f);
            REQUIRE(Vec2f::Zero.y == 0.0f);
        }

        SECTION("AABB2f::One")
        {
            REQUIRE(AABB2f::One.center == Vec2f::Zero);
            REQUIRE(AABB2f::One.extents.x == 0.5f);
            REQUIRE(AABB2f::One.extents.y == 0.5f);
        }

        // Constructors

        SECTION("AABB2()")
        {
            AABB2f box;
        }

        SECTION("AABB2(const Vec2<Real>& center, const Vec2<Real>& extents)")
        {
            AABB2f box;
            box = AABB2f(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(0.5f, 1.0f));
        }

        // Setters

        SECTION("set(const Vec2<Real>& point)")
        {
            AABB2f box;
            box.set(Vec2f(1, 2));
            REQUIRE(box.center == Vec2f(1, 2));
            REQUIRE(box.extents == Vec2f::Zero);
        }

        SECTION("set(const Vec2<Real>& center, const Vec2<Real>& size)")
        {
            AABB2f box;
            box.set(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(0.5f, 1.0f));
        }

        SECTION("setInfSup(const Vec2<Real>& inf, const Vec2<Real>& sup)")
        {
            AABB2f box;
            box.setInfSup(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box.center == Vec2f(0.5f, 1.0f));
            REQUIRE(box.extents == Vec2f(0.5f, 1.0f));
        }

        SECTION("set(int count, const Vec2<Real>* points)")
        {
            Vec2f points[] = {
                Vec2f(-10, -10),
                Vec2f(-1, -1),
                Vec2f(1, 1),
                Vec2f(10, 10)
            };

            AABB2f box;
            box.set(4, points);
            REQUIRE(box.center == Vec2f(0, 0));
            REQUIRE(box.extents == Vec2f(10, 10));
        }

        SECTION("set(int count, const Vec2<Real>* points, int stride)")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(-10, -10),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
                Vec2f(10, 10),
                Vec2f::OneX * 1000,
            };

            AABB2f box;
            box.set(4, &points[1], sizeof(Vec2f)*2);
            REQUIRE(box.center == Vec2f(0, 0));
            REQUIRE(box.extents == Vec2f(10, 10));
        }

        SECTION("add(const Vec2<Real>& point)")
        {
            AABB2f box;
            box.set(Vec2f::Zero)
                .add(Vec2f(1, 1))
                .add(Vec2f(-1, -1))
                .add(Vec2f::Zero);
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(1, 1));
        }

        // Create from

        SECTION("from(const Vec2<Real>& point)")
        {
            AABB2f box = AABB2f::from(Vec2f(1, 2));
            REQUIRE(box.center == Vec2f(1, 2));
            REQUIRE(box.extents == Vec2f::Zero);
        }

        SECTION("from(const Vec2<Real>& center, const Vec2<Real>& size)")
        {
            AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(0.5f, 1.0f));
        }

        SECTION("fromInfSup(const Vec2<Real>& inf, const Vec2<Real>& sup)")
        {
            AABB2f box = AABB2f::fromInfSup(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box.center == Vec2f(0.5f, 1.0f));
            REQUIRE(box.extents == Vec2f(0.5f, 1.0f));
        }

        SECTION("from(int count, const Vec2<Real>* points)")
        {
            Vec2f points[] = {
                Vec2f(-10, -10),
                Vec2f(-1, -1),
                Vec2f(1, 1),
                Vec2f(10, 10)
            };

            AABB2f box = AABB2f::from(4, points);
            REQUIRE(box.center == Vec2f(0, 0));
            REQUIRE(box.extents == Vec2f(10, 10));
        }

        SECTION("from(int count, const Vec2<Real>* points, int stride)")
        {
            Vec2f points[] = {
                Vec2f::OneX * 1000,
                Vec2f(-10, -10),
                Vec2f::OneX * 1000,
                Vec2f(-1, -1),
                Vec2f::OneX * 1000,
                Vec2f(1, 1),
                Vec2f::OneX * 1000,
                Vec2f(10, 10),
                Vec2f::OneX * 1000,
            };

            AABB2f box = AABB2f::from(4, &points[1], sizeof(Vec2f) * 2);
            REQUIRE(box.center == Vec2f(0, 0));
            REQUIRE(box.extents == Vec2f(10, 10));
        }

        // Assignment operators

        SECTION("operator+= (const Vec2& t)")
        {
            AABB2f box = AABB2f::One;
            box += Vec2f(1, 2);
            REQUIRE(box.center == Vec2f(1, 2));
            REQUIRE(box.extents == Vec2f(0.5f, 0.5f));
        }

        SECTION("operator-= (const Vec2& t)")
        {
            AABB2f box = AABB2f::One;
            box -= Vec2f(1, 2);
            REQUIRE(box.center == Vec2f(-1, -2));
            REQUIRE(box.extents == Vec2f(0.5f, 0.5f));
        }

        SECTION("operator*= (Real k)")
        {
            AABB2f box = AABB2f::One;
            box *= 2.0f;
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(1, 1));
        }

        SECTION("operator/= (Real k)")
        {
            AABB2f box = AABB2f::One;
            box /= 2.0f;
            REQUIRE(box.center == Vec2f::Zero);
            REQUIRE(box.extents == Vec2f(0.25f, 0.25f));
        }

        // Comparison operators

        SECTION("operator== (const Line3 &rhs)")
        {
            AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(box == box);
            REQUIRE(box == AABB2f::from(Vec2f::Zero, Vec2f(1, 2)));
            REQUIRE(!(box == AABB2f::One));
        }

        SECTION("operator!= (const Line3 &rhs)")
        {
            AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE(!(box != box));
            REQUIRE(box != AABB2f::from(Vec2f::OneX, Vec2f(1, 2)));
            REQUIRE(box != AABB2f::from(Vec2f::Zero, Vec2f(3, 2)));
        }

        //  Functions

        SECTION("inf() const")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE_THAT(box.inf(), Matches::WithinAbs(Vec2f(-0.5f, -0.5f), 1e-10));
        }

        SECTION("sup() const")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE_THAT(box.sup(), Matches::WithinAbs(Vec2f(0.5f, 0.5f), 1e-10));
        }

        SECTION("size() const")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec2f(1.0f, 1.0f), 1e-10));
        }

        SECTION("innerCircle() const")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE_THAT(box.innerCircle(), Matches::WithinAbs(Circlef(Vec2f::Zero, 0.5f), 1e-10));
        }

        SECTION("outerCircle() const")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE_THAT(box.outerCircle(), Matches::WithinAbs(Circlef(Vec2f::Zero, 0.70710676908493042f), 1e-6));
        }

        SECTION("area()")
        {
            AABB2f box;
            
            box = AABB2f::One;
            REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            box = AABB2f(Vec2f::Zero, Vec2f(2, 2));
            REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(4.0f, 1e-10));
            box = AABB2f(Vec2f::Zero, Vec2f(1, 2));
            REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(2.0f, 1e-10));
        }

        SECTION("isNull()")
        {
            AABB2f box;

            box = AABB2f::One;
            REQUIRE(!box.isNull());
            box = AABB2f(Vec2f::Zero, Vec2f::Zero);
            REQUIRE(box.isNull());
        }

        SECTION("pointAt(Real t)")
        {
            AABB2f box;

            box = AABB2f::One;

            REQUIRE_THAT(box.pointAt(Vec2f(0, 0)), Matches::WithinAbs(Vec2f::Zero, 1e-10));

            REQUIRE_THAT(box.pointAt(Vec2f(+1, +1)), Matches::WithinAbs(Vec2f(+0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(+1, -1)), Matches::WithinAbs(Vec2f(+0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(-1, -1)), Matches::WithinAbs(Vec2f(-0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(-1, +1)), Matches::WithinAbs(Vec2f(-0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(+1, +1)), Matches::WithinAbs(Vec2f(+0.5f, +0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(+1, -1)), Matches::WithinAbs(Vec2f(+0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(-1, -1)), Matches::WithinAbs(Vec2f(-0.5f, -0.5f), 1e-10));
            REQUIRE_THAT(box.pointAt(Vec2f(-1, +1)), Matches::WithinAbs(Vec2f(-0.5f, +0.5f), 1e-10));
        }

        SECTION("contains(const Vec2<Real>& point)")
        {
            AABB2f box = AABB2f::One;

            REQUIRE(box.contains(Vec2f::Zero));

            REQUIRE(box.contains(Vec2f(+0.5f, +0.5f)));
            REQUIRE(box.contains(Vec2f(+0.5f, -0.5f)));
            REQUIRE(box.contains(Vec2f(-0.5f, -0.5f)));
            REQUIRE(box.contains(Vec2f(-0.5f, +0.5f)));
            REQUIRE(box.contains(Vec2f(+0.5f, +0.5f)));
            REQUIRE(box.contains(Vec2f(+0.5f, -0.5f)));
            REQUIRE(box.contains(Vec2f(-0.5f, -0.5f)));
            REQUIRE(box.contains(Vec2f(-0.5f, +0.5f)));

            REQUIRE(!box.contains(Vec2f(+0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec2f(+0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec2f(-0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec2f(-0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec2f(+0.51f, +0.51f)));
            REQUIRE(!box.contains(Vec2f(+0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec2f(-0.51f, -0.51f)));
            REQUIRE(!box.contains(Vec2f(-0.51f, +0.51f)));
        }

        SECTION("contains(const AABB2<Real>& box)")
        {
            AABB2f box = AABB2f::One;
            AABB2f box2 = AABB2f::One * 0.1f;

            REQUIRE(box.contains(box2));

            REQUIRE(box.contains(box2 + Vec2f(+0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(+0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(-0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(-0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(+0.45f, +0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(+0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(-0.45f, -0.45f)));
            REQUIRE(box.contains(box2 + Vec2f(-0.45f, +0.45f)));

            REQUIRE(!box.contains(box2 + Vec2f(+0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(+0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(-0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(-0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(+0.46f, +0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(+0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(-0.46f, -0.46f)));
            REQUIRE(!box.contains(box2 + Vec2f(-0.46f, +0.46f)));
        }

        SECTION("intersects(const AABB2<Real>& box)")
        {
            AABB2f box = AABB2f::One;
            AABB2f box2 = AABB2f::One * 0.1f;

            REQUIRE(box.intersects(box2));

            REQUIRE(box.intersects(box2 + Vec2f(+0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.45f, +0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.45f, -0.45f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.45f, +0.45f)));

            REQUIRE(box.intersects(box2 + Vec2f(+0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.46f, +0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(+0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.46f, -0.46f)));
            REQUIRE(box.intersects(box2 + Vec2f(-0.46f, +0.46f)));

            REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, +0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, -0.56f)));
            REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, +0.56f)));
        }

        SECTION("cast()")
        {
            REQUIRE(AABB2f::One.cast<double>() == AABB2d::One);

            REQUIRE(AABB2d::One.cast<float>() == AABB2f::One);
        }
    }
}
