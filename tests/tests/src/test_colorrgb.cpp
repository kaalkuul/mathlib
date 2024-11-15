#include "utils.h"

using namespace mathlib;

TEST_CASE("ColorRGB", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(ColorRGBf::Real) == sizeof(float));
        REQUIRE(sizeof(ColorRGBd::Real) == sizeof(double));
    }

    // Constants

    SECTION("ColorRGBf::Black")
    {
        REQUIRE(ColorRGBf::Black.r == 0.0f);
        REQUIRE(ColorRGBf::Black.g == 0.0f);
        REQUIRE(ColorRGBf::Black.b == 0.0f);
    }

    SECTION("ColorRGBf::Red")
    {
        REQUIRE(ColorRGBf::Red.r == 1.0f);
        REQUIRE(ColorRGBf::Red.g == 0.0f);
        REQUIRE(ColorRGBf::Red.b == 0.0f);
    }

    SECTION("ColorRGBf::Green")
    {
        REQUIRE(ColorRGBf::Green.r == 0.0f);
        REQUIRE(ColorRGBf::Green.g == 1.0f);
        REQUIRE(ColorRGBf::Green.b == 0.0f);
    }

    SECTION("ColorRGBf::Blue")
    {
        REQUIRE(ColorRGBf::Blue.r == 0.0f);
        REQUIRE(ColorRGBf::Blue.g == 0.0f);
        REQUIRE(ColorRGBf::Blue.b == 1.0f);
    }

    SECTION("ColorRGBf::White")
    {
        REQUIRE(ColorRGBf::White.r == 1.0f);
        REQUIRE(ColorRGBf::White.g == 1.0f);
        REQUIRE(ColorRGBf::White.b == 1.0f);
    }

    // Constructors

    SECTION("ColorRGB(Real k)")
    {
        ColorRGBf c(42);
        REQUIRE(c.r == 42.0f);
        REQUIRE(c.g == 42.0f);
        REQUIRE(c.b == 42.0f);
    }

    SECTION("ColorRGB(Real x, Real y, Real z)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE(c.r == 1.0f);
        REQUIRE(c.g == 2.0f);
        REQUIRE(c.b == 3.0f);
    }

    // Create from

    SECTION("fromInterp(const ColorRGB& a, const ColorRGB& b, Real ratio)")
    {
        REQUIRE_THAT(ColorRGBf::fromInterp(ColorRGBf::Red, ColorRGBf::Green, 0.0f),
            Matches::WithinAbs(ColorRGBf::Red));
        REQUIRE_THAT(ColorRGBf::fromInterp(ColorRGBf::Red, ColorRGBf::Green, 1.0f),
            Matches::WithinAbs(ColorRGBf::Green));
        REQUIRE_THAT(ColorRGBf::fromInterp(ColorRGBf::Black, ColorRGBf::White, 0.5f),
            Matches::WithinAbs(ColorRGBf(0.5f)));
    }

    // Setters

    SECTION("set(Real r, Real g, Real b)")
    {
        ColorRGBf c;
        c.set(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(1.0f, 2.0f, 3.0f)));
    }

    SECTION("set(const ColorRGB& b)")
    {
        ColorRGBf c;
        c.set(ColorRGBf::Red);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf::Red));
        c.set(ColorRGBf::Green);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf::Green));
        c.set(ColorRGBf::Blue);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf::Blue));
        c.set(ColorRGBf(1.0f, 2.0f, 3.0f));
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(1.0f, 2.0f, 3.0f)));
    }

    SECTION("interp(const ColorRGB& a, const ColorRGB& b, Real ratio)")
    {
        ColorRGBf c;
        c.interp(ColorRGBf::Red, ColorRGBf::Green, 0.0f);
        REQUIRE_THAT(c,
            Matches::WithinAbs(ColorRGBf::Red));

        c.interp(ColorRGBf::Red, ColorRGBf::Green, 1.0f);
        REQUIRE_THAT(c,
            Matches::WithinAbs(ColorRGBf::Green));

        c.interp(ColorRGBf::Black, ColorRGBf::White, 0.5f);
        REQUIRE_THAT(c,
            Matches::WithinAbs(ColorRGBf(0.5f)));
    }

    // Assignments

    SECTION("operator+=(const ColorRGB &c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        c += ColorRGBf(10.0f, 11.0f, 12.0f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(11.0f, 13.0f, 15.0f)));
    }

    SECTION("operator-=(const ColorRGB &c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        c -= ColorRGBf(10.0f, 11.0f, 12.0f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(-9.0f, -9.0f, -9.0f)));
    }

    SECTION("operator*=(Real k)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        c *= 3;
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(3.0f, 6.0f, 9.0f)));
    }

    SECTION("operator/=(Real k)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        c /= 2.0f;
        REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBf(0.5f, 1.0f, 1.5f)));
    }

    // Arithmetic operators

    SECTION("operator+ (const ColorRGB& c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(c + ColorRGBf(10.0f, 11.0f, 12.0f),
            Matches::WithinAbs(ColorRGBf(11.0f, 13.0f, 15.0f)));
    }

    SECTION("operator- ()")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(-c, Matches::WithinAbs(ColorRGBf(-1.0f, -2.0f, -3.0f)));
    }

    SECTION("operator+ (const ColorRGB &c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(c - ColorRGBf(10.0f, 11.0f, 12.0f),
            Matches::WithinAbs(ColorRGBf(-9.0f, -9.0f, -9.0f)));
    }

    SECTION("operator* (Real k)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(c * 2, Matches::WithinAbs(ColorRGBf(2.0f, 4.0f, 6.0f)));
    }

    SECTION("operator/ (Real k)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE_THAT(c / 0.5f, Matches::WithinAbs(ColorRGBf(2.0f, 4.0f, 6.0f)));
    }

    // Comparison operators

    SECTION("operator== (const ColorRGB &c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE(c == c);
        REQUIRE(c == ColorRGBf(1.0f, 2.0f, 3.0f));
    }

    SECTION("operator!= (const ColorRGB &c)")
    {
        ColorRGBf c(1.0f, 2.0f, 3.0f);
        REQUIRE(!(c != c));
        REQUIRE(!(c != ColorRGBf(1.0f, 2.0f, 3.0f)));
    }

    //  Functions

    SECTION("toHSV()")
    {
        REQUIRE(ColorRGBf::Black.toHSV() == ColorHSVf::Black);
        REQUIRE(ColorRGBf::Red.toHSV() == ColorHSVf::Red);
        REQUIRE(ColorRGBf::Green.toHSV() == ColorHSVf::Green);
        REQUIRE(ColorRGBf::Blue.toHSV() == ColorHSVf::Blue);
        REQUIRE(ColorRGBf::White.toHSV() == ColorHSVf::White);

        REQUIRE(ColorRGBf(255, 255, 0).toHSV() == ColorHSVf(60.0f, 1.0f, 1.0f));
        REQUIRE(ColorRGBf(0, 255, 255).toHSV() == ColorHSVf(180.0f, 1.0f, 1.0f));
        REQUIRE(ColorRGBf(255, 0, 255).toHSV() == ColorHSVf(300.0f, 1.0f, 1.0f));

        REQUIRE_THAT(ColorRGBf(128, 128, 64).toHSV(),
            Matches::WithinAbs(ColorHSVf(60.0f, 0.5f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(64, 128, 128).toHSV(),
            Matches::WithinAbs(ColorHSVf(180.0f, 0.5f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(128, 64, 128).toHSV(),
            Matches::WithinAbs(ColorHSVf(300.0f, 0.5f, 0.502f)));

        REQUIRE_THAT(ColorRGBf(128, 64, 32).toHSV(),
            Matches::WithinAbs(ColorHSVf(20.0f, 0.75f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(128, 32, 64).toHSV(),
            Matches::WithinAbs(ColorHSVf(340.0f, 0.75f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(64, 128, 32).toHSV(),
            Matches::WithinAbs(ColorHSVf(100.0f, 0.75f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(32, 128, 64).toHSV(),
            Matches::WithinAbs(ColorHSVf(140.0f, 0.75f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(64, 32, 128).toHSV(),
            Matches::WithinAbs(ColorHSVf(260.0f, 0.75f, 0.502f)));
        REQUIRE_THAT(ColorRGBf(32, 64, 128).toHSV(),
            Matches::WithinAbs(ColorHSVf(220.0f, 0.75f, 0.502f)));
    }

    SECTION("data()")
    {
        ColorRGBf c = ColorRGBf::Red;
        const float* cdata = c.data();
        float* data = c.data();

        REQUIRE(cdata == data);
        REQUIRE(cdata[0] == 1.0f);
        REQUIRE(cdata[1] == 0.0f);
        REQUIRE(cdata[2] == 0.0f);
    }

    SECTION("cast()")
    {
        REQUIRE(ColorRGBf::Black.cast<double>() == ColorRGBd::Black);
        REQUIRE(ColorRGBf::Red.cast<double>() == ColorRGBd::Red);
        REQUIRE(ColorRGBf::Green.cast<double>() == ColorRGBd::Green);
        REQUIRE(ColorRGBf::Blue.cast<double>() == ColorRGBd::Blue);
        REQUIRE(ColorRGBf::White.cast<double>() == ColorRGBd::White);

        REQUIRE(ColorRGBd::Black.cast<float>() == ColorRGBf::Black);
        REQUIRE(ColorRGBd::Red.cast<float>() == ColorRGBf::Red);
        REQUIRE(ColorRGBd::Green.cast<float>() == ColorRGBf::Green);
        REQUIRE(ColorRGBd::Blue.cast<float>() == ColorRGBf::Blue);
        REQUIRE(ColorRGBd::White.cast<float>() == ColorRGBf::White);
    }

    SECTION("random()")
    {
        ColorRGBf c = ColorRGBf::random();
    }
    
    SECTION("Matches::WithinAbs")
    {
        REQUIRE_THAT(ColorRGBf::White, Matches::WithinAbs(ColorRGBf::White));
    }
}
