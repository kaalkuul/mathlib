#include "utils.h"

namespace
{
    using namespace mathlib;

    TEST_CASE("Mat4", "")
    {
        // Constants

        SECTION("Mat4f::Zero")
        {
            REQUIRE(Mat4f::Zero.x == Vec3f::Zero);
            REQUIRE(Mat4f::Zero.y == Vec3f::Zero);
            REQUIRE(Mat4f::Zero.z == Vec3f::Zero);
            REQUIRE(Mat4f::Zero.isInitialized());
            REQUIRE(!Mat4f::Zero.isNormal());
            REQUIRE(Mat4f::Zero.isOrthogonal());
            REQUIRE(!Mat4f::Zero.isOrthonormal());
            REQUIRE(!Mat4f::Zero.isIdentity());
        }

        SECTION("Mat4f::One")
        {
            REQUIRE(Mat4f::One.x == Vec3f::OneX);
            REQUIRE(Mat4f::One.y == Vec3f::OneY);
            REQUIRE(Mat4f::One.z == Vec3f::OneZ);
            REQUIRE(Mat4f::One.isInitialized());
            REQUIRE(Mat4f::One.isNormal());
            REQUIRE(Mat4f::One.isOrthogonal());
            REQUIRE(Mat4f::One.isOrthonormal());
            REQUIRE(Mat4f::One.isIdentity());
        }

        // Constructors

        SECTION("Mat4()")
        {
            Mat4f m;
            REQUIRE(!m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat4(Real k)")
        {
            Mat4f m(3);
            REQUIRE(m.x == Vec3f(3, 0, 0));
            REQUIRE(m.y == Vec3f(0, 3, 0));
            REQUIRE(m.z == Vec3f(0, 0, 3));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat4(const Vec3<Real> &u, const Vec3<Real> &v, const Vec3<Real> &w)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            REQUIRE(m.x == Vec4f(1, 2, 3));
            REQUIRE(m.y == Vec4f(4, 5, 6));
            REQUIRE(m.z == Vec4f(7, 8, 9));
            REQUIRE(m.t == Vec4f(10, 11, 12, 1));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Setters

        SECTION("setIdentity()")
        {
            Mat4f m(3);
            m.setIdentity();
            REQUIRE(m == Mat4f::One);
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Mat4<Real>& m)")
        {
            Mat4f m(3);
            Mat4f a(42);
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
            Mat4f m(3);
            m.set(q);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z)")
        {
            Mat4f m(3);
            m.set(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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
            Mat4f m(3);

            m.set(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m.set(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Vec3<Real> &axis, Real angle)")
        {
            Mat4f m(3);
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(
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
            Mat4f m(3);
            m.set(Coord::X, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m.set(Coord::Y, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneY, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m.set(Coord::Z, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Create from

        SECTION("from(const Quat<Real>& q, const Vec3<Real> &t)")
        {
            Quatf q = Quatf::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            Mat4f m(3);
            m = Mat4f::from(q);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &x, const Vec3<Real> &y, const Vec3<Real> &z, const Vec3<Real> &t)")
        {
            Mat4f m(3);
            m = Mat4f::from(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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
            Mat4f m(3);
            
            m = Mat4f::from(Coord::X, Vec3f::OneX, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat4f::from(Coord::X, Vec3f::OneX, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat4f::from(Coord::Y, Vec3f::OneY, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat4f::from(Coord::Y, Vec3f::OneY, Coord::Z, Vec3f::OneZ);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat4f::from(Coord::Z, Vec3f::OneZ, Coord::X, Vec3f::OneX);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());

            m = Mat4f::from(Coord::Z, Vec3f::OneZ, Coord::Y, Vec3f::OneY);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("from(const Vec3<Real> &axis, Real angle)")
        {
            Mat4f m(3);
            m = Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_4);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(Vec3f(CPI4, SPI4, 0), Vec3f(-SPI4, CPI4, 0), Vec3f(0, 0, 1))));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("from(Coord axis, Real angle)")
        {
            Mat4f m(3);
            m = Mat4f::from(Coord::X, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m = Mat4f::from(Coord::Y, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneY, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
            m = Mat4f::from(Coord::Z, Constantsf::PI_OVER_3);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Arithmetic operators

        SECTION("operator-()")
        {
            Mat4f k(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat4f m = -k;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(Vec3f(-1, -2, -3), Vec3f(-4, -5, -6), Vec3f(-7, -8, -9), -Vec4f::OneW)));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Mat4 &m)")
        {
            Mat4f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat4f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            Mat4f m = a * b;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(Vec3f(90, 114, 138), Vec3f(54, 69, 84), Vec3f(18, 24, 30))));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Vec3<Real> &u)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE_THAT(m * Vec3f::OneX, Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(m * Vec3f::OneY, Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(m * Vec3f::OneZ, Matches::WithinAbs(Vec3f(7, 8, 9)));
        }


        // Comparison operators

        SECTION("operator==(const Mat4 &m)")
        {
            Mat4f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat4f b;
            b.x = Vec3f(1, 2, 3);
            b.y = Vec3f(4, 5, 6);
            b.z = Vec3f(7, 8, 9);
            b.t = Vec4f::OneW;
            REQUIRE(a == a);
            REQUIRE(a == b);
        }

        SECTION("operator!=(const Mat4 &m)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            REQUIRE(m != Mat4f(Vec3f(1.1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2.1, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3.1), Vec3f(4, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4.1, 5, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4, 5.1, 6), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4, 5, 6.1), Vec3f(7, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7.1, 8, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8.1, 9)));
            REQUIRE(m != Mat4f(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9.1)));
        }

        // Transformations

        SECTION("rotate(const Quat<Real> &q)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(const Vec3<Real>& axis, Real angle)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(Coord axis, Real angle)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotate(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6) * Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("translate(const Vec3<Real>& translation)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.translate(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.scale(Vec3f(10, 100, 1000));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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

        SECTION("transform(const Mat4& mat)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3).translate(Vec3f(1, 10, 100));
            Mat4f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6).translate(Vec3f(4, 5, 6));
            m.transform(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6).translate(Vec3f(4, 5, 6))
                * Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3).translate(Vec3f(1, 10, 100))
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }


        SECTION("rotatePre(const Quat<Real> &q)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Quatf::from(Vec3f::OneX, Constantsf::PI_OVER_6));
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(const Vec3<Real>& axis, Real angle)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Vec3f::OneX, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(Coord axis, Real angle)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3);
            m.rotatePre(Coord::X, Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3)
                * Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6)
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("translatePre(const Vec3<Real>& translation)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.translatePre(Vec3f(2, 3, 4));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9), Vec3f(10, 11, 12));
            m.scalePre(Vec3f(10, 100, 1000));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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

        SECTION("transformPre(const Mat34& mat)")
        {
            Mat4f m;
            m.set(Vec3f::OneZ, Constantsf::PI_OVER_3).translate(Vec3f(1, 10, 100));
            Mat4f a;
            a.set(Vec3f::OneX, Constantsf::PI_OVER_6).translate(Vec3f(4, 5, 6));
            m.transformPre(a);
            REQUIRE_THAT(m, Matches::WithinAbs(
                Mat4f::from(Vec3f::OneZ, Constantsf::PI_OVER_3).translate(Vec3f(1, 10, 100))
                * Mat4f::from(Vec3f::OneX, Constantsf::PI_OVER_6).translate(Vec3f(4, 5, 6))
            ));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("orthonormalise()")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
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
            Mat4f m(Vec4f(1, 2, 3, 4), Vec4f(5, 6, 7, 8), Vec4f(9, 10, 11, 12), Vec4f(13, 14, 15, 16));
            m.transpose();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
                    Vec4f(1, 5,  9, 13),
                    Vec4f(2, 6, 10, 14),
                    Vec4f(3, 7, 11, 15),
                    Vec4f(4, 8, 12, 16)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("invert()")
        {
            Mat4f m, im;

            m.set(Coord::X, Constantsf::PI_OVER_6).transformPre(Mat4f::from(Coord::Y, Constantsf::PI_OVER_3));
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat4f::One));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());

            m.set(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            im.set(m).invert();
            REQUIRE_THAT(m * im, Matches::WithinAbs(Mat4f::One));
            REQUIRE_THAT(im,
                Matches::WithinAbs(Mat4f(
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

        SECTION("transposed()")
        {
            Mat4f k(Vec4f(1, 2, 3, 4), Vec4f(5, 6, 7, 8), Vec4f(9, 10, 11, 12), Vec4f(13, 14, 15, 16));
            Mat4f m = k.transposed();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
                    Vec4f(1, 5, 9, 13),
                    Vec4f(2, 6, 10, 14),
                    Vec4f(3, 7, 11, 15),
                    Vec4f(4, 8, 12, 16)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("trace()")
        {
            Mat4f m(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            REQUIRE(m.trace() == 7.0f);
        }

        SECTION("determinant()")
        {
            Mat4f m(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            REQUIRE(m.determinant() == 295.0f);
        }

        SECTION("inversed()")
        {
            Mat4f k(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3));
            Mat4f m = k.inversed();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat4f(
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
            REQUIRE(Mat4f::One.isIdentity());
            REQUIRE(!Mat4f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).isIdentity());
            REQUIRE(!Mat4f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).isIdentity());
            REQUIRE(!Mat4f(1.1).isIdentity());
        }

        SECTION("isOrthonormal()")
        {
            REQUIRE(Mat4f::One.isOrthonormal());
            REQUIRE(Mat4f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).isOrthonormal());
            REQUIRE(!Mat4f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).isOrthonormal());
            REQUIRE(!Mat4f(1.1).isOrthonormal());
        }

        SECTION("normalError()")
        {
            REQUIRE(Mat4f::One.normalError() == 0.0f);
            REQUIRE(Mat4f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).normalError() == 0.0f);
            REQUIRE_THAT(Mat4f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).normalError(),
                Catch::Matchers::WithinAbs(27530.0f, 0.001f));
            REQUIRE_THAT(Mat4f(1.1).normalError(),
                Catch::Matchers::WithinAbs(0.1323f, 0.001f));
        }

        SECTION("orthogonalError()")
        {
            REQUIRE(Mat4f::One.orthogonalError() == 0.0f);
            REQUIRE(Mat4f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).orthogonalError() == 0.0f);
            REQUIRE_THAT(Mat4f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).orthogonalError(),
                Catch::Matchers::WithinAbs(16622.0f, 0.001f));
            REQUIRE(Mat4f(1.1).orthogonalError() == 0.0f);
        }

        SECTION("identityError()")
        {
            REQUIRE(Mat4f::One.identityError() == 0.0f);
            REQUIRE(Mat4f(Vec3f::OneZ, Vec3f::OneY, Vec3f::OneX).identityError() == 4.0f);
            REQUIRE_THAT(Mat4f(Vec3f(1, 7, 8), Vec3f(4, 2, 9), Vec3f(5, 6, 3)).identityError(),
                Catch::Matchers::WithinAbs(276.0f, 0.001f));
            REQUIRE_THAT(Mat4f(1.1).identityError(),
                Catch::Matchers::WithinAbs(0.03f, 0.001f));
        }

        SECTION("data()")
        {
            Mat4f m = Mat4f::One;
            const float* cdata = m.data();
            float* data = m.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[ 0] == 1.0f);
            REQUIRE(cdata[ 1] == 0.0f);
            REQUIRE(cdata[ 2] == 0.0f);
            REQUIRE(cdata[ 3] == 0.0f);
            REQUIRE(cdata[ 4] == 0.0f);
            REQUIRE(cdata[ 5] == 1.0f);
            REQUIRE(cdata[ 6] == 0.0f);
            REQUIRE(cdata[ 7] == 0.0f);
            REQUIRE(cdata[ 8] == 0.0f);
            REQUIRE(cdata[ 9] == 0.0f);
            REQUIRE(cdata[10] == 1.0f);
            REQUIRE(cdata[11] == 0.0f);
            REQUIRE(cdata[12] == 0.0f);
            REQUIRE(cdata[13] == 0.0f);
            REQUIRE(cdata[14] == 0.0f);
            REQUIRE(cdata[15] == 1.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(Mat4f::Zero.cast<double>() == Mat4d::Zero);
            REQUIRE(Mat4f::One.cast<double>() == Mat4d::One);

            REQUIRE(Mat4d::Zero.cast<float>() == Mat4f::Zero);
            REQUIRE(Mat4d::One.cast<float>() == Mat4f::One);
        }

        SECTION("transform(Vec3<Real>& dest, const Vec3<Real>& src)")
        {
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
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
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
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
            Mat4f m(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Vec3f d[6], v[6];
            v[0] = Vec3f::OneX;
            v[2] = Vec3f::OneY;
            v[4] = Vec3f::OneZ;
            m.transform(d, v, 3, 2*sizeof(Vec3f), 2*sizeof(Vec3f));
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec3f(1, 2, 3)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec3f(4, 5, 6)));
            REQUIRE_THAT(d[4], Matches::WithinAbs(Vec3f(7, 8, 9)));
        }

        SECTION("multiply(Mat4& dest, const Mat4& a, const Mat4& b)")
        {
            Mat4f a(Vec3f(1, 2, 3), Vec3f(4, 5, 6), Vec3f(7, 8, 9));
            Mat4f b(Vec3f(9, 8, 7), Vec3f(6, 5, 4), Vec3f(3, 2, 1));
            Mat4f m;
            Mat4f::multiply(m, a, b);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat4f(
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
