#include "utils.h"

using namespace mathlib;

TEST_CASE("Tri2", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(Tri2f::Real) == sizeof(float));
        REQUIRE(sizeof(Tri2d::Real) == sizeof(double));
    }

    // Create from

    SECTION("from(const Vec2<Real>& a, const Vec2<Real>& b, const Vec2<Real>& c)")
    {
        Tri2f tri;

        tri = Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY);
        REQUIRE(tri.a == Vec2f::Zero);
        REQUIRE(tri.b == Vec2f::OneX);
        REQUIRE(tri.c == Vec2f::OneY);
    }

    // Comparison operators

    SECTION("operator== (const Tri2 &rhs)")
    {
        Tri2f tri = Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY);
        REQUIRE(tri == tri);
        REQUIRE(tri == Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY));
    }

    SECTION("operator!= (const Tri2 &rhs)")
    {
        Tri2f tri = Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY);
        REQUIRE(!(tri != tri));
        REQUIRE(tri != Tri2f::from(Vec2f::Zero, Vec2f::Zero, Vec2f::Zero));
    }

    //  Functions

    SECTION("contains(const Vec2<Real>& point)")
    {
        Tri2f tri;

        tri = Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY);
        REQUIRE(tri.contains(Vec2f::Zero));
        REQUIRE(tri.contains(Vec2f::OneX));
        REQUIRE(tri.contains(Vec2f::OneY));
        REQUIRE(tri.contains(Vec2f(0.99f, 0.0f)));
        REQUIRE(tri.contains(Vec2f(0.0f, 0.99f)));
        REQUIRE(tri.contains(Vec2f(0.5f, 0.5f)));

        REQUIRE(!tri.contains(Vec2f(1.01f, 0.0f)));
        REQUIRE(!tri.contains(Vec2f(0.0f, 1.01f)));
        REQUIRE(!tri.contains(Vec2f(-0.01f, 0.0f)));
        REQUIRE(!tri.contains(Vec2f(0.0f, -0.01f)));
        REQUIRE(!tri.contains(Vec2f(-0.01f, -0.01f)));
        REQUIRE(!tri.contains(Vec2f(10.0f, 3.0f)));
    }

    SECTION("cast()")
    {
        REQUIRE(Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY).cast<double>() == Tri2d::from(Vec2d::Zero, Vec2d::OneX, Vec2d::OneY));

        REQUIRE(Tri2d::from(Vec2d::Zero, Vec2d::OneX, Vec2d::OneY).cast<float>() == Tri2f::from(Vec2f::Zero, Vec2f::OneX, Vec2f::OneY));
    }
}
