#include "utils.h"

using namespace mathlib;

TEST_CASE("Line2", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(Line2f::Real) == sizeof(float));
        REQUIRE(sizeof(Line2d::Real) == sizeof(double));
    }

    // Create from

    SECTION("from(const Vec2<Real>& start, const Vec2<Real>& end)")
    {
        Line2f line;

        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE(line.start == Vec2f::Zero);
        REQUIRE(line.end == Vec2f::OneX);

        line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE(line.start == Vec2f::OneX);
        REQUIRE(line.end == Vec2f::OneY);
    }

    // Comparison operators

    SECTION("operator== (const Line2 &rhs)")
    {
        Line2f line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE(line == line);
        REQUIRE(line == Line2f::from(Vec2f::Zero, Vec2f::OneX));
    }

    SECTION("operator!= (const Line2 &rhs)")
    {
        Line2f line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE(!(line != line));
        REQUIRE(line != Line2f::from(Vec2f::Zero, Vec2f::Zero));
    }

    //  Functions

    SECTION("length()")
    {
        Line2f line;
        
        line = Line2f::from(Vec2f::OneX, Vec2f::OneX);
        REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneY);
        REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(sqrt(2.0f), 1e-6));
    }

    SECTION("lengthSqr()")
    {
        Line2f line;

        line = Line2f::from(Vec2f::OneX, Vec2f::OneX);
        REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneY);
        REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(2.0f, 1e-6));
    }

    SECTION("isNull()")
    {
        Line2f line;

        line = Line2f::from(Vec2f::OneX, Vec2f::OneX);
        REQUIRE(line.isNull());
        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE(!line.isNull());
        line = Line2f::from(Vec2f::Zero, Vec2f::OneY);
        REQUIRE(!line.isNull());
        line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE(!line.isNull());
    }

    SECTION("pointAt(Real t)")
    {
        Line2f line;

        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE_THAT(line.pointAt(0.0f), Matches::WithinAbs(Vec2f::Zero, 1e-10));
        REQUIRE_THAT(line.pointAt(1.0f), Matches::WithinAbs(Vec2f::OneX, 1e-10));
        REQUIRE_THAT(line.pointAt(0.5f), Matches::WithinAbs(Vec2f::OneX * 0.5f, 1e-10));

        line = Line2f::from(Vec2f::Zero, Vec2f::OneY);
        REQUIRE_THAT(line.pointAt(0.0f), Matches::WithinAbs(Vec2f::Zero, 1e-10));
        REQUIRE_THAT(line.pointAt(1.0f), Matches::WithinAbs(Vec2f::OneY, 1e-10));
        REQUIRE_THAT(line.pointAt(0.5f), Matches::WithinAbs(Vec2f::OneY * 0.5f, 1e-10));
    }

    SECTION("distance(const Vec2<Real>& point)")
    {
        Line2f line;

        line = Line2f::from(Vec2f::OneX, Vec2f::OneX);
        REQUIRE_THAT(line.distance(Vec2f::Zero), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneX);
        REQUIRE_THAT(line.distance(Vec2f(10.0f, 3.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
        line = Line2f::from(Vec2f::Zero, Vec2f::OneY);
        REQUIRE_THAT(line.distance(Vec2f(3.0f, 10.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
        line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE_THAT(line.distance(Vec2f::Zero), Catch::Matchers::WithinAbs(sqrt(2.0f)/2.0f, 1e-6));
    }

    SECTION("cast()")
    {
        REQUIRE(Line2f::from(Vec2f::Zero, Vec2f::Zero).cast<double>() == Line2d::from(Vec2d::Zero, Vec2d::Zero));
        REQUIRE(Line2f::from(Vec2f::Zero, Vec2f::OneX).cast<double>() == Line2d::from(Vec2d::Zero, Vec2d::OneX));
        REQUIRE(Line2f::from(Vec2f::Zero, Vec2f::OneY).cast<double>() == Line2d::from(Vec2d::Zero, Vec2d::OneY));

        REQUIRE(Line2d::from(Vec2d::Zero, Vec2d::Zero).cast<float>() == Line2f::from(Vec2f::Zero, Vec2f::Zero));
        REQUIRE(Line2d::from(Vec2d::Zero, Vec2d::OneX).cast<float>() == Line2f::from(Vec2f::Zero, Vec2f::OneX));
        REQUIRE(Line2d::from(Vec2d::Zero, Vec2d::OneY).cast<float>() == Line2f::from(Vec2f::Zero, Vec2f::OneY));
    }
    
    SECTION("Matches::WithinAbs")
    {
        Line2f line = Line2f::from(Vec2f::OneX, Vec2f::OneY);
        REQUIRE_THAT(line, Matches::WithinAbs(line));
    }
}
