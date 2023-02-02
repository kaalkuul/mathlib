#include "utils.h"

namespace
{
    using namespace mathlib;

    TEST_CASE("Mat3", "")
    {
        // Constants

        SECTION("Mat3f::Zero")
        {
            REQUIRE(Mat3f::Zero.x == Vec3f::Zero);
            REQUIRE(Mat3f::Zero.y == Vec3f::Zero);
            REQUIRE(Mat3f::Zero.z == Vec3f::Zero);
            REQUIRE(Mat3f::Zero.isInitialized());
            REQUIRE(!Mat3f::Zero.isNormal());
            REQUIRE(Mat3f::Zero.isOrthogonal());
            REQUIRE(!Mat3f::Zero.isOrthonormal());
            REQUIRE(!Mat3f::Zero.isIdentity());
        }

        SECTION("Mat3f::One")
        {
            REQUIRE(Mat3f::One.x == Vec3f::OneX);
            REQUIRE(Mat3f::One.y == Vec3f::OneY);
            REQUIRE(Mat3f::One.z == Vec3f::OneZ);
            REQUIRE(Mat3f::One.isInitialized());
            REQUIRE(Mat3f::One.isNormal());
            REQUIRE(Mat3f::One.isOrthogonal());
            REQUIRE(Mat3f::One.isOrthonormal());
            REQUIRE(Mat3f::One.isIdentity());
        }

        // Constructors

        SECTION("Mat3()")
        {
            Mat3f m;
            REQUIRE(!m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat3(Real k)")
        {
            Mat3f m(3);
            REQUIRE(m.x == Vec3f(3, 0, 0));
            REQUIRE(m.y == Vec3f(0, 3, 0));
            REQUIRE(m.z == Vec3f(0, 0, 3));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat3(const Vec3<Real> &u, const Vec3<Real> &v, const Vec3<Real> &w)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE(m.x == Vec3f(1, 2, 3));
            REQUIRE(m.y == Vec3f(4, 5, 6));
            REQUIRE(m.z == Vec3f(7, 8, 9));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Setters

        SECTION("setIdentity()")
        {
            Mat3f m(3);
            m.setIdentity();
            REQUIRE(m == Mat3f::One);
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Mat3<Real>& m)")
        {
            Mat3f m(3);
            Mat3f a(42);
            m.set(a);
            REQUIRE(m == a);
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(const Quat<Real>& q)")
        {
            Quatf q = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            Mat3f m(3);
            m.set(q);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z)")
        {
            Mat3f m(3);
            m.set(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)")
        {
            Mat3f m(3);

            m.set(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &axis, Real angle)")
        {
            Mat3f m(3);
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(
                Vec3f(CPI4, SPI4, 0),
                Vec3f(-SPI4, CPI4, 0),
                Vec3f(0, 0, 1)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(Coord axis, Real angle)")
        {
            Mat3f m(3);
            m.set(Coord::X, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m.set(Coord::Y, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneY, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m.set(Coord::Z, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("slerp(const Mat3 &a, const Mat3 &b, Real weight)")
        {
            Mat3f a = Mat3f::One;
            Mat3f b = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat3f expect = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_6);
            Mat3f m0, mdot5, m1;
            m0.slerp(a, b, 0.0f);
            mdot5.slerp(a, b, 0.5f);
            m1.slerp(a, b, 1.0f);
            REQUIRE_THAT(m0, Matches::WithinAbs(a));
            REQUIRE(m0.isInitialized());
            REQUIRE(m0.isNormal());
            REQUIRE(m0.isOrthogonal());
            REQUIRE(m0.isOrthonormal());
            REQUIRE(m0.isIdentity());
            REQUIRE_THAT(mdot5, Matches::WithinAbs(expect));
            REQUIRE(mdot5.isInitialized());
            REQUIRE(mdot5.isNormal());
            REQUIRE(mdot5.isOrthogonal());
            REQUIRE(mdot5.isOrthonormal());
            REQUIRE(!mdot5.isIdentity());
            REQUIRE_THAT(m1, Matches::WithinAbs(b));
            REQUIRE(m1.isInitialized());
            REQUIRE(m1.isNormal());
            REQUIRE(m1.isOrthogonal());
            REQUIRE(m1.isOrthonormal());
            REQUIRE(!m1.isIdentity());
        }

        SECTION("slerpMaxAngle(const Mat3 &a, const Mat3 &b, Real maxAngle)")
        {
            Mat3f a = Mat3f::One;
            Mat3f b = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat3f expect = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_8);
            Mat3f m0, actual, m1;
            m0.slerpMaxAngle(a, b, 0.0f);
            actual.slerpMaxAngle(a, b, Constantsf::PI_OVER_8);
            m1.slerpMaxAngle(a, b, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m0, Matches::WithinAbs(a));
            REQUIRE(m0.isInitialized());
            REQUIRE(m0.isNormal());
            REQUIRE(m0.isOrthogonal());
            REQUIRE(m0.isOrthonormal());
            REQUIRE(m0.isIdentity());
            REQUIRE_THAT(actual, Matches::WithinAbs(expect));
            REQUIRE(actual.isInitialized());
            REQUIRE(actual.isNormal());
            REQUIRE(actual.isOrthogonal());
            REQUIRE(actual.isOrthonormal());
            REQUIRE(!actual.isIdentity());
            REQUIRE_THAT(m1, Matches::WithinAbs(b));
            REQUIRE(m1.isInitialized());
            REQUIRE(m1.isNormal());
            REQUIRE(m1.isOrthogonal());
            REQUIRE(m1.isOrthonormal());
            REQUIRE(!m1.isIdentity());
        }

        // Create from

        SECTION("from(const Quat<Real>& q)")
        {
            Quatf q = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            Mat3f m(3);
            m = Mat3f::from(q);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z)")
        {
            Mat3f m(3);
            m = Mat3f::from(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)")
        {
            Mat3f m(3);
            
            m = Mat3f::from(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat3f::from(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat3f::from(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat3f::from(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat3f::from(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat3f::from(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &axis, Real angle)")
        {
            Mat3f m(3);
            m = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(Coord axis, Real angle)")
        {
            Mat3f m(3);
            m = Mat3f::from(Coord::X, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m = Mat3f::from(Coord::Y, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneY, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m = Mat3f::from(Coord::Z, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("fromSlerp(const Mat3 &a, const Mat3 &b, Real weight)")
        {
            Mat3f a = Mat3f::One;
            Mat3f b = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat3f expect = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_6);
            Mat3f m0, mdot5, m1;
            m0 = Mat3f::fromSlerp(a, b, 0.0f);
            mdot5 = Mat3f::fromSlerp(a, b, 0.5f);
            m1 = Mat3f::fromSlerp(a, b, 1.0f);
            REQUIRE_THAT(m0, Matches::WithinAbs(a));
            REQUIRE(m0.isInitialized());
            REQUIRE(m0.isNormal());
            REQUIRE(m0.isOrthogonal());
            REQUIRE(m0.isOrthonormal());
            REQUIRE(m0.isIdentity());
            REQUIRE_THAT(mdot5, Matches::WithinAbs(expect));
            REQUIRE(mdot5.isInitialized());
            REQUIRE(mdot5.isNormal());
            REQUIRE(mdot5.isOrthogonal());
            REQUIRE(mdot5.isOrthonormal());
            REQUIRE(!mdot5.isIdentity());
            REQUIRE_THAT(m1, Matches::WithinAbs(b));
            REQUIRE(m1.isInitialized());
            REQUIRE(m1.isNormal());
            REQUIRE(m1.isOrthogonal());
            REQUIRE(m1.isOrthonormal());
            REQUIRE(!m1.isIdentity());
        }

        SECTION("fromSlerpMaxAngle(const Mat3 &a, const Mat3 &b, Real maxAngle)")
        {
            Mat3f a = Mat3f::One;
            Mat3f b = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat3f expect = Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_8);
            Mat3f m0, actual, m1;
            m0 = Mat3f::fromSlerpMaxAngle(a, b, 0.0f);
            actual = Mat3f::fromSlerpMaxAngle(a, b, Constantsf::PI_OVER_8);
            m1 = Mat3f::fromSlerpMaxAngle(a, b, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m0, Matches::WithinAbs(a));
            REQUIRE(m0.isInitialized());
            REQUIRE(m0.isNormal());
            REQUIRE(m0.isOrthogonal());
            REQUIRE(m0.isOrthonormal());
            REQUIRE(m0.isIdentity());
            REQUIRE_THAT(actual, Matches::WithinAbs(expect));
            REQUIRE(actual.isInitialized());
            REQUIRE(actual.isNormal());
            REQUIRE(actual.isOrthogonal());
            REQUIRE(actual.isOrthonormal());
            REQUIRE(!actual.isIdentity());
            REQUIRE_THAT(m1, Matches::WithinAbs(b));
            REQUIRE(m1.isInitialized());
            REQUIRE(m1.isNormal());
            REQUIRE(m1.isOrthogonal());
            REQUIRE(m1.isOrthonormal());
            REQUIRE(!m1.isIdentity());
        }


        // Assignments

        SECTION("operator*=(Real k)")
        {
            Mat3f m = Mat3f::One;
            m *= 42.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(42.0f)));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*=(const Mat3 &m)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f a(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            m *= a;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        // Arithmetic operators

        SECTION("operator/=(Real k)")
        {
            Mat3f m(Vec3f(10, 10, 10), Vec3f(10, 10, 10), Vec3f(10, 10, 10));
            m /= 5.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(2, 2, 2), Vec3f(2, 2, 2), Vec3f(2, 2, 2))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator-()")
        {
            Mat3f k(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f m = -k;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(-1, -2, -3), Vec3f(-4, -5, -6), Vec3f(-7, -8, -9))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Mat3 &m)")
        {
            Mat3f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            Mat3f m = a * b;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(90, 114, 138), Vec3f(54, 69, 84), Vec3f(18, 24, 30))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(Real k)")
        {
            Mat3f k(Vec3f(10, 10, 10), Vec3f(10, 10, 10), Vec3f(10, 10, 10));
            Mat3f m = k * 0.2f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(2, 2, 2), Vec3f(2, 2, 2), Vec3f(2, 2, 2))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Vec3<Real> &u)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m * Vec3f::OneX, Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(m * Vec3f::OneY, Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(m * Vec3f::OneZ, Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("operator/(Real k)")
        {
            Mat3f k(Vec3f(10, 10, 10), Vec3f(10, 10, 10), Vec3f(10, 10, 10));
            Mat3f m = k / 5.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(2, 2, 2), Vec3f(2, 2, 2), Vec3f(2, 2, 2))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        // Comparison operators

        SECTION("operator==(const Mat3 &m)")
        {
            Mat3f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f b;
            b.x = Vec3f(1, 2, 3);
            b.y = Vec3f(4, 5, 6);
            b.z = Vec3f(7, 8, 9);
            REQUIRE(a == a);
            REQUIRE(a == b);
        }

        SECTION("operator!=(const Mat3 &m)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE(m != Mat3f(Vec3f(1.1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2.1, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3.1), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4.1, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4, 5.1, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4, 5, 6.1), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7.1, 8, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8.1, 9)));
            REQUIRE(m != Mat3f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9.1)));
        }

        // Transformations

        SECTION("scale(const Vec3<Real>& coefficients)")
        {
            Mat3f m(Vec3f(10, 10, 10), Vec3f(10, 10, 10), Vec3f(10, 10, 10));
            m.scale(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(20, 20, 20),
                    Vec3f(30, 30, 30),
                    Vec3f(40, 40, 40)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(const Mat3& m)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(const Quat<Real>& q)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(const Vec3<Real>& axis, Real angle)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(Coord coord, Real angle)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(const Mat3& m)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3) * Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(const Quat<Real>& q)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3) * Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(const Vec3<Real>& axis, Real angle)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3) * Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(Coord coord, Real angle)")
        {
            Mat3f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3) * Mat3f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("orthonormalise()")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            m.orthonormalise();
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transpose()")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            m.transpose();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(1, 4, 7),
                    Vec3f(2, 5, 8),
                    Vec3f(3, 6, 9)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("invert()")
        {
            Mat3f m, im;

            m.set(Coord::X, Constantsf::PI_OVER_6).rotate(Coord::Y, Constantsf::PI_OVER_3);
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat3f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());

            m.set(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(im,
                Matches::WithinAbs(Mat3f(
                    Vec3f(-48 / 295.0f, 27 / 295.0f, 47 / 295.0f),
                    Vec3f(33 / 295.0f, -37 / 295.0f, 23 / 295.0f),
                    Vec3f(14 / 295.0f, 29 / 295.0f, -26 / 295.0f)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Functions

        SECTION("scaled()")
        {
            Mat3f k(Vec3f(10, 10, 10), Vec3f(10, 10, 10), Vec3f(10, 10, 10));
            Mat3f m = k.scaled(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(20, 20, 20),
                    Vec3f(30, 30, 30),
                    Vec3f(40, 40, 40)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transposed()")
        {
            Mat3f k(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f m = k.transposed();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(1, 4, 7), Vec3f(2, 5, 8), Vec3f(3, 6, 9))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("cofactors()")
        {
            Mat3f k(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            Mat3f m = k.cofactors();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(-48, 33, 14), Vec3f(27, -37, 29), Vec3f(47, 23, -26))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("adjoint()")
        {
            Mat3f k(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            Mat3f m = k.adjoint();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(Vec3f(-48, 27, 47), Vec3f(33, -37, 23), Vec3f(14, 29, -26))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("trace()")
        {
            Mat3f m(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            REQUIRE(m.trace() == 6.0f);
        }

        SECTION("determinant()")
        {
            Mat3f m(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            REQUIRE(m.determinant() == 295.0f);
        }

        SECTION("inversed()")
        {
            Mat3f k(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            Mat3f m = k.inversed();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat3f(
                    Vec3f(-48 / 295.0f,  27 / 295.0f,  47 / 295.0f),
                    Vec3f( 33 / 295.0f, -37 / 295.0f,  23 / 295.0f),
                    Vec3f( 14 / 295.0f,  29 / 295.0f, -26 / 295.0f)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("isIdentity()")
        {
            REQUIRE(Mat3f::One.isIdentity());
            REQUIRE(!Mat3f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).isIdentity());
            REQUIRE(!Mat3f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).isIdentity());
            REQUIRE(!Mat3f(1.1).isIdentity());
        }

        SECTION("isOrthonormal()")
        {
            REQUIRE(Mat3f::One.isOrthonormal());
            REQUIRE(Mat3f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).isOrthonormal());
            REQUIRE(!Mat3f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).isOrthonormal());
            REQUIRE(!Mat3f(1.1).isOrthonormal());
        }

        SECTION("normalError()")
        {
            REQUIRE(Mat3f::One.normalError() == 0.0f);
            REQUIRE(Mat3f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).normalError() == 0.0f);
            REQUIRE_THAT(Mat3f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).normalError(),
                Catch::Matchers::WithinAbs(27530.0f, 0.001f));
            REQUIRE_THAT(Mat3f(1.1).normalError(),
                Catch::Matchers::WithinAbs(0.1323f, 0.001f));
        }

        SECTION("orthogonalError()")
        {
            REQUIRE(Mat3f::One.orthogonalError() == 0.0f);
            REQUIRE(Mat3f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).orthogonalError() == 0.0f);
            REQUIRE_THAT(Mat3f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).orthogonalError(),
                Catch::Matchers::WithinAbs(16622.0f, 0.001f));
            REQUIRE(Mat3f(1.1).orthogonalError() == 0.0f);
        }

        SECTION("identityError()")
        {
            REQUIRE(Mat3f::One.identityError() == 0.0f);
            REQUIRE(Mat3f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).identityError() == 4.0f);
            REQUIRE_THAT(Mat3f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).identityError(),
                Catch::Matchers::WithinAbs(276.0f, 0.001f));
            REQUIRE_THAT(Mat3f(1.1).identityError(),
                Catch::Matchers::WithinAbs(0.03f, 0.001f));
        }

        SECTION("transform(Vec3<Real>& dest, const Vec3<Real>& src)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Vec3f v;
            m.transform(v, Vec3f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(1, 2, 3)));
            m.transform(v, Vec3f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(4, 5, 6)));
            m.transform(v, Vec3f::OneZ);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Vec3f d[3], v[3];
            v[0] = Vec3f::OneX;
            v[1] = Vec3f::OneY;
            v[2] = Vec3f::OneZ;
            m.transform(d, v, 3);
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(d[1], Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count, size_t destStride, size_t srcStride)")
        {
            Mat3f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Vec3f d[6], v[6];
            v[0] = Vec3f::OneX;
            v[2] = Vec3f::OneY;
            v[4] = Vec3f::OneZ;
            m.transform(d, v, 3, 2*sizeof(Vec3f), 2*sizeof(Vec3f));
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(d[4], Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("multiply(Mat3& dest, const Mat3& a, const Mat3& b)")
        {
            Mat3f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat3f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            Mat3f m;
            Mat3f::multiply(m, a, b);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat3f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }
    }
}
