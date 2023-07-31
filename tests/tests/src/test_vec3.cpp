#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Vec3", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(Vec3f::Real) == sizeof(float));
            REQUIRE(sizeof(Vec3d::Real) == sizeof(double));
        }

        // Constants

        SECTION("Vec3f::Zero")
        {
            REQUIRE(Vec3f::Zero.x == 0.0f);
            REQUIRE(Vec3f::Zero.y == 0.0f);
            REQUIRE(Vec3f::Zero.z == 0.0f);
        }

        SECTION("Vec3f::OneX")
        {
            REQUIRE(Vec3f::OneX.x == 1.0f);
            REQUIRE(Vec3f::OneX.y == 0.0f);
            REQUIRE(Vec3f::OneX.z == 0.0f);
        }

        SECTION("Vec3f::OneY")
        {
            REQUIRE(Vec3f::OneY.x == 0.0f);
            REQUIRE(Vec3f::OneY.y == 1.0f);
            REQUIRE(Vec3f::OneY.z == 0.0f);
        }

        SECTION("Vec3f::OneZ")
        {
            REQUIRE(Vec3f::OneZ.x == 0.0f);
            REQUIRE(Vec3f::OneZ.y == 0.0f);
            REQUIRE(Vec3f::OneZ.z == 1.0f);
        }

        // Constructors

        SECTION("Vec3(Real k)")
        {
            Vec3f v(42);
            REQUIRE(v.x == 42.0f);
            REQUIRE(v.y == 42.0f);
            REQUIRE(v.z == 42.0f);
        }

        SECTION("Vec3(Real x, Real y, Real z)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE(v.x == 1.0f);
            REQUIRE(v.y == 2.0f);
            REQUIRE(v.z == 3.0f);
        }

        SECTION("Vec3(const Vec2<Real> &u, Coord c = Coord::Z)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(Vec3f(Vec2f(1, 2), Coord::X), Matches::WithinAbs(Vec3f(0, 1, 2)));
            REQUIRE_THAT(Vec3f(Vec2f(1, 2), Coord::Y), Matches::WithinAbs(Vec3f(1, 0, 2)));
            REQUIRE_THAT(Vec3f(Vec2f(1, 2), Coord::Z), Matches::WithinAbs(Vec3f(1, 2, 0)));
        }

        // Create from

        SECTION("fromSlerp(const Vec3& u, const Vec3& v, Real ratio)")
        {
            REQUIRE_THAT(Vec3f::fromSlerp(Vec3f::OneX, Vec3f::OneY, 0.0f),
                Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::fromSlerp(Vec3f::OneX, Vec3f::OneY, 1.0f),
                Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::fromSlerp(Vec3f::OneX, Vec3f::OneY, 0.5f),
                Matches::WithinAbs(Vec3f::OneX.rotated(Coord::Z, Constantsf::PI_OVER_4)));
            REQUIRE_THAT(Vec3f::fromSlerp(Vec3f::OneX, Vec3f::OneY * 3.0f, 0.5f),
                Matches::WithinAbs(Vec3f::OneX
                    .rotated(Coord::Z, Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        SECTION("fromSlerpMaxAngle(const Vec3& u, const Vec3& v, Real maxAngle)")
        {
            REQUIRE_THAT(Vec3f::fromSlerpMaxAngle(Vec3f::OneX, Vec3f::OneY, 0.0f),
                Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::fromSlerpMaxAngle(Vec3f::OneX, Vec3f::OneY, Constantsf::PI),
                Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::fromSlerpMaxAngle(Vec3f::OneX, Vec3f::OneY, Constantsf::PI_OVER_4),
                Matches::WithinAbs(Vec3f::OneX.rotated(Coord::Z, Constantsf::PI_OVER_4)));
            REQUIRE_THAT(Vec3f::fromSlerpMaxAngle(Vec3f::OneX, Vec3f::OneY * 3.0f, Constantsf::PI_OVER_4),
                Matches::WithinAbs(Vec3f::OneX
                    .rotated(Coord::Z, Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        // Setters

        SECTION("set(Real x, Real y, Real z)")
        {
            Vec3f v;
            v.set(1, 2, 3);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(1, 2, 3)));
        }

        SECTION("set(const Vec3& v)")
        {
            Vec3f v;
            v.set(Vec3f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));
            v.set(Vec3f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));
            v.set(Vec3f::OneZ);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));
            v.set(Vec3f(1, 2, 3));
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(1, 2, 3)));
        }

        SECTION("slerp(const Vec3& u, const Vec3& v, Real ratio)")
        {
            Vec3f v;
            v.slerp(Vec3f::OneX, Vec3f::OneY, 0.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX));

            v.slerp(Vec3f::OneX, Vec3f::OneY, 1.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneY));

            v.slerp(Vec3f::OneX, Vec3f::OneY, 0.5f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX.rotated(Coord::Z, Constantsf::PI_OVER_4)));

            v.slerp(Vec3f::OneX, Vec3f::OneY * 3.0f, 0.5f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX
                    .rotated(Coord::Z, Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        SECTION("slerpMaxAngle(const Vec3& u, const Vec3& v, Real maxAngle)")
        {
            Vec3f v;

            v.slerpMaxAngle(Vec3f::OneX, Vec3f::OneY, 0.0f);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX));

            v.slerpMaxAngle(Vec3f::OneX, Vec3f::OneY, Constantsf::PI);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneY));

            v.slerpMaxAngle(Vec3f::OneX, Vec3f::OneY, Constantsf::PI_OVER_4);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX.rotated(Coord::Z, Constantsf::PI_OVER_4)));

            v.slerpMaxAngle(Vec3f::OneX, Vec3f::OneY * 3.0f, Constantsf::PI_OVER_4);
            REQUIRE_THAT(v,
                Matches::WithinAbs(Vec3f::OneX
                    .rotated(Coord::Z, Constantsf::PI_OVER_4)
                    * 2.0f
                ));
        }

        // Transformations

        SECTION("normalize(Real k = 1)")
        {
            Vec3f v;

            v = Vec3f::Zero;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::OneX;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));

            v = Vec3f::OneY;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));

            v = Vec3f::OneZ;
            v.normalize();
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));


            v = Vec3f::Zero;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::OneX;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX * 2.0f));

            v = Vec3f::OneY;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY * 2.0f));

            v = Vec3f::OneZ;
            v.normalize(2.0f);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ * 2.0f));
        }

        SECTION("rotate(Coord axis, Real angle)")
        {
            Vec3f v;

            v = Vec3f::Zero;
            v.rotate(Coord::X, Constantsf::PI_OVER_3);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::Zero;
            v.rotate(Coord::Y, Constantsf::PI_OVER_3);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::Zero;
            v.rotate(Coord::Z, Constantsf::PI_OVER_3);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::OneX;
            v.rotate(Coord::X, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));

            v = Vec3f::OneX;
            v.rotate(Coord::Y, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneZ));

            v = Vec3f::OneX;
            v.rotate(Coord::Z, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));

            v = Vec3f::OneY;
            v.rotate(Coord::X, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));

            v = Vec3f::OneY;
            v.rotate(Coord::Y, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));

            v = Vec3f::OneY;
            v.rotate(Coord::Z, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneX));

            v = Vec3f::OneZ;
            v.rotate(Coord::X, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneY));

            v = Vec3f::OneZ;
            v.rotate(Coord::Y, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));

            v = Vec3f::OneZ;
            v.rotate(Coord::Z, Constantsf::PI_OVER_2);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));
        }

        SECTION("mirror(Coord plane)")
        {
            Vec3f v;
            
            v = Vec3f::Zero;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::Zero;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::Zero;
            v.mirror(Coord::Z);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::Zero));

            v = Vec3f::OneX;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneX));

            v = Vec3f::OneX;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));

            v = Vec3f::OneX;
            v.mirror(Coord::Z);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneX));

            v = Vec3f::OneY;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));

            v = Vec3f::OneY;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneY));

            v = Vec3f::OneY;
            v.mirror(Coord::Z);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneY));

            v = Vec3f::OneZ;
            v.mirror(Coord::X);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));

            v = Vec3f::OneZ;
            v.mirror(Coord::Y);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f::OneZ));

            v = Vec3f::OneZ;
            v.mirror(Coord::Z);
            REQUIRE_THAT(v, Matches::WithinAbs(-Vec3f::OneZ));

        }

    	// Access operators

        SECTION("operator[](Coord c)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE(v[Coord::X] == 1.0f);
            REQUIRE(v[Coord::Y] == 2.0f);
            REQUIRE(v[Coord::Z] == 3.0f);
            v[Coord::X] = 1001.0f;
            v[Coord::Y] = 1002.0f;
            v[Coord::Z] = 1003.0f;
            REQUIRE(v[Coord::X] == 1001.0f);
            REQUIRE(v[Coord::Y] == 1002.0f);
            REQUIRE(v[Coord::Z] == 1003.0f);
        }

    	// Assignments

        SECTION("operator+=(const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            v += Vec3f(10, 11, 12);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(11, 13, 15)));
        }

        SECTION("operator-=(const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            v -= Vec3f(10, 11, 12);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(-9, -9, -9)));
        }

        SECTION("operator*=(Real k)")
        {
            Vec3f v(1, 2, 3);
            v *= 3;
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(3, 6, 9)));
        }

        SECTION("operator*=(const Mat3<Real> &m)")
        {
            Vec3f v(1, 2, 3);
            v *= Mat3f(
                Vec3f(4, 5, 6),
                Vec3f(7, 8, 9),
                Vec3f(10, 11, 12)
            );
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(32, 50, 68)));
        }

        SECTION("operator/=(Real k)")
        {
            Vec3f v(1, 2, 3);
            v /= 2;
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(0.5, 1, 1.5)));
        }

        SECTION("operator%=(const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            v %= Vec3f(4, 5, 6);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(-3, 6, -3)));
        }

        SECTION("operator%=(Coord c)")
        {
            Vec3f v(1, 2, 3);
            v %= Coord::Z;
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(2, -1, 0)));
        }

        // Arithmetic operators

        SECTION("operator+ (const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v + Vec3f(10, 11, 12), Matches::WithinAbs(Vec3f(11, 13, 15)));
        }

        SECTION("operator- ()")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(-v, Matches::WithinAbs(Vec3f(-1, -2, -3)));
        }

        SECTION("operator+ (const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v - Vec3f(10, 11, 12), Matches::WithinAbs(Vec3f(-9, -9, -9)));
        }

        SECTION("operator* (const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE(v * Vec3f(10, 11, 12) == 68);
        }

        SECTION("operator*=(const Mat3<Real> &m)")
        {
            Vec3f v(1, 2, 3);
            Mat3f m(
                Vec3f(4, 5, 6),
                Vec3f(7, 8, 9),
                Vec3f(10, 11, 12)
            );
            REQUIRE_THAT(v * m, Matches::WithinAbs(Vec3f(32, 50, 68)));
        }

        SECTION("operator%(const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v % Vec3f(4, 5, 6), Matches::WithinAbs(Vec3f(-3, 6, -3)));
        }

        SECTION("operator%(Coord c)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v % Coord::Z, Matches::WithinAbs(Vec3f(2, -1, 0)));
        }

        SECTION("operator* (Real k)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v * 2, Matches::WithinAbs(Vec3f(2, 4, 6)));
        }

        SECTION("operator/ (Real k)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE_THAT(v / 0.5f, Matches::WithinAbs(Vec3f(2, 4, 6)));
        }

    	// Comparison operators

        SECTION("operator== (const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE(v == v);
            REQUIRE(v == Vec3f(1, 2, 3));
        }

        SECTION("operator!= (const Vec3 &u)")
        {
            Vec3f v(1, 2, 3);
            REQUIRE(!(v != v));
            REQUIRE(v != Vec3f(1.1, 2, 3));
        }

        //  Functions

        SECTION("length()")
        {
            REQUIRE_THAT(Vec3f::Zero.length(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneX.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneY.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneZ.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f(2, 2, 2).length(), Catch::Matchers::WithinAbs(sqrt(3.0f) * 2, 1e-6));
        }

        SECTION("lengthSqr()")
        {
            REQUIRE_THAT(Vec3f::Zero.lengthSqr(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneX.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneY.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f::OneZ.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            REQUIRE_THAT(Vec3f(2, 2, 2).lengthSqr(), Catch::Matchers::WithinAbs(12.0f, 1e-10));
        }

        SECTION("normalized(Real k = 1)")
        {
            REQUIRE_THAT(Vec3f::Zero.normalized(), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::OneX.normalized(), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneY.normalized(), Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneZ.normalized(), Matches::WithinAbs(Vec3f::OneZ));

            REQUIRE_THAT(Vec3f::Zero.normalized(2.0f), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::OneX.normalized(2.0f), Matches::WithinAbs(Vec3f::OneX * 2.0f));
            REQUIRE_THAT(Vec3f::OneY.normalized(2.0f), Matches::WithinAbs(Vec3f::OneY * 2.0f));
            REQUIRE_THAT(Vec3f::OneZ.normalized(2.0f), Matches::WithinAbs(Vec3f::OneZ * 2.0f));
        }

        SECTION("rotated(Coord axis, Real angle)")
        {
            REQUIRE_THAT(Vec3f::Zero.rotated(Coord::X, Constantsf::PI_OVER_3), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::Zero.rotated(Coord::Y, Constantsf::PI_OVER_3), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::Zero.rotated(Coord::Z, Constantsf::PI_OVER_3), Matches::WithinAbs(Vec3f::Zero));

            REQUIRE_THAT(Vec3f::OneX.rotated(Coord::X, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneX.rotated(Coord::Y, Constantsf::PI_OVER_2), Matches::WithinAbs(-Vec3f::OneZ));
            REQUIRE_THAT(Vec3f::OneX.rotated(Coord::Z, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneY));

            REQUIRE_THAT(Vec3f::OneY.rotated(Coord::X, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneZ));
            REQUIRE_THAT(Vec3f::OneY.rotated(Coord::Y, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneY.rotated(Coord::Z, Constantsf::PI_OVER_2), Matches::WithinAbs(-Vec3f::OneX));

            REQUIRE_THAT(Vec3f::OneZ.rotated(Coord::X, Constantsf::PI_OVER_2), Matches::WithinAbs(-Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneZ.rotated(Coord::Y, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneZ.rotated(Coord::Z, Constantsf::PI_OVER_2), Matches::WithinAbs(Vec3f::OneZ));
        }

        SECTION("mirrored(Coord plane)")
        {
            REQUIRE_THAT(Vec3f::Zero.mirrored(Coord::X), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::Zero.mirrored(Coord::Y), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::Zero.mirrored(Coord::Z), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec3f::OneX.mirrored(Coord::X), Matches::WithinAbs(-Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneX.mirrored(Coord::Y), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneX.mirrored(Coord::Z), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec3f::OneY.mirrored(Coord::X), Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneY.mirrored(Coord::Y), Matches::WithinAbs(-Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneY.mirrored(Coord::Z), Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec3f::OneZ.mirrored(Coord::X), Matches::WithinAbs(Vec3f::OneZ));
            REQUIRE_THAT(Vec3f::OneZ.mirrored(Coord::Y), Matches::WithinAbs(Vec3f::OneZ));
            REQUIRE_THAT(Vec3f::OneZ.mirrored(Coord::Z), Matches::WithinAbs(-Vec3f::OneZ));
        }

        SECTION("majorCoord()")
        {
            REQUIRE(Vec3f::Zero.majorCoord()   == Coord::X);
            REQUIRE(Vec3f::OneX.majorCoord()   == Coord::X);
            REQUIRE(Vec3f::OneY.majorCoord()   == Coord::Y);
            REQUIRE(Vec3f::OneZ.majorCoord()   == Coord::Z);
            REQUIRE(Vec3f(2, 2, 2).majorCoord()== Coord::X);
            REQUIRE(Vec3f(1, 2, 3).majorCoord()== Coord::Z);
            REQUIRE(Vec3f(1, 3, 2).majorCoord()== Coord::Y);
            REQUIRE(Vec3f(3, 1, 2).majorCoord()== Coord::X);
        }

        SECTION("majorCoord()")
        {
            REQUIRE(Vec3f::Zero.minorCoord()   == Coord::Z);
            REQUIRE(Vec3f::OneX.minorCoord()   == Coord::Z);
            REQUIRE(Vec3f::OneY.minorCoord()   == Coord::Z);
            REQUIRE(Vec3f::OneZ.minorCoord()   == Coord::Y);
            REQUIRE(Vec3f(2, 2, 2).minorCoord()== Coord::Z);
            REQUIRE(Vec3f(1, 2, 3).minorCoord()== Coord::X);
            REQUIRE(Vec3f(3, 1, 2).minorCoord()== Coord::Y);
            REQUIRE(Vec3f(3, 2, 1).minorCoord()== Coord::Z);
        }

        SECTION("isNull()")
        {
            REQUIRE(Vec3f::Zero.isNull());
            REQUIRE(!Vec3f::OneX.isNull());
            REQUIRE(!Vec3f::OneY.isNull());
            REQUIRE(!Vec3f::OneZ.isNull());
            REQUIRE(!Vec3f(2, 2, 2).isNull());
            REQUIRE(!Vec3f(1, 2, 3).isNull());
            REQUIRE(!Vec3f(3, 1, 2).isNull());
            REQUIRE(!Vec3f(3, 2, 1).isNull());
        }

        SECTION("data()")
        {
            Vec3f v = Vec3f::OneX;
            const float* cdata = v.data();
            float* data = v.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[0] == 1.0f);
            REQUIRE(cdata[1] == 0.0f);
            REQUIRE(cdata[2] == 0.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(Vec3f::Zero.cast<double>() == Vec3d::Zero);
            REQUIRE(Vec3f::OneX.cast<double>() == Vec3d::OneX);
            REQUIRE(Vec3f::OneY.cast<double>() == Vec3d::OneY);
            REQUIRE(Vec3f::OneZ.cast<double>() == Vec3d::OneZ);

            REQUIRE(Vec3d::Zero.cast<float>() == Vec3f::Zero);
            REQUIRE(Vec3d::OneX.cast<float>() == Vec3f::OneX);
            REQUIRE(Vec3d::OneY.cast<float>() == Vec3f::OneY);
            REQUIRE(Vec3d::OneZ.cast<float>() == Vec3f::OneZ);
        }

        SECTION("randomUnitVector()")
        {
            for (int i = 0; i < N_TEST_RUNS; i++)
            {
                Vec3f v = Vec3f::randomUnitVector();
                REQUIRE(v.lengthSqr() <= 1.000001f);
            }
        }

    }
}
