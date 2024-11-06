#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Line3", "")
    {
        // Types

        SECTION("Real")
        {
            REQUIRE(sizeof(Line3f::Real) == sizeof(float));
            REQUIRE(sizeof(Line3d::Real) == sizeof(double));
        }

        // Create from

        SECTION("from(const Vec3<Real>& start, const Vec3<Real>& end)")
        {
            Line3f line;

            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(line.start == Vec3f::Zero);
            REQUIRE(line.end == Vec3f::OneX);

            line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE(line.start == Vec3f::OneX);
            REQUIRE(line.end == Vec3f::OneY);
        }

        // Comparison operators

        SECTION("operator== (const Line3 &rhs)")
        {
            Line3f line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(line == line);
            REQUIRE(line == Line3f::from(Vec3f::Zero, Vec3f::OneX));
        }

        SECTION("operator!= (const Line3 &rhs)")
        {
            Line3f line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(!(line != line));
            REQUIRE(line != Line3f::from(Vec3f::Zero, Vec3f::Zero));
        }

        //  Functions

        SECTION("length()")
        {
            Line3f line;
            
            line = Line3f::from(Vec3f::OneX, Vec3f::OneX);
            REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE_THAT(line.length(), Catch::Matchers::WithinAbs(sqrt(2.0f), 1e-6));
        }

        SECTION("lengthSqr()")
        {
            Line3f line;

            line = Line3f::from(Vec3f::OneX, Vec3f::OneX);
            REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(0.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE_THAT(line.lengthSqr(), Catch::Matchers::WithinAbs(2.0f, 1e-6));
        }

        SECTION("isNull()")
        {
            Line3f line;

            line = Line3f::from(Vec3f::OneX, Vec3f::OneX);
            REQUIRE(line.isNull());
            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE(!line.isNull());
            line = Line3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE(!line.isNull());
            line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE(!line.isNull());
        }

        SECTION("pointAt(Real t)")
        {
            Line3f line;

            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(line.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(line.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneX, 1e-10));
            REQUIRE_THAT(line.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneX * 0.5f, 1e-10));

            line = Line3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(line.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(line.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneY, 1e-10));
            REQUIRE_THAT(line.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneY * 0.5f, 1e-10));

            line = Line3f::from(Vec3f::Zero, Vec3f::OneZ);
            REQUIRE_THAT(line.pointAt(0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(line.pointAt(1.0f), Matches::WithinAbs(Vec3f::OneZ, 1e-10));
            REQUIRE_THAT(line.pointAt(0.5f), Matches::WithinAbs(Vec3f::OneZ * 0.5f, 1e-10));
        }

        SECTION("distance(const Vec3<Real>& point)")
        {
            Line3f line;

            line = Line3f::from(Vec3f::OneX, Vec3f::OneX);
            REQUIRE_THAT(line.distance(Vec3f::Zero), Catch::Matchers::WithinAbs(1.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneX);
            REQUIRE_THAT(line.distance(Vec3f(10.0f, 3.0f, 0.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            line = Line3f::from(Vec3f::Zero, Vec3f::OneY);
            REQUIRE_THAT(line.distance(Vec3f(3.0f, 10.0f, 0.0f)), Catch::Matchers::WithinAbs(3.0f, 1e-10));
            line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE_THAT(line.distance(Vec3f::Zero), Catch::Matchers::WithinAbs(sqrt(2.0f) / 2.0f, 1e-6));
        }

        SECTION("cast()")
        {
            REQUIRE(Line3f::from(Vec3f::Zero, Vec3f::Zero).cast<double>() == Line3d::from(Vec3d::Zero, Vec3d::Zero));
            REQUIRE(Line3f::from(Vec3f::Zero, Vec3f::OneX).cast<double>() == Line3d::from(Vec3d::Zero, Vec3d::OneX));
            REQUIRE(Line3f::from(Vec3f::Zero, Vec3f::OneY).cast<double>() == Line3d::from(Vec3d::Zero, Vec3d::OneY));

            REQUIRE(Line3d::from(Vec3d::Zero, Vec3d::Zero).cast<float>() == Line3f::from(Vec3f::Zero, Vec3f::Zero));
            REQUIRE(Line3d::from(Vec3d::Zero, Vec3d::OneX).cast<float>() == Line3f::from(Vec3f::Zero, Vec3f::OneX));
            REQUIRE(Line3d::from(Vec3d::Zero, Vec3d::OneY).cast<float>() == Line3f::from(Vec3f::Zero, Vec3f::OneY));
        }
        
        SECTION("Matches::WithinAbs")
        {
            Line3f line = Line3f::from(Vec3f::OneX, Vec3f::OneY);
            REQUIRE_THAT(line, Matches::WithinAbs(line));
        }
    }
}
