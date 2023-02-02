#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Vec2", "")
    {
        // Constants

        SECTION("Vec2f::Zero")
        {
            REQUIRE(Vec2f::Zero.x == 0.0f);
            REQUIRE(Vec2f::Zero.y == 0.0f);
        }

        SECTION("Vec2f::OneX")
        {
            REQUIRE(Vec2f::OneX.x == 1.0f);
            REQUIRE(Vec2f::OneX.y == 0.0f);
        }

        SECTION("Vec2f::OneY")
        {
            REQUIRE(Vec2f::OneY.x == 0.0f);
            REQUIRE(Vec2f::OneY.y == 1.0f);
        }

        // Constructors

        SECTION("Vec2(Real k)")
        {
            Vec2f v(42);
            REQUIRE(v.x == 42.0f);
            REQUIRE(v.y == 42.0f);
        }

        SECTION("Vec3(Real x, Real y)")
        {
            Vec2f v(1, 2);
            REQUIRE(v.x == 1.0f);
            REQUIRE(v.y == 2.0f);
        }

        // Create from

        SECTION("fromAngle(Real angle, Real length = Real(1))")
        {
            REQUIRE_THAT(Vec2f::fromAngle(0.0f), Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_2), Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI), Matches::WithinAbs(-Vec2f::OneX));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_2*3), Matches::WithinAbs(-Vec2f::OneY));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_TIMES_2), Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_4),
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));

            REQUIRE_THAT(Vec2f::fromAngle(0.0f, 42.0), Matches::WithinAbs(Vec2f::OneX * 42.0));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_2, 42.0), Matches::WithinAbs(Vec2f::OneY * 42.0));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI, 42.0), Matches::WithinAbs(-Vec2f::OneX * 42.0));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_2 * 3, 42.0), Matches::WithinAbs(-Vec2f::OneY * 42.0));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_TIMES_2, 42.0), Matches::WithinAbs(Vec2f::OneX * 42.0));
            REQUIRE_THAT(Vec2f::fromAngle(Constantsf::PI_OVER_4, 42.0),
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4) * 42.0));
        }

        SECTION("fromClerp(const Vec2& u, const Vec2& v, Real ratio)")
        {
            REQUIRE_THAT(Vec2f::fromClerp(Vec2f::OneX, Vec2f::OneY, 0.0f),
                Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::fromClerp(Vec2f::OneX, Vec2f::OneY, 1.0f),
                Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::fromClerp(Vec2f::OneX, Vec2f::OneY, 0.5f),
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));
            REQUIRE_THAT(Vec2f::fromClerp(Vec2f::OneX, Vec2f::OneY * 3.0f, 0.5f),
                Matches::WithinAbs(Vec2f::OneX
                    .rotated(Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        SECTION("fromClerpMaxAngle(const Vec3& u, const Vec3& v, Real maxAngle)")
        {
            REQUIRE_THAT(Vec2f::fromClerpMaxAngle(Vec2f::OneX, Vec2f::OneY, 0.0f),
                Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::fromClerpMaxAngle(Vec2f::OneX, Vec2f::OneY, Constantsf::PI),
                Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::fromClerpMaxAngle(Vec2f::OneX, Vec2f::OneY, Constantsf::PI_OVER_4),
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));
            REQUIRE_THAT(Vec2f::fromClerpMaxAngle(Vec2f::OneX, Vec2f::OneY * 3.0f, Constantsf::PI_OVER_4),
                Matches::WithinAbs(Vec2f::OneX
                    .rotated(Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        // Setters

        SECTION("set(Real x, Real y)")
        {
            Vec2f v;
            v.set(1, 2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(1, 2)));
        }

        SECTION("set(const Vec2& v)")
        {
            Vec2f v;
            v.set(Vec2f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));
            v.set(Vec2f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));
            v.set(Vec2f(1, 2));
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(1, 2)));
        }

        SECTION("setAngle(Real angle, Real length = Real(1))")
        {
            Vec2f v;

            v.setAngle(0.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));
            v.setAngle(Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));
            v.setAngle(Constantsf::PI);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX));
            v.setAngle(Constantsf::PI_OVER_2 * 3);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneY));
            v.setAngle(Constantsf::PI_TIMES_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));
            v.setAngle(Constantsf::PI_OVER_4);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));

            v.setAngle(0.0f, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX * 42.0));
            v.setAngle(Constantsf::PI_OVER_2, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY * 42.0));
            v.setAngle(Constantsf::PI, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX * 42.0));
            v.setAngle(Constantsf::PI_OVER_2 * 3, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneY * 42.0));
            v.setAngle(Constantsf::PI_TIMES_2, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX * 42.0));
            v.setAngle(Constantsf::PI_OVER_4, 42.0);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4) * 42.0));
        }

        SECTION("clerp(const Vec2& u, const Vec2& v, Real ratio)")
        {
            Vec2f v;
            v.clerp(Vec2f::OneX, Vec2f::OneY, 0.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX));

            v.clerp(Vec2f::OneX, Vec2f::OneY, 1.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneY));

            v.clerp(Vec2f::OneX, Vec2f::OneY, 0.5f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));

            v.clerp(Vec2f::OneX, Vec2f::OneY * 3.0f, 0.5f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX
                    .rotated(Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        SECTION("clerpMaxAngle(const Vec2& u, const Vec2& v, Real maxAngle)")
        {
            Vec2f v;

            v.clerpMaxAngle(Vec2f::OneX, Vec2f::OneY, 0.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX));

            v.clerpMaxAngle(Vec2f::OneX, Vec2f::OneY, Constantsf::PI);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneY));

            v.clerpMaxAngle(Vec2f::OneX, Vec2f::OneY, Constantsf::PI_OVER_4);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX.rotated(Constantsf::PI_OVER_4)));

            v.clerpMaxAngle(Vec2f::OneX, Vec2f::OneY * 3.0f, Constantsf::PI_OVER_4);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec2f::OneX
                    .rotated(Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        // Transformations

        SECTION("normalize(Real k = 1)")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));

            v = Vec2f::OneY;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));


            v = Vec2f::Zero;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX * 2.0f));

            v = Vec2f::OneY;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY * 2.0f));
        }

        SECTION("rotate(Real angle)")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.rotate(Constantsf::PI_OVER_3);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.rotate(Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));

            v = Vec2f::OneY;
            v.rotate(Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX));
        }

        SECTION("rotate90()")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.rotate90();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.rotate90();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));

            v = Vec2f::OneY;
            v.rotate90();
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX));
        }

        SECTION("rotate180()")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.rotate180();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.rotate180();
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX));

            v = Vec2f::OneY;
            v.rotate180();
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneY));
        }

        SECTION("rotate270()")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.rotate270();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.rotate270();
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneY));

            v = Vec2f::OneY;
            v.rotate270();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));
        }

        SECTION("mirror(Coord axis)")
        {
            Vec2f v;

            v = Vec2f::Zero;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::Zero;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::Zero;
            v.mirror(Coord::Z);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::Zero));

            v = Vec2f::OneX;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneX));

            v = Vec2f::OneX;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneX));

            v = Vec2f::OneY;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f::OneY));

            v = Vec2f::OneY;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec2f::OneY));
        }

        // Access operators

        SECTION("operator[](Coord c)")
        {
            Vec2f v(1, 2);
            REQUIRE(v[Coord::X] == 1.0f);
            REQUIRE(v[Coord::Y] == 2.0f);
            v[Coord::X] = 1001.0f;
            v[Coord::Y] = 1002.0f;
            REQUIRE(v[Coord::X] == 1001.0f);
            REQUIRE(v[Coord::Y] == 1002.0f);
        }

        // Assignments

        SECTION("operator+=(const Vec2 &u)")
        {
            Vec2f v(1, 2);
            v += Vec2f(10, 11);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(11, 13)));
        }

        SECTION("operator-=(const Vec2 &u)")
        {
            Vec2f v(1, 2);
            v -= Vec2f(10, 11);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(-9, -9)));
        }

        SECTION("operator*=(Real k)")
        {
            Vec2f v(1, 2);
            v *= 3;
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(3, 6)));
        }

        SECTION("operator*=(const Mat2<Real> &m)")
        {
            Vec2f v(1, 2);
            v *= Mat2f(
                Vec2f(4, 5),
                Vec2f(7, 8)
            );
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(14, 23)));
        }

        SECTION("operator/=(Real k)")
        {
            Vec2f v(1, 2);
            v /= 2;
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(0.5, 1)));
        }

        // Arithmetic operators

        SECTION("operator+ (const Vec2 &u)")
        {
            Vec2f v(1, 2);
            REQUIRE_THAT(v + Vec2f(10, 11), Matches::WithinAbs(Vec2f(11, 13)));
        }

        SECTION("operator- ()")
        {
            Vec2f v(1, 2);
            REQUIRE_THAT(-v, Matches::WithinAbs(Vec2f(-1, -2)));
        }

        SECTION("operator+ (const Vec2 &u)")
        {
            Vec2f v(1, 2);
            REQUIRE_THAT(v - Vec2f(10, 11), Matches::WithinAbs(Vec2f(-9, -9)));
        }

        SECTION("operator* (const Vec2 &u)")
        {
            Vec2f v(1, 2);
            REQUIRE(v * Vec2f(10, 11) == 32);
        }

        SECTION("operator*=(const Mat3<Real> &m)")
        {
            Vec2f v(1, 2);
            Mat2f m(
                Vec2f(4, 5),
                Vec2f(7, 8)
            );
            REQUIRE_THAT(v * m, Matches::WithinAbs(Vec2f(14, 23)));
        }

        SECTION("operator* (Real k)")
        {
            Vec2f v(1, 2);
            REQUIRE_THAT(v * 2, Matches::WithinAbs(Vec2f(2, 4)));
        }

        SECTION("operator/ (Real k)")
        {
            Vec2f v(1, 2);
            REQUIRE_THAT(v / 0.5f, Matches::WithinAbs(Vec2f(2, 4)));
        }

        // Comparison operators

        SECTION("operator== (const Vec2 &u)")
        {
            Vec2f v(1, 2);
            REQUIRE(v == v);
            REQUIRE(v == Vec2f(1, 2));
        }

        SECTION("operator!= (const Vec2 &u)")
        {
            Vec2f v(1, 2);
            REQUIRE(!(v != v));
            REQUIRE(v != Vec2f(1.1, 2));
        }

        //  Functions

        SECTION("length()")
        {
            REQUIRE_THAT(Vec2f::Zero.length(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            REQUIRE_THAT(Vec2f::OneX.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec2f::OneY.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec2f(2, 2).length(), Catch::Matchers::WithinAbs(sqrt(2.0f) * 2, 1e-6));
        }

        SECTION("lengthSqr()")
        {
            REQUIRE_THAT(Vec2f::Zero.lengthSqr(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            REQUIRE_THAT(Vec2f::OneX.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec2f::OneY.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec2f(2, 2).lengthSqr(), Catch::Matchers::WithinAbs(8.0f, 1e-10));
        }

        SECTION("normalized(Real k = 1)")
        {
            REQUIRE_THAT(Vec2f::Zero.normalized(), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.normalized(), Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::OneY.normalized(), Matches::WithinAbs(Vec2f::OneY));

            REQUIRE_THAT(Vec2f::Zero.normalized(2.0f), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.normalized(2.0f), Matches::WithinAbs(Vec2f::OneX * 2.0f));
            REQUIRE_THAT(Vec2f::OneY.normalized(2.0f), Matches::WithinAbs(Vec2f::OneY * 2.0f));
        }

        SECTION("rotated()")
        {
            REQUIRE_THAT(Vec2f::Zero.rotated(Constantsf::PI_OVER_3), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.rotated(Constantsf::PI_OVER_2), Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::OneY.rotated(Constantsf::PI_OVER_2), Matches::WithinAbs(-Vec2f::OneX));
        }

        SECTION("rotated90()")
        {
            REQUIRE_THAT(Vec2f::Zero.rotated90(), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.rotated90(), Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::OneY.rotated90(), Matches::WithinAbs(-Vec2f::OneX));
        }

        SECTION("rotated180()")
        {
            REQUIRE_THAT(Vec2f::Zero.rotated180(), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.rotated180(), Matches::WithinAbs(-Vec2f::OneX));
            REQUIRE_THAT(Vec2f::OneY.rotated180(), Matches::WithinAbs(-Vec2f::OneY));
        }

        SECTION("rotated270()")
        {
            REQUIRE_THAT(Vec2f::Zero.rotated270(), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.rotated270(), Matches::WithinAbs(-Vec2f::OneY));
            REQUIRE_THAT(Vec2f::OneY.rotated270(), Matches::WithinAbs(Vec2f::OneX));
        }

        SECTION("mirrored(Coord axis)")
        {
            REQUIRE_THAT(Vec2f::Zero.mirrored(Coord::X), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::Zero.mirrored(Coord::Y), Matches::WithinAbs(Vec2f::Zero));
            REQUIRE_THAT(Vec2f::OneX.mirrored(Coord::X), Matches::WithinAbs(-Vec2f::OneX));
            REQUIRE_THAT(Vec2f::OneX.mirrored(Coord::Y), Matches::WithinAbs(Vec2f::OneX));
            REQUIRE_THAT(Vec2f::OneY.mirrored(Coord::X), Matches::WithinAbs(Vec2f::OneY));
            REQUIRE_THAT(Vec2f::OneY.mirrored(Coord::Y), Matches::WithinAbs(-Vec2f::OneY));
        }

        SECTION("majorCoord()")
        {
            REQUIRE(Vec2f::Zero.majorCoord() == Coord::X);
            REQUIRE(Vec2f::OneX.majorCoord() == Coord::X);
            REQUIRE(Vec2f::OneY.majorCoord() == Coord::Y);
            REQUIRE(Vec2f(2, 2).majorCoord() == Coord::X);
            REQUIRE(Vec2f(1, 2).majorCoord() == Coord::Y);
            REQUIRE(Vec2f(3, 1).majorCoord() == Coord::X);
        }

        SECTION("minorCoord()")
        {
            REQUIRE(Vec2f::Zero.minorCoord() == Coord::Y);
            REQUIRE(Vec2f::OneX.minorCoord() == Coord::Y);
            REQUIRE(Vec2f::OneY.minorCoord() == Coord::X);
            REQUIRE(Vec2f(2, 2).minorCoord() == Coord::Y);
            REQUIRE(Vec2f(1, 2).minorCoord() == Coord::X);
            REQUIRE(Vec2f(3, 1).minorCoord() == Coord::Y);
        }

        SECTION("isNull()")
        {
            REQUIRE(Vec2f::Zero.isNull());
            REQUIRE(!Vec2f::OneX.isNull());
            REQUIRE(!Vec2f::OneY.isNull());
            REQUIRE(!Vec2f(2, 2).isNull());
            REQUIRE(!Vec2f(1, 2).isNull());
            REQUIRE(!Vec2f(2, 1).isNull());
        }

        SECTION("randomUnitVector()")
        {
            for (int i = 0; i < N_TEST_RUNS; i++)
            {
                Vec2f v = Vec2f::randomUnitVector();
                REQUIRE(v.lengthSqr() <= 1.000001f);
            }
        }

    }
}
