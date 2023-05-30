#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Vec4", "")
    {
        // Constants

        SECTION("Vec4f::Zero")
        {
            REQUIRE(Vec4f::Zero.x == 0.0f);
            REQUIRE(Vec4f::Zero.y == 0.0f);
            REQUIRE(Vec4f::Zero.z == 0.0f);
            REQUIRE(Vec4f::Zero.w == 0.0f);
        }

        SECTION("Vec4f::OneX")
        {
            REQUIRE(Vec4f::OneX.x == 1.0f);
            REQUIRE(Vec4f::OneX.y == 0.0f);
            REQUIRE(Vec4f::OneX.z == 0.0f);
            REQUIRE(Vec4f::OneX.w == 1.0f);
        }

        SECTION("Vec4f::OneY")
        {
            REQUIRE(Vec4f::OneY.x == 0.0f);
            REQUIRE(Vec4f::OneY.y == 1.0f);
            REQUIRE(Vec4f::OneY.z == 0.0f);
            REQUIRE(Vec4f::OneY.w == 1.0f);
        }

        SECTION("Vec4f::OneZ")
        {
            REQUIRE(Vec4f::OneZ.x == 0.0f);
            REQUIRE(Vec4f::OneZ.y == 0.0f);
            REQUIRE(Vec4f::OneZ.z == 1.0f);
            REQUIRE(Vec4f::OneZ.w == 1.0f);
        }

        SECTION("Vec4f::OneW")
        {
            REQUIRE(Vec4f::OneW.x == 0.0f);
            REQUIRE(Vec4f::OneW.y == 0.0f);
            REQUIRE(Vec4f::OneW.z == 0.0f);
            REQUIRE(Vec4f::OneW.w == 1.0f);
        }

        // Constructors

        SECTION("Vec4(Real k)")
        {
            Vec4f v(42);
            REQUIRE(v.x == 42.0f);
            REQUIRE(v.y == 42.0f);
            REQUIRE(v.z == 42.0f);
            REQUIRE(v.w == 42.0f);
        }

        SECTION("Vec4(Real x, Real y, Real z, Real w)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE(v.x == 1.0f);
            REQUIRE(v.y == 2.0f);
            REQUIRE(v.z == 3.0f);
            REQUIRE(v.w == 4.0f);
        }

        SECTION("Vec4(const Vec3<Real> &u, Real w)")
        {
            REQUIRE_THAT(Vec4f(Vec3f(1, 2, 3), 4), Matches::WithinAbs(Vec4f(1, 2, 3, 4)));
        }

        // Setters

        SECTION("set(Real x, Real y, Real z, Real w)")
        {
            Vec4f v;
            v.set(1, 2, 3, 4);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f(1, 2, 3, 4)));
        }

        SECTION("set(const Vec4& v)")
        {
            Vec4f v;
            v.set(Vec4f::OneX);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f::OneX));
            v.set(Vec4f::OneY);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f::OneY));
            v.set(Vec4f::OneZ);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f::OneZ));
            v.set(Vec4f::OneW);
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f::OneW));
            v.set(Vec4f(1, 2, 3, 4));
            REQUIRE_THAT(v, Matches::WithinAbs(Vec4f(1, 2, 3, 4)));
        }

        // Arithmetic operators

        SECTION("operator+ (const Vec4 &u)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE_THAT(v + Vec4f(10, 11, 12, 13), Matches::WithinAbs(Vec4f(11, 13, 15, 17)));
        }

        SECTION("operator- ()")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE_THAT(-v, Matches::WithinAbs(Vec4f(-1, -2, -3, -4)));
        }

        SECTION("operator+ (const Vec4 &u)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE_THAT(v - Vec4f(10, 11, 12, 13), Matches::WithinAbs(Vec4f(-9, -9, -9, -9)));
        }

        SECTION("operator* (const Vec4 &u)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE(v * Vec4f(10, 11, 12, 13) == 120);
        }

        SECTION("operator* (Real k)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE_THAT(v * 2, Matches::WithinAbs(Vec4f(2, 4, 6, 8)));
        }

        SECTION("operator/ (Real k)")
        {
            Vec4f v(1, 2, 3, 4);
            REQUIRE_THAT(v / 0.5f, Matches::WithinAbs(Vec4f(2, 4, 6, 8)));
        }

        //  Functions

        SECTION("toVec3()")
        {
            REQUIRE_THAT(Vec4f::Zero.toVec3(), Matches::WithinAbs(Vec3f::Zero));
            REQUIRE_THAT(Vec4f::OneX.toVec3(), Matches::WithinAbs(Vec3f::OneX));
            REQUIRE_THAT(Vec4f::OneY.toVec3(), Matches::WithinAbs(Vec3f::OneY));
            REQUIRE_THAT(Vec4f::OneZ.toVec3(), Matches::WithinAbs(Vec3f::OneZ));
            REQUIRE_THAT(Vec4f::OneW.toVec3(), Matches::WithinAbs(Vec3f::Zero));
        }

        SECTION("isNull()")
        {
            REQUIRE(Vec4f::Zero.isNull());
            REQUIRE(!Vec4f::OneX.isNull());
            REQUIRE(!Vec4f::OneY.isNull());
            REQUIRE(!Vec4f::OneZ.isNull());
            REQUIRE(!Vec4f::OneW.isNull());
            REQUIRE(!Vec4f(2, 2, 2, 2).isNull());
        }

        SECTION("data()")
        {
            Vec4f v = Vec4f::OneX;
            const float* cdata = v.data();
            float* data = v.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[0] == 1.0f);
            REQUIRE(cdata[1] == 0.0f);
            REQUIRE(cdata[2] == 0.0f);
            REQUIRE(cdata[3] == 1.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(Vec4f::Zero.cast<double>() == Vec4d::Zero);
            REQUIRE(Vec4f::OneX.cast<double>() == Vec4d::OneX);
            REQUIRE(Vec4f::OneY.cast<double>() == Vec4d::OneY);
            REQUIRE(Vec4f::OneZ.cast<double>() == Vec4d::OneZ);
            REQUIRE(Vec4f::OneW.cast<double>() == Vec4d::OneW);

            REQUIRE(Vec4d::Zero.cast<float>() == Vec4f::Zero);
            REQUIRE(Vec4d::OneX.cast<float>() == Vec4f::OneX);
            REQUIRE(Vec4d::OneY.cast<float>() == Vec4f::OneY);
            REQUIRE(Vec4d::OneZ.cast<float>() == Vec4f::OneZ);
            REQUIRE(Vec4d::OneW.cast<float>() == Vec4f::OneW);
        }
    }
}
