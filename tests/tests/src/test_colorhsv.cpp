#include "utils.h"

using namespace mathlib;

TEST_CASE("ColorHSV", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(ColorHSVf::Real) == sizeof(float));
        REQUIRE(sizeof(ColorHSVd::Real) == sizeof(double));
    }

    // Constants

    SECTION("ColorHSVf::Black")
    {
        REQUIRE(ColorHSVf::Black.h == 0.0f);
        REQUIRE(ColorHSVf::Black.s == 0.0f);
        REQUIRE(ColorHSVf::Black.v == 0.0f);
    }

    SECTION("ColorHSVf::Red")
    {
        REQUIRE(ColorHSVf::Red.h == 0.0f);
        REQUIRE(ColorHSVf::Red.s == 1.0f);
        REQUIRE(ColorHSVf::Red.v == 1.0f);
    }

    SECTION("ColorHSVf::Green")
    {
        REQUIRE(ColorHSVf::Green.h == 120.0f);
        REQUIRE(ColorHSVf::Green.s == 1.0f);
        REQUIRE(ColorHSVf::Green.v == 1.0f);
    }

    SECTION("ColorHSVf::Blue")
    {
        REQUIRE(ColorHSVf::Blue.h == 240.0f);
        REQUIRE(ColorHSVf::Blue.s == 1.0f);
        REQUIRE(ColorHSVf::Blue.v == 1.0f);
    }

    SECTION("ColorHSVf::White")
    {
        REQUIRE(ColorHSVf::White.h == 0.0f);
        REQUIRE(ColorHSVf::White.s == 0.0f);
        REQUIRE(ColorHSVf::White.v == 1.0f);
    }

    // Constructors

    SECTION("ColorHSV(Real h, Real s, Real v)")
    {
        ColorHSVf c(1, 2, 3);
        REQUIRE(c.h == 1.0f);
        REQUIRE(c.s == 2.0f);
        REQUIRE(c.v == 3.0f);
    }

    // Create from

    SECTION("fromInterp(const ColorHSV& a, const ColorHSV& b, Real ratio)")
    {
        REQUIRE_THAT(ColorHSVf::fromInterp(ColorHSVf::Red, ColorHSVf::Green, 0.0f),
            Matches::WithinAbs(ColorHSVf::Red));
        REQUIRE_THAT(ColorHSVf::fromInterp(ColorHSVf::Red, ColorHSVf::Green, 1.0f),
            Matches::WithinAbs(ColorHSVf::Green));
        REQUIRE_THAT(ColorHSVf::fromInterp(ColorHSVf::Black, ColorHSVf::White, 0.5f),
            Matches::WithinAbs(ColorHSVf(0.0f, 0.0f, 0.5f)));
    }

    // Setters

    SECTION("set(Real h, Real s, Real v)")
    {
        ColorHSVf c;
        c.set(1, 2, 3);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(1, 2, 3)));
    }

    SECTION("set(const ColorHSV& b)")
    {
        ColorHSVf c;
        c.set(ColorHSVf::Red);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf::Red));
        c.set(ColorHSVf::Green);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf::Green));
        c.set(ColorHSVf::Blue);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf::Blue));
        c.set(ColorHSVf(1, 2, 3));
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(1, 2, 3)));
    }

    SECTION("interp(const ColorHSV& a, const ColorHSV& b, Real ratio)")
    {
        ColorHSVf c;
        c.interp(ColorHSVf::Red, ColorHSVf::Green, 0.0f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf::Red));

        c.interp(ColorHSVf::Red, ColorHSVf::Green, 1.0f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf::Green));

        c.interp(ColorHSVf::Black, ColorHSVf::White, 0.5f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(0.0f, 0.0f, 0.5f)));

        c.interp(ColorHSVf(0.0f, 0.0f, 0.0f), ColorHSVf(178.0f, 1.0f, 1.0f), 0.5f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(89.0f, 0.5f, 0.5f)));

        c.interp(ColorHSVf(0.0f, 0.0f, 0.0f), ColorHSVf(182.0f, 1.0f, 1.0f), 0.5f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(271.0f, 0.5f, 0.5f)));

        c.interp(ColorHSVf(178.0f, 1.0f, 1.0f), ColorHSVf(0.0f, 0.0f, 0.0f), 0.5f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(89.0f, 0.5f, 0.5f)));

        c.interp(ColorHSVf(182.0f, 1.0f, 1.0f), ColorHSVf(0.0f, 0.0f, 0.0f), 0.5f);
        REQUIRE_THAT(c, Matches::WithinAbs(ColorHSVf(271.0f, 0.5f, 0.5f)));
    }

    // Comparison operators

    SECTION("operator== (const ColorHSV &c)")
    {
        ColorHSVf c(1, 2, 3);
        REQUIRE(c == c);
        REQUIRE(c == ColorHSVf(1, 2, 3));
    }

    SECTION("operator!= (const ColorHSV &c)")
    {
        ColorHSVf c(1, 2, 3);
        REQUIRE(!(c != c));
        REQUIRE(c != ColorHSVf(1.1, 2, 3));
    }

    //  Functions

    SECTION("toRGB()")
    {
        REQUIRE(ColorHSVf::Black.toRGB() == ColorRGBf::Black);
        REQUIRE(ColorHSVf::Red.toRGB()   == ColorRGBf::Red);
        REQUIRE(ColorHSVf::Green.toRGB() == ColorRGBf::Green);
        REQUIRE(ColorHSVf::Blue.toRGB()  == ColorRGBf::Blue);
        REQUIRE(ColorHSVf::White.toRGB() == ColorRGBf::White);

        REQUIRE(ColorHSVf(60.0f,  1.0f, 1.0f).toRGB() == ColorRGBf(255, 255, 0));
        REQUIRE(ColorHSVf(180.0f, 1.0f, 1.0f).toRGB() == ColorRGBf(0, 255, 255));
        REQUIRE(ColorHSVf(300.0f, 1.0f, 1.0f).toRGB() == ColorRGBf(255, 0, 255));

        REQUIRE_THAT(ColorHSVf(60.0f,  0.5f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(128, 128, 64)));
        REQUIRE_THAT(ColorHSVf(180.0f, 0.5f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(64, 128, 128)));
        REQUIRE_THAT(ColorHSVf(300.0f, 0.5f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(128, 64, 128)));

        REQUIRE_THAT(ColorHSVf(20.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(128, 64, 32)));
        REQUIRE_THAT(ColorHSVf(340.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(128, 32, 64)));
        REQUIRE_THAT(ColorHSVf(100.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(64, 128, 32)));
        REQUIRE_THAT(ColorHSVf(140.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(32, 128, 64)));
        REQUIRE_THAT(ColorHSVf(260.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(64, 32, 128)));
        REQUIRE_THAT(ColorHSVf(220.0f, 0.75f, 0.502f).toRGB(),
            Matches::WithinAbs(ColorRGBf(32, 64, 128)));
    }

    SECTION("data()")
    {
        ColorHSVf c = ColorHSVf::Red;
        const float* cdata = c.data();
        float* data = c.data();

        REQUIRE(cdata == data);
        REQUIRE(cdata[0] == 0.0f);
        REQUIRE(cdata[1] == 1.0f);
        REQUIRE(cdata[2] == 1.0f);
    }

    SECTION("cast()")
    {
        REQUIRE(ColorHSVf::Black.cast<double>() == ColorHSVd::Black);
        REQUIRE(ColorHSVf::Red.cast<double>() == ColorHSVd::Red);
        REQUIRE(ColorHSVf::Green.cast<double>() == ColorHSVd::Green);
        REQUIRE(ColorHSVf::Blue.cast<double>() == ColorHSVd::Blue);
        REQUIRE(ColorHSVf::White.cast<double>() == ColorHSVd::White);

        REQUIRE(ColorHSVd::Black.cast<float>() == ColorHSVf::Black);
        REQUIRE(ColorHSVd::Red.cast<float>() == ColorHSVf::Red);
        REQUIRE(ColorHSVd::Green.cast<float>() == ColorHSVf::Green);
        REQUIRE(ColorHSVd::Blue.cast<float>() == ColorHSVf::Blue);
        REQUIRE(ColorHSVd::White.cast<float>() == ColorHSVf::White);
    }

    SECTION("random()")
    {
        ColorHSVf c = ColorHSVf::random();
    }
    
    SECTION("Matches::WithinAbs")
    {
        REQUIRE_THAT(ColorHSVf::White, Matches::WithinAbs(ColorHSVf::White));
    }
}
