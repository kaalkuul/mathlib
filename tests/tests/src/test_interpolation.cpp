#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("Interpolation", "")
    {
        SECTION("interpolationRatio")
        {
            REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Linear), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Linear), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Linear), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Parabolic), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Parabolic), Catch::Matchers::WithinAbs(0.25, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Parabolic), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(0.125, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Exponential), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Exponential), Catch::Matchers::WithinAbs(0.4142135624, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Exponential), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Cosine), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Cosine), Catch::Matchers::WithinAbs(0.2928932188, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Cosine), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuadraticIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuadraticIn), Catch::Matchers::WithinAbs(0.25, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuadraticIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuadraticOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuadraticOut), Catch::Matchers::WithinAbs(0.75, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuadraticOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuadraticInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuadraticInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuadraticInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CubicIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CubicIn), Catch::Matchers::WithinAbs(0.125, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CubicIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CubicOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CubicOut), Catch::Matchers::WithinAbs(0.875, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CubicOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CubicInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CubicInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CubicInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuarticIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuarticIn), Catch::Matchers::WithinAbs(0.0625, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuarticIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuarticOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuarticOut), Catch::Matchers::WithinAbs(0.9375, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuarticOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuarticInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuarticInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuarticInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuinticIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuinticIn), Catch::Matchers::WithinAbs(0.03125, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuinticIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuinticOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuinticOut), Catch::Matchers::WithinAbs(0.96875, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuinticOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::QuinticInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::QuinticInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::QuinticInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::SinusoidalIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::SinusoidalIn), Catch::Matchers::WithinAbs(0.2928932188, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::SinusoidalIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::SinusoidalOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::SinusoidalOut), Catch::Matchers::WithinAbs(0.7071067812, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::SinusoidalOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::SinusoidalInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::SinusoidalInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::SinusoidalInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::ExponentialIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::ExponentialIn), Catch::Matchers::WithinAbs(0.0303031056, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::ExponentialIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::ExponentialOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::ExponentialOut), Catch::Matchers::WithinAbs(0.9696968944, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::ExponentialOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::ExponentialInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::ExponentialInOut), Catch::Matchers::WithinAbs(0.4999987502, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::ExponentialInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Exponential2In), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Exponential2In), Catch::Matchers::WithinAbs(0.0009765625, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Exponential2In), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Exponential2Out), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Exponential2Out), Catch::Matchers::WithinAbs(0.9990234375, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Exponential2Out), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::Exponential2InOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::Exponential2InOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::Exponential2InOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CircularIn), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CircularIn), Catch::Matchers::WithinAbs(0.1339745962, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CircularIn), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CircularOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CircularOut), Catch::Matchers::WithinAbs(0.8660254038, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CircularOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        	REQUIRE_THAT(interpolationRatio(0.0, InterpolationMode::CircularInOut), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(interpolationRatio(0.5, InterpolationMode::CircularInOut), Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(interpolationRatio(1.0, InterpolationMode::CircularInOut), Catch::Matchers::WithinAbs(1.0, 1e-10));
        }

        SECTION("lerp(int from, int to, Real ratio)")
        {
            REQUIRE(lerp(0, 100, 0.0) == 0);
            REQUIRE(lerp(0, 100, 0.5) == 50);
            REQUIRE(lerp(0, 100, 1.0) == 100);
        }

        SECTION("lerp(Real from, Real to, Real ratio)")
        {
            REQUIRE_THAT(lerp(0.0, 100.0, 0.0), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(lerp(0.0, 100.0, 0.5), Catch::Matchers::WithinAbs(50.0, 1e-10));
            REQUIRE_THAT(lerp(0.0, 100.0, 1.0), Catch::Matchers::WithinAbs(100.0, 1e-10));
        }

        SECTION("lerp(const Vec2<Real>& from, const Vec2<Real>& to, Real ratio)")
        {
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 0.0f), Matches::WithinAbs(Vec2f::Zero, 1e-10));
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 0.5f), Matches::WithinAbs(Vec2f(0.5f, 0.5f), 1e-10));
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 1.0f), Matches::WithinAbs(Vec2f(1.0f, 1.0f), 1e-10));
        }

        SECTION("lerp(const Vec3<Real>& from, const Vec3<Real>& to, Real ratio)")
        {
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 0.0f), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 0.5f), Matches::WithinAbs(Vec3f(0.5f, 0.5f, 0.5f), 1e-10));
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 1.0f), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
        }

        SECTION("lerp(int from, int to, Real ratio)")
        {
            REQUIRE(lerp(0, 100, 0.0, InterpolationMode::Cubic) == 0);
            REQUIRE(lerp(0, 100, 0.5, InterpolationMode::Cubic) == 12);
            REQUIRE(lerp(0, 100, 1.0, InterpolationMode::Cubic) == 100);
        }

        SECTION("lerp(Real from, Real to, Real ratio, InterpolationMode Mode)")
        {
            REQUIRE_THAT(lerp(0.0, 100.0, 0.0, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(lerp(0.0, 100.0, 0.5, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(12.5, 1e-10));
            REQUIRE_THAT(lerp(0.0, 100.0, 1.0, InterpolationMode::Cubic), Catch::Matchers::WithinAbs(100.0, 1e-10));
        }

        SECTION("lerp(const Vec2<Real>& from, const Vec2<Real>& to, Real ratio, InterpolationMode Mode)")
        {
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 0.0f, InterpolationMode::Cubic), Matches::WithinAbs(Vec2f::Zero, 1e-10));
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 0.5f, InterpolationMode::Cubic), Matches::WithinAbs(Vec2f(0.125f, 0.125f), 1e-10));
            REQUIRE_THAT(lerp(Vec2f::Zero, Vec2f(1.0f, 1.0f), 1.0f, InterpolationMode::Cubic), Matches::WithinAbs(Vec2f(1.0f, 1.0f), 1e-10));
        }

        SECTION("lerp(const Vec3<Real>& from, const Vec3<Real>& to, Real ratio, InterpolationMode Mode)")
        {
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 0.0f, InterpolationMode::Cubic), Matches::WithinAbs(Vec3f::Zero, 1e-10));
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 0.5f, InterpolationMode::Cubic), Matches::WithinAbs(Vec3f(0.125f, 0.125f, 0.125f), 1e-10));
            REQUIRE_THAT(lerp(Vec3f::Zero, Vec3f(1.0f, 1.0f, 1.0f), 1.0f, InterpolationMode::Cubic), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
        }

        SECTION("clerp(Real from, Real to, Real ratio)")
        {
            REQUIRE_THAT(clerp(0.0, Constantsd::PI, 0.0), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerp(0.0, Constantsd::PI, 0.5), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
            REQUIRE_THAT(clerp(0.0, Constantsd::PI, 1.0), Catch::Matchers::WithinAbs(-Constantsd::PI, 1e-10));

            REQUIRE_THAT(clerp(0.0, Constantsd::PI*1.5, 0.0), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerp(0.0, Constantsd::PI*1.5, 0.5), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_4, 1e-10));
            REQUIRE_THAT(clerp(0.0, Constantsd::PI*1.5, 1.0), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
        }

        SECTION("clerpMaxAngle(Real from, Real to, Real maxAngle)")
        {
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, 0.0), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, Constantsd::PI_OVER_2), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, Constantsd::PI*10.0), Catch::Matchers::WithinAbs(-Constantsd::PI, 1e-10));

            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, 0.0), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, Constantsd::PI_OVER_4), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_4, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, Constantsd::PI * 10.0), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
        }

        SECTION("clerpMaxAngle(Real from, Real to, Real maxAngle, Real& ratio)")
        {
            double ratio;
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, 0.0, ratio), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, Constantsd::PI_OVER_2, ratio), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI, Constantsd::PI * 10.0, ratio), Catch::Matchers::WithinAbs(-Constantsd::PI, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(1.0, 1e-10));

            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, 0.0, ratio), Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(0.0, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, Constantsd::PI_OVER_4, ratio), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_4, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(0.5, 1e-10));
            REQUIRE_THAT(clerpMaxAngle(0.0, Constantsd::PI * 1.5, Constantsd::PI * 10.0, ratio), Catch::Matchers::WithinAbs(-Constantsd::PI_OVER_2, 1e-10));
            REQUIRE_THAT(ratio, Catch::Matchers::WithinAbs(1.0, 1e-10));
        }

    }
}
