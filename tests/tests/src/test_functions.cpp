#include "utils.h"

using namespace mathlib;

TEST_CASE("Functions", "")
{
    SECTION("next")
    {
        REQUIRE(next(Coord::X) == Coord::Y);
        REQUIRE(next(Coord::Y) == Coord::Z);
        REQUIRE(next(Coord::Z) == Coord::X);
        REQUIRE(next(Coord::Undefined) == Coord::Undefined);
    }
    
    SECTION("degreeToRadian")
    {
        REQUIRE(degreeToRadian(0.0) == 0.0);
        REQUIRE(degreeToRadian(180.0) == Constantsd::PI);
    }

    SECTION("radianToDegree")
    {
        REQUIRE(radianToDegree(0.0) == 0.0);
        REQUIRE(radianToDegree(Constantsd::PI) == 180.0);
    }

    SECTION("asin")
    {
        REQUIRE_THAT(asin(0.0), Catch::Matchers::WithinAbs(0.0, 0.0));
        REQUIRE_THAT(asin(1.0), Catch::Matchers::WithinAbs(Constantsd::PI_OVER_2, 1e-10));
        REQUIRE_THAT(asin(-1.0), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
    }

    SECTION("acos")
    {
        REQUIRE_THAT(acos(0.0), Catch::Matchers::WithinAbs(Constantsd::PI_OVER_2, 1e-10));
        REQUIRE_THAT(acos(1.0), Catch::Matchers::WithinAbs(0.0, 0.0));
        REQUIRE_THAT(acos(-1.0), Catch::Matchers::WithinAbs(Constantsd::PI, 1e-10));
    }

    SECTION("rand(int n)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            int value = rand(10);
            REQUIRE(value >= 0);
            REQUIRE(value < 10);
        }
    }

    SECTION("randBetween(int from, int to)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            int value = randBetween(10, 20);
            REQUIRE(value >= 10);
            REQUIRE(value < 20);
        }
    }

    SECTION("randAmplitude(int n)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            int value = randAmplitude(10);
            REQUIRE(value >= -10);
            REQUIRE(value < 10);
        }
    }

    SECTION("randAmplitude(int from, int to)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            int value = randAmplitude(10, 20);
            if (value >= 0)
            {
                REQUIRE(value >= 10);
                REQUIRE(value < 20);
            }
            else
            {
                REQUIRE(value >= -20);
                REQUIRE(value < -10);
            }
        }
    }

    SECTION("rand(double n)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            double value = rand(10.0);
            REQUIRE(value >= 0.0);
            REQUIRE(value < 10.0);
        }
    }

    SECTION("randBetween(double from, double to)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            double value = randBetween(10.0, 20.0);
            REQUIRE(value >= 10.0);
            REQUIRE(value < 20.0);
        }
    }

    SECTION("randAmplitude(double n)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            double value = randAmplitude(10.0);
            REQUIRE(value >= -10.0);
            REQUIRE(value < 10.0);
        }
    }

    SECTION("randAmplitude(double from, double to)")
    {
        for (int i = 0; i < N_TEST_RUNS; i++)
        {
            double value = randAmplitude(10, 20);
            if (value >= 0.0)
            {
                REQUIRE(value >= 10.0);
                REQUIRE(value < 20.0);
            }
            else
            {
                REQUIRE(value >= -20.0);
                REQUIRE(value < -10.0);
            }
        }
    }

    SECTION("fmod")
    {
        REQUIRE(fmod(0.0, 10.0) == 0.0);
        REQUIRE(fmod(5.0, 10.0) == 5.0);
        REQUIRE(fmod(10.0, 10.0) == 0.0);
        REQUIRE(fmod(15.0, 10.0) == 5.0);
        REQUIRE(fmod(-5.0, 10.0) == -5.0);
        REQUIRE(fmod(-10.0, 10.0) == 0.0);
        REQUIRE(fmod(-15.0, 10.0) == -5.0);
    }

    SECTION("fmodPositive")
    {
        REQUIRE(fmodPositive(0.0, 10.0) == 0.0);
        REQUIRE(fmodPositive(5.0, 10.0) == 5.0);
        REQUIRE(fmodPositive(10.0, 10.0) == 0.0);
        REQUIRE(fmodPositive(15.0, 10.0) == 5.0);
        REQUIRE(fmodPositive(-5.0, 10.0) == 5.0);
        REQUIRE(fmodPositive(-10.0, 10.0) == 0.0);
        REQUIRE(fmodPositive(-15.0, 10.0) == 5.0);
    }

    SECTION("fmodCentered")
    {
        REQUIRE(fmodCentered(0.0, 10.0) == 0.0);
        REQUIRE(fmodCentered(5.0, 10.0) == -5.0);
        REQUIRE(fmodCentered(10.0, 10.0) == 0.0);
        REQUIRE(fmodCentered(15.0, 10.0) == -5.0);
        REQUIRE(fmodCentered(-5.0, 10.0) == -5.0);
        REQUIRE(fmodCentered(-10.0, 10.0) == 0.0);
        REQUIRE(fmodCentered(-15.0, 10.0) == -5.0);
    }

    SECTION("distance(Vec2 a, Vec2 b)")
    {
        REQUIRE(distance(Vec2d::Zero, Vec2d::Zero) == 0.0);
        REQUIRE(distance(Vec2d::Zero, Vec2d::OneX) == 1.0);
        REQUIRE(distance(Vec2d::Zero, Vec2d::OneX * 2) == 2.0);
        REQUIRE_THAT(distance(Vec2d::OneX, Vec2d::OneY),
            Catch::Matchers::WithinAbs(1.4142135624, 1e-10));
    }

    SECTION("distanceSqr(Vec2 a, Vec2 b)")
    {
        REQUIRE(distanceSqr(Vec2d::Zero, Vec2d::Zero) == 0.0);
        REQUIRE(distanceSqr(Vec2d::Zero, Vec2d::OneX) == 1.0);
        REQUIRE(distanceSqr(Vec2d::Zero, Vec2d::OneX * 2) == 4.0);
        REQUIRE(distanceSqr(Vec2d::OneX, Vec2d::OneY) == 2.0);
    }

    SECTION("distance(Vec3 a, Vec3 b)")
    {
        REQUIRE(distance(Vec3d::Zero, Vec3d::Zero) == 0.0);
        REQUIRE(distance(Vec3d::Zero, Vec3d::OneX) == 1.0);
        REQUIRE(distance(Vec3d::Zero, Vec3d::OneX * 2) == 2.0);
        REQUIRE_THAT(distance(Vec3d::OneX, Vec3d::OneY),
            Catch::Matchers::WithinAbs(1.4142135624, 1e-10));
        REQUIRE_THAT(distance(Vec3d::OneX, Vec3d::OneZ),
            Catch::Matchers::WithinAbs(1.4142135624, 1e-10));
        REQUIRE_THAT(distance(Vec3d::OneY, Vec3d::OneZ),
            Catch::Matchers::WithinAbs(1.4142135624, 1e-10));
    }

    SECTION("distanceSqr(Vec3 a, Vec3 b)")
    {
        REQUIRE(distanceSqr(Vec3d::Zero, Vec3d::Zero) == 0.0);
        REQUIRE(distanceSqr(Vec3d::Zero, Vec3d::OneX) == 1.0);
        REQUIRE(distanceSqr(Vec3d::Zero, Vec3d::OneX * 2) == 4.0);
        REQUIRE(distanceSqr(Vec3d::OneX, Vec3d::OneY) == 2.0);
        REQUIRE(distanceSqr(Vec3d::OneX, Vec3d::OneZ) == 2.0);
        REQUIRE(distanceSqr(Vec3d::OneY, Vec3d::OneZ) == 2.0);
    }

    SECTION("min(int a, int b)")
    {
        REQUIRE(min(-10, -20) == -20);
        REQUIRE(min(-20, -10) == -20);
        REQUIRE(min(0, 0) == 0);
        REQUIRE(min(10, 20) == 10);
        REQUIRE(min(20, 10) == 10);
    }

    SECTION("min(double a, double b)")
    {
        REQUIRE(min(-10.0, -20.0) == -20.0);
        REQUIRE(min(-20.0, -10.0) == -20.0);
        REQUIRE(min(0.0, 0.0) == 0.0);
        REQUIRE(min(10.0, 20.0) == 10.0);
        REQUIRE(min(20.0, 10.0) == 10.0);
    }

    SECTION("max(int a, int b)")
    {
        REQUIRE(max(-10, -20) == -10);
        REQUIRE(max(-20, -10) == -10);
        REQUIRE(max(0, 0) == 0);
        REQUIRE(max(10, 20) == 20);
        REQUIRE(max(20, 10) == 20);
    }

    SECTION("max(double a, double b)")
    {
        REQUIRE(max(-10.0, -20.0) == -10.0);
        REQUIRE(max(-20.0, -10.0) == -10.0);
        REQUIRE(max(0.0, 0.0) == 0.0);
        REQUIRE(max(10.0, 20.0) == 20.0);
        REQUIRE(max(20.0, 10.0) == 20.0);
    }

    SECTION("clippedBetween(int value, int a, int b)")
    {
        REQUIRE(clippedBetween(9, 10, 20) == 10);
        REQUIRE(clippedBetween(10, 10, 20) == 10);
        REQUIRE(clippedBetween(15, 10, 20) == 15);
        REQUIRE(clippedBetween(20, 10, 20) == 20);
        REQUIRE(clippedBetween(21, 10, 20) == 20);
    }

    SECTION("clippedBetween(double value, double a, double b)")
    {
        REQUIRE(clippedBetween( 9.0, 10.0, 20.0) == 10.0);
        REQUIRE(clippedBetween(10.0, 10.0, 20.0) == 10.0);
        REQUIRE(clippedBetween(15.0, 10.0, 20.0) == 15.0);
        REQUIRE(clippedBetween(20.0, 10.0, 20.0) == 20.0);
        REQUIRE(clippedBetween(21.0, 10.0, 20.0) == 20.0);
    }

    SECTION("evaluate(double value, double threshold, Zero)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Zero) == 0.0);
        REQUIRE(evaluate(0.5, 0.0, ResponseCurveType::Zero) == 0.0);
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Zero) == 0.0);
    }

    SECTION("evaluate(double value, double threshold, Linear)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Linear) == 0.0);
        REQUIRE(evaluate(0.5, 0.0, ResponseCurveType::Linear) == 0.5);
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Linear) == 1.0);
    }

    SECTION("evaluate(double value, double threshold, Parabolic)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Parabolic) == 0.0);
        REQUIRE(evaluate(0.5, 0.0, ResponseCurveType::Parabolic) == 0.25);
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Parabolic) == 1.0);
    }

    SECTION("evaluate(double value, double threshold, Cubic)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Cubic) == 0.0);
        REQUIRE(evaluate(0.5, 0.0, ResponseCurveType::Cubic) == 0.125);
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Cubic) == 1.0);
    }

    SECTION("evaluate(double value, double threshold, Exponential)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Exponential) == 0.0);
        REQUIRE_THAT(evaluate(0.5, 0.0, ResponseCurveType::Exponential),
            Catch::Matchers::WithinAbs(0.4142135624, 1e-10));
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Exponential) == 1.0);
    }

    SECTION("evaluate(double value, double threshold, Cosine)")
    {
        REQUIRE(evaluate(0.0, 0.0, ResponseCurveType::Cosine) == 0.0);
        REQUIRE_THAT(evaluate(0.5, 0.0, ResponseCurveType::Cosine),
            Catch::Matchers::WithinAbs(0.292893219, 1e-10));
        REQUIRE(evaluate(1.0, 0.0, ResponseCurveType::Cosine) == 1.0);
    }

}
