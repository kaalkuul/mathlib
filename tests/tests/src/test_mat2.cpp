#include "utils.h"

namespace
{
    using namespace mathlib;

    TEST_CASE("Mat2", "")
    {
        // Constants

        SECTION("Mat2f::Zero")
        {
            REQUIRE(Mat2f::Zero.x == Vec2f::Zero);
            REQUIRE(Mat2f::Zero.y == Vec2f::Zero);
            REQUIRE(Mat2f::Zero.isInitialized());
            REQUIRE(!Mat2f::Zero.isNormal());
            REQUIRE(Mat2f::Zero.isOrthogonal());
            REQUIRE(!Mat2f::Zero.isOrthonormal());
            REQUIRE(!Mat2f::Zero.isIdentity());
        }

        SECTION("Mat2f::One")
        {
            REQUIRE(Mat2f::One.x == Vec2f::OneX);
            REQUIRE(Mat2f::One.y == Vec2f::OneY);
            REQUIRE(Mat2f::One.isInitialized());
            REQUIRE(Mat2f::One.isNormal());
            REQUIRE(Mat2f::One.isOrthogonal());
            REQUIRE(Mat2f::One.isOrthonormal());
            REQUIRE(Mat2f::One.isIdentity());
        }

        // Constructors

        SECTION("Mat2(Real k)")
        {
            Mat2f m(3);
            REQUIRE(m.x == Vec2f(3, 0));
            REQUIRE(m.y == Vec2f(0, 3));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("Mat2(const Vec2<Real> &u, const Vec2<Real> &v)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            REQUIRE(m.x == Vec2f(1, 2));
            REQUIRE(m.y == Vec2f(4, 5));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Setters

        SECTION("setIdentity()")
        {
            Mat2f m(3);
            m.setIdentity();
            REQUIRE(m == Mat2f::One);
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isIdentity());
        }

        SECTION("set(const Mat2<Real>& m)")
        {
            Mat2f m(3);
            Mat2f a(42);
            m.set(a);
            REQUIRE(m == a);
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(const Vec2<Real> &x, const Vec2<Real> &y)")
        {
            Mat2f m(3);
            m.set(Vec2f(1, 2), Vec2f(4, 5));
            REQUIRE_THAT(m.scaled(Vec2f(2, 3)),
                Matches::WithinAbs(Mat2f(
                    Vec2f(2, 4),
                    Vec2f(12, 15)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("set(Real angle)")
        {
            Mat2f m(3);
            m.set(Constantsf::PI_OVER_4);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(CPI4, SPI4),
                Vec2f(-SPI4, CPI4)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("slerp(const Mat2 &a, const Mat2 &b, Real weight)")
        {
            Mat2f a = Mat2f::One;
            Mat2f b = Mat2f::from(Constantsf::PI_OVER_3);
            Mat2f expect = Mat2f::from(Constantsf::PI_OVER_6);
            Mat2f m0, mdot5, m1;
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

        SECTION("slerpMaxAngle(const Mat2 &a, const Mat2 &b, Real maxAngle)")
        {
            Mat2f a = Mat2f::One;
            Mat2f b = Mat2f::from(Constantsf::PI_OVER_3);
            Mat2f expect = Mat2f::from(Constantsf::PI_OVER_8);
            Quatf qe = Quatf::from(Constantsf::PI_OVER_8);
            Mat2f m0, actual, m1;
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

        // Assignments

        SECTION("operator*=(Real k)")
        {
            Mat2f m = Mat2f::One;
            m *= 42.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(42.0f)));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*=(const Mat2 &m)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f a(Vec2f(9, 8), Vec2f(6, 5));
            m *= a;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(41, 58),
                Vec2f(26, 37)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator/=(Real k)")
        {
            Mat2f m(Vec2f(10, 10), Vec2f(10, 10));
            m /= 5.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(2, 2),
                Vec2f(2, 2)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator-()")
        {
            Mat2f k(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f m = -k;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(-1, -2),
                Vec2f(-4, -5)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Mat2 &m)")
        {
            Mat2f a(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f b(Vec2f(9, 8), Vec2f(6, 5));
            Mat2f m = a * b;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(41, 58), 
                Vec2f(26, 37)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(Real k)")
        {
            Mat2f k(Vec2f(10, 10), Vec2f(10, 10));
            Mat2f m = k * 0.2f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(2, 2),
                Vec2f(2, 2)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("operator*(const Vec2<Real> &u)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            REQUIRE_THAT(m * Vec2f::OneX, Matches::WithinAbs(Vec2f(1, 2)));
            REQUIRE_THAT(m * Vec2f::OneY, Matches::WithinAbs(Vec2f(4, 5)));
        }

        SECTION("operator/(Real k)")
        {
            Mat2f k(Vec2f(10, 10), Vec2f(10, 10));
            Mat2f m = k / 5.0f;
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(2, 2),
                Vec2f(2, 2)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Comparison operators

        SECTION("operator==(const Mat2 &m)")
        {
            Mat2f a(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f b;
            b.x = Vec2f(1, 2);
            b.y = Vec2f(4, 5);
            REQUIRE(a == a);
            REQUIRE(a == b);
        }

        SECTION("operator!=(const Mat2 &m)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            REQUIRE(m != Mat2f(Vec2f(1.1, 2), Vec2f(4, 5)));
            REQUIRE(m != Mat2f(Vec2f(1, 2.1), Vec2f(4, 5)));
            REQUIRE(m != Mat2f(Vec2f(1, 2), Vec2f(4.1, 5)));
            REQUIRE(m != Mat2f(Vec2f(1, 2), Vec2f(4, 5.1)));
        }

        // Transformations

        SECTION("scale(const Vec2<Real>& coefficients)")
        {
            Mat2f m(Vec2f(10, 10), Vec2f(10, 10));
            m.scale(Vec2f(2, 3));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat2f(
                    Vec2f(20, 20),
                    Vec2f(30, 30)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transpose()")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            m.transpose();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat2f(
                    Vec2f(1, 4),
                    Vec2f(2, 5)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotate(Coord coord, Real angle)")
        {
            Mat2f m;
            m.set(Constantsf::PI_OVER_3);
            m.rotate(Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f::from(Constantsf::PI_OVER_6) * Mat2f::from(Constantsf::PI_OVER_3)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("rotatePre(Coord coord, Real angle)")
        {
            Mat2f m;
            m.set(Constantsf::PI_OVER_3);
            m.rotatePre(Constantsf::PI_OVER_6);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f::from(Constantsf::PI_OVER_3) * Mat2f::from(Constantsf::PI_OVER_6)));
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("orthonormalise()")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            m.orthonormalise();
            REQUIRE(m.isOrthonormal());
            REQUIRE(m.isInitialized());
            REQUIRE(m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        // Funtions

        SECTION("scaled()")
        {
            Mat2f k(Vec2f(10, 10), Vec2f(10, 10));
            Mat2f m = k.scaled(Vec2f(2, 3));
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat2f(
                    Vec2f(20, 20),
                    Vec2f(30, 30)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("transposed()")
        {
            Mat2f k(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f m = k.transposed();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(1, 4),
                Vec2f(2, 5)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("cofactors()")
        {
            Mat2f k(Vec2f(1, 7), Vec2f(4, 2));
            Mat2f m = k.cofactors();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(2, -4),
                Vec2f(-7, 1)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("adjoint()")
        {
            Mat2f k(Vec2f(1, 7), Vec2f(4, 2));
            Mat2f m = k.adjoint();
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(2, -7),
                Vec2f(-4, 1)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("trace()")
        {
            Mat2f m(Vec2f(1, 7), Vec2f(4, 2));
            REQUIRE(m.trace() == 3.0f);
        }

        SECTION("determinant()")
        {
            Mat2f m(Vec2f(1, 7), Vec2f(4, 2));
            REQUIRE(m.determinant() == -26.0f);
        }

        SECTION("inversed()")
        {
            Mat2f k(Vec2f(1, 7), Vec2f(4, 2));
            Mat2f m = k.inversed();
            REQUIRE_THAT(m,
                Matches::WithinAbs(Mat2f(
                    Vec2f(-2 / 26.0f,  7 / 26.0f),
                    Vec2f( 4 / 26.0f, -1 / 26.0f)
                )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }

        SECTION("isIdentity()")
        {
            REQUIRE(Mat2f::One.isIdentity());
            REQUIRE(!Mat2f(Vec2f::OneY, Vec2f::OneX).isIdentity());
            REQUIRE(!Mat2f(Vec2f(1, 7), Vec2f(4, 2)).isIdentity());
            REQUIRE(!Mat2f(1.1).isIdentity());
        }

        SECTION("isOrthonormal()")
        {
            REQUIRE(Mat2f::One.isOrthonormal());
            REQUIRE(Mat2f(Vec2f::OneY, Vec2f::OneX).isOrthonormal());
            REQUIRE(!Mat2f(Vec2f(1, 7), Vec2f(4, 2)).isOrthonormal());
            REQUIRE(!Mat2f(1.1).isOrthonormal());
        }

        SECTION("normalError()")
        {
            REQUIRE(Mat2f::One.normalError() == 0.0f);
            REQUIRE(Mat2f(Vec2f::OneY, Vec2f::OneX).normalError() == 0.0f);
            REQUIRE_THAT(Mat2f(Vec2f(1, 7), Vec2f(4, 2)).normalError(),
                Catch::Matchers::WithinAbs(2762.0f, 0.001f));
            REQUIRE_THAT(Mat2f(1.1).normalError(),
                Catch::Matchers::WithinAbs(0.0882f, 0.001f));
        }

        SECTION("orthogonalError()")
        {
            REQUIRE(Mat2f::One.orthogonalError() == 0.0f);
            REQUIRE(Mat2f(Vec2f::OneY, Vec2f::OneX).orthogonalError() == 0.0f);
            REQUIRE_THAT(Mat2f(Vec2f(1, 7), Vec2f(4, 2)).orthogonalError(),
                Catch::Matchers::WithinAbs(324.0f, 0.001f));
            REQUIRE(Mat2f(1.1).orthogonalError() == 0.0f);
        }

        SECTION("identityError()")
        {
            REQUIRE(Mat2f::One.identityError() == 0.0f);
            REQUIRE(Mat2f(Vec2f::OneY, Vec2f::OneX).identityError() == 4.0f);
            REQUIRE_THAT(Mat2f(Vec2f(1, 7), Vec2f(4, 2)).identityError(),
                Catch::Matchers::WithinAbs(66.0f, 0.001f));
            REQUIRE_THAT(Mat2f(1.1).identityError(),
                Catch::Matchers::WithinAbs(0.02f, 0.001f));
        }

        SECTION("cast()")
        {
            REQUIRE(Mat2f::Zero.cast<double>() == Mat2d::Zero);
            REQUIRE(Mat2f::One.cast<double>() == Mat2d::One);

            REQUIRE(Mat2d::Zero.cast<float>() == Mat2f::Zero);
            REQUIRE(Mat2d::One.cast<float>() == Mat2f::One);
        }

        SECTION("transform(Vec2<Real>& dest, const Vec2<Real>& src)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            Vec2f v;
            m.transform(v, Vec2f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(1, 2)));
            m.transform(v, Vec2f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec2f(4, 5)));
        }

        SECTION("transform(Vec2<Real>* dest, const Vec2<Real>* src, size_t count)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            Vec2f d[3], v[3];
            v[0] = Vec2f::OneX;
            v[1] = Vec2f::OneY;
            v[2] = Vec2f(1, 1);
            m.transform(d, v, 3);
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec2f(1, 2)));
            REQUIRE_THAT(d[1], Matches::WithinAbs(Vec2f(4, 5)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec2f(5, 7)));
        }

        SECTION("transform(Vec3<Real>* dest, const Vec3<Real>* src, size_t count, size_t destStride, size_t srcStride)")
        {
            Mat2f m(Vec2f(1, 2), Vec2f(4, 5));
            Vec2f d[6], v[6];
            v[0] = Vec2f::OneX;
            v[2] = Vec2f::OneY;
            v[4] = Vec2f(1, 1);
            m.transform(d, v, 3, 2 * sizeof(Vec2f), 2 * sizeof(Vec2f));
            REQUIRE_THAT(d[0], Matches::WithinAbs(Vec2f(1, 2)));
            REQUIRE_THAT(d[2], Matches::WithinAbs(Vec2f(4, 5)));
            REQUIRE_THAT(d[4], Matches::WithinAbs(Vec2f(5, 7)));
        }

        SECTION("multiply(Mat2& dest, const Mat2& a, const Mat2& b)")
        {
            Mat2f a(Vec2f(1, 2), Vec2f(4, 5));
            Mat2f b(Vec2f(9, 8), Vec2f(6, 5));
            Mat2f m;
            Mat2f::multiply(m, a, b);
            REQUIRE_THAT(m, Matches::WithinAbs(Mat2f(
                Vec2f(41, 58),
                Vec2f(26, 37)
            )));
            REQUIRE(m.isInitialized());
            REQUIRE(!m.isNormal());
            REQUIRE(!m.isOrthogonal());
            REQUIRE(!m.isOrthonormal());
            REQUIRE(!m.isIdentity());
        }
    }
}
