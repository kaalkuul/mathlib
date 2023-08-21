#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Mat34", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(Mat34f::Real) == sizeof(float));
            REQUIRE(sizeof(Mat34d::Real) == sizeof(double));
        }

        // Constants

        SECTION("Mat34f::Zero")
        {
            REQUIRE(Mat34f::Zero.rs == Mat3f::Zero);
            REQUIRE(Mat34f::Zero.t == Vec3f::Zero);
        }

        SECTION("Mat34f::One")
        {
            REQUIRE(Mat34f::One.rs == Mat3f::One);
            REQUIRE(Mat34f::One.t == Vec3f::Zero);
        }

        // Constructors

        SECTION("Mat34()")
        {
            Mat34f m;
            REQUIRE(!m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat34(Real k)")
        {
            Mat34f m(3.0f);
            REQUIRE(m.rs == Mat3f(3));
            REQUIRE(m.t == Vec3f::Zero);
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat34(const Vec3<Real> &u, const Vec3<Real> &v, const Vec3<Real> &w, const Vec3<Real> &t)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE(m.rs.x == Vec3f(1, 2, 3));
            REQUIRE(m.rs.y == Vec3f(4, 5, 6));
            REQUIRE(m.rs.z == Vec3f(7, 8, 9));
            REQUIRE(m.t == Vec3f(10, 11, 12));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Setters

        SECTION("setIdentity()")
        {
            Mat34f m(3);
            m.setIdentity();
            REQUIRE(m == Mat34f::One);
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Mat3<Real>& m)")
        {
            Mat34f m(3);
            Mat34f a(42);
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
            Mat34f m(3);
            m.set(q);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z, const Vec3<Real> &t)")
        {
            Mat34f m(3);
            m.set(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9),
                    Vec3f(10, 11, 12)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)")
        {
            Mat34f m(3);
            m.set(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &axis, Real angle)")
        {
            Mat34f m(3);
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("slerp(const Mat34 &a, const Mat34 &b, Real weight)")
        {
            Mat34f a = Mat34f::One;
            Mat34f b = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat34f expect = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_6);
            Mat34f m0, mdot5, m1;
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

        SECTION("slerpMaxAngle(const Mat34 &a, const Mat34 &b, Real maxAngle)")
        {
            Mat34f a = Mat34f::One;
            Mat34f b = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat34f expect = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_8);
            Mat34f m0, actual, m1;
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
            Mat34f m(3);
            m = Mat34f::from(q);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z)")
        {
            Mat34f m(3);
            m = Mat34f::from(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE_THAT(m.rs,
                Matches::WithinAbs(Mat3f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9)
                )));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f(10, 11, 12)));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(Coord ecoord, const Vec3<Real>& exact, Coord acoord, const Vec3<Real>& approx)")
        {
            Mat34f m(3);

            m = Mat34f::from(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat34f::from(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat34f::from(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat34f::from(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat34f::from(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat34f::from(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f::One));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &axis, Real angle)")
        {
            Mat34f m(3);
            m = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m.rs, Matches::WithinAbs(Mat3f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE_THAT(m.t, Matches::WithinAbs(Vec3f::Zero));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("fromSlerp(const Mat3 &a, const Mat3 &b, Real weight)")
        {
            Mat34f a = Mat34f::One;
            Mat34f b = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat34f expect = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_6);
            Mat34f m0, mdot5, m1;
            m0 = Mat34f::fromSlerp(a, b, 0.0f);
            mdot5 = Mat34f::fromSlerp(a, b, 0.5f);
            m1 = Mat34f::fromSlerp(a, b, 1.0f);
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
            Mat34f a = Mat34f::One;
            Mat34f b = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3);
            Mat34f expect = Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_8);
            Mat34f m0, actual, m1;
            m0 = Mat34f::fromSlerpMaxAngle(a, b, 0.0f);
            actual = Mat34f::fromSlerpMaxAngle(a, b, Constantsf::PI_OVER_8);
            m1 = Mat34f::fromSlerpMaxAngle(a, b, Constantsf::PI_OVER_3);
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


        // Access operators

        SECTION("operator[](Coord c) const")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE_THAT(m[Coord::X], Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(m[Coord::Y], Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(m[Coord::Z], Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("operator[](Coord c)")
        {
            Mat34f m;
            m[Coord::X] = Vec3f(1, 2, 3);
            m[Coord::Y] = Vec3f(4, 5, 6);
            m[Coord::Z] = Vec3f(7, 8, 9);
            REQUIRE_THAT(m[Coord::X], Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(m[Coord::Y], Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(m[Coord::Z], Matches::WithinAbs(Vec3f(7, 8, 9)));
        }


        // Assignments

        SECTION("operator*=(const Mat3 &m)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat3f a(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            m *= a;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30),
                Vec3f(10, 11, 12)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*=(const Mat34 &m)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat34f a(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1), Vec3f(20, 21, 22));
            m *= a;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30),
                Vec3f(268, 332, 396)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        // Arithmetic operators

        SECTION("operator-()")
        {
            Mat34f k(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat34f m = -k;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(-1, -2, -3),
                Vec3f(-4, -5, -6),
                Vec3f(-7, -8, -9),
                Vec3f(-10, -11, -12)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Mat3<Real> &m)")
        {
            Mat34f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat3f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            Mat34f m = a * b;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30),
                Vec3f(10, 11, 12)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Mat34 &m)")
        {
            Mat34f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat34f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1), Vec3f(20, 21, 22));
            Mat34f m = a * b;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30),
                Vec3f(268, 332, 396)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Vec3<Real> &u)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE_THAT(m * Vec3f::OneX, Matches::WithinAbs(Vec3f(11, 13, 15)));
            REQUIRE_THAT(m * Vec3f::OneY, Matches::WithinAbs(Vec3f(14, 16, 18)));
            REQUIRE_THAT(m * Vec3f::OneZ, Matches::WithinAbs(Vec3f(17, 19, 21)));
        }


        // Comparison operators

        SECTION("operator==(const Mat34 &m)")
        {
            Mat34f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat34f b(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE(a == a);
            REQUIRE(a == b);
        }

        SECTION("operator!=(const Mat34 &m)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE(m != Mat34f(Vec3f(1.1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2.1, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3.1), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4.1, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5.1, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6.1), Vec3f(7, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7.1, 8, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8.1, 9), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9.1), Vec3f(10, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10.1, 11, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11.1, 12)));
            REQUIRE(m != Mat34f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12.1)));
        }


        // Transformations

        SECTION("rotate(const Quat<Real> &q)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(const Vec3<Real>& axis, Real angle)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(Coord axis, Real angle)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat3f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("translate(const Vec3<Real>& translation)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.translate(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9),
                    Vec3f(12, 14, 16)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("scale(const Vec3<Real>& coefficients)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.scale(Vec3f(10, 100, 1000));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(10, 20, 30),
                    Vec3f(400, 500, 600),
                    Vec3f(7000, 8000, 9000),
                    Vec3f(100, 1100, 12000)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transform(const Mat3<Real>& mat)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100));
            Mat3f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6);
            m.transform(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
                * Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100))
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transform(const Mat34& mat)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100));
            Mat34f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6, Vec3f(4, 5, 6));
            m.transform(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6, Vec3f(4, 5, 6))
                * Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100))
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        SECTION("rotatePre(const Quat<Real> &q)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(const Vec3<Real>& axis, Real angle)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(Coord axis, Real angle)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("translatePre(const Vec3<Real>& translation)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.translatePre(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(1, 2, 3),
                    Vec3f(4, 5, 6),
                    Vec3f(7, 8, 9),
                    Vec3f(52, 62, 72)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("scalePre(const Vec3<Real>& coefficients)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.scalePre(Vec3f(10, 100, 1000));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(10, 20, 30),
                    Vec3f(400, 500, 600),
                    Vec3f(7000, 8000, 9000),
                    Vec3f(10, 11, 12)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transformPre(const Mat3<Real>& mat)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100));
            Mat3f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6);
            m.transformPre(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100))
                * Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transformPre(const Mat34& mat)")
        {
            Mat34f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100));
            Mat34f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6, Vec3f(4, 5, 6));
            m.transformPre(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat34f::from(Vec3f::OneZ, Constantsf::PI_OVER_3, Vec3f(1, 10, 100))
                * Mat34f::from(Vec3f::OneX, Constantsf::PI_OVER_6, Vec3f(4, 5, 6))
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        SECTION("transpose()")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.transpose();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat34f(
                    Vec3f(1, 4, 7),
                    Vec3f(2, 5, 8),
                    Vec3f(3, 6, 9),
                    Vec3f(10, 11, 12)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("invert()")
        {
            Mat34f m, im;

            m.set(Coord::X, Constantsf::PI_OVER_6, Vec3f(10, 11, 12)).rotate(Coord::Y, Constantsf::PI_OVER_3);
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat34f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());

            m.set(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3), Vec3f(10, 11, 12));
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat34f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        // Functions

        SECTION("localAxis(Coord axis)")
        {
            Mat34f m(Vec3f::OneX, Vec3f::OneY, Vec3f::OneZ, Vec3f(13, 14, 15));
            REQUIRE_THAT(m.localAxis(Coord::X),
                Matches::WithinAbs(Ray3f::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneX
                )));
            REQUIRE_THAT(m.localAxis(Coord::Y),
                Matches::WithinAbs(Ray3f::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneY
                )));
            REQUIRE_THAT(m.localAxis(Coord::Z),
                Matches::WithinAbs(Ray3f::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneZ
                )));
        }

        SECTION("localPlane(Coord axis)")
        {
            Mat34f m(Vec3f::OneX, Vec3f::OneY, Vec3f::OneZ, Vec3f(13, 14, 15));
            REQUIRE_THAT(m.localPlane(Coord::X),
                Matches::WithinAbs(Planef::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneX
                )));
            REQUIRE_THAT(m.localPlane(Coord::Y),
                Matches::WithinAbs(Planef::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneY
                )));
            REQUIRE_THAT(m.localPlane(Coord::Z),
                Matches::WithinAbs(Planef::from(
                    Vec3f(13, 14, 15),
                    Vec3f::OneZ
                )));
        }

        SECTION("isIdentity()")
        {
            REQUIRE(Mat34f::One.isIdentity());
            REQUIRE(!Mat34f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX, Vec3f::Zero).isIdentity());
            REQUIRE(!Mat34f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3), Vec3f::Zero).isIdentity());
            REQUIRE(!Mat34f(1.1).isIdentity());
        }

        SECTION("isOrthonormal()")
        {
            REQUIRE(Mat34f::One.isOrthonormal());
            REQUIRE(Mat34f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX, Vec3f::Zero).isOrthonormal());
            REQUIRE(!Mat34f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3), Vec3f::Zero).isOrthonormal());
            REQUIRE(!Mat34f(1.1).isOrthonormal());
        }

        SECTION("data()")
        {
            Mat34f m = Mat34f(Mat3f::One, Vec3f(1, 2, 3));
            const float* cdata = m.data();
            float* data = m.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[0] == 1.0f);
            REQUIRE(cdata[1] == 0.0f);
            REQUIRE(cdata[2] == 0.0f);
            REQUIRE(cdata[3] == 0.0f);
            REQUIRE(cdata[4] == 1.0f);
            REQUIRE(cdata[5] == 0.0f);
            REQUIRE(cdata[6] == 0.0f);
            REQUIRE(cdata[7] == 0.0f);
            REQUIRE(cdata[8] == 1.0f);
            REQUIRE(cdata[9] == 1.0f);
            REQUIRE(cdata[10] == 2.0f);
            REQUIRE(cdata[11] == 3.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(Mat34f::Zero.cast<double>() == Mat34d::Zero);
            REQUIRE(Mat34f::One.cast<double>() == Mat34d::One);

            REQUIRE(Mat34d::Zero.cast<float>() == Mat34f::Zero);
            REQUIRE(Mat34d::One.cast<float>() == Mat34f::One);
        }

        SECTION("transform(Vec3<Real>& dest, const Vec3<Real>& src)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Vec3f v;
            m.transform(v, Vec3f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(1, 2, 3) + Vec3f(10, 11, 12)));
            m.transform(v, Vec3f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(4, 5, 6) + Vec3f(10, 11, 12)));
            m.transform(v, Vec3f::OneZ);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec3f(7, 8, 9) + Vec3f(10, 11, 12)));
        }

        SECTION("transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Vec3f d[3], v[3];
            v[0] = Vec3f::OneX;
            v[1] = Vec3f::OneY;
            v[2] = Vec3f::OneZ;
            m.transform(d, v, 3);
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec3f(1, 2, 3) + Vec3f(10, 11, 12)));
            REQUIRE_THAT(d[1], Matches::WithinAbs(Vec3f(4, 5, 6) + Vec3f(10, 11, 12)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec3f(7, 8, 9) + Vec3f(10, 11, 12)));
        }

        SECTION("transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count, size_t destStride, size_t srcStride)")
        {
            Mat34f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Vec3f d[6], v[6];
            v[0] = Vec3f::OneX;
            v[2] = Vec3f::OneY;
            v[4] = Vec3f::OneZ;
            m.transform(d, v, 3, 2 * sizeof(Vec3f), 2 * sizeof(Vec3f));
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec3f(1, 2, 3) + Vec3f(10, 11, 12)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec3f(4, 5, 6) + Vec3f(10, 11, 12)));
            REQUIRE_THAT(d[4], Matches::WithinAbs(Vec3f(7, 8, 9) + Vec3f(10, 11, 12)));
        }

        SECTION("multiply(Mat3& dest, const Mat3& a, const Mat3& b)")
        {
            Mat34f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            Mat34f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1), Vec3f(20, 21, 22));
            Mat34f m;
            Mat34f::multiply(m, a, b);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat34f(
                Vec3f(90, 114, 138),
                Vec3f(54, 69, 84),
                Vec3f(18, 24, 30),
                Vec3f(268, 332, 396)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

    }
}
