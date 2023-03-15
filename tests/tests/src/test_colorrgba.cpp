#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("ColorRGBA", "")
    {
        // Constants

        SECTION("ColorRGBAf::Black")
        {
            REQUIRE(ColorRGBAf::Black.r == 0.0f);
            REQUIRE(ColorRGBAf::Black.g == 0.0f);
            REQUIRE(ColorRGBAf::Black.b == 0.0f);
        }

        SECTION("ColorRGBAf::Red")
        {
            REQUIRE(ColorRGBAf::Red.r == 1.0f);
            REQUIRE(ColorRGBAf::Red.g == 0.0f);
            REQUIRE(ColorRGBAf::Red.b == 0.0f);
        }

        SECTION("ColorRGBAf::Green")
        {
            REQUIRE(ColorRGBAf::Green.r == 0.0f);
            REQUIRE(ColorRGBAf::Green.g == 1.0f);
            REQUIRE(ColorRGBAf::Green.b == 0.0f);
        }

        SECTION("ColorRGBAf::Blue")
        {
            REQUIRE(ColorRGBAf::Blue.r == 0.0f);
            REQUIRE(ColorRGBAf::Blue.g == 0.0f);
            REQUIRE(ColorRGBAf::Blue.b == 1.0f);
        }

        SECTION("ColorRGBAf::White")
        {
            REQUIRE(ColorRGBAf::White.r == 1.0f);
            REQUIRE(ColorRGBAf::White.g == 1.0f);
            REQUIRE(ColorRGBAf::White.b == 1.0f);
        }

        // Constructors

        SECTION("ColorRGBA(Real k)")
        {
            ColorRGBAf c(42);
            REQUIRE(c.r == 42.0f);
            REQUIRE(c.g == 42.0f);
            REQUIRE(c.b == 42.0f);
        }

        SECTION("ColorRGBA(Real x, Real y, Real z)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE(c.r == 1.0f);
            REQUIRE(c.g == 2.0f);
            REQUIRE(c.b == 3.0f);
        }

        // Create from

        SECTION("fromInterp(const ColorRGBA& a, const ColorRGBA& b, Real ratio)")
        {
            REQUIRE_THAT(ColorRGBAf::fromInterp(ColorRGBAf::Red, ColorRGBAf::Green, 0.0f),
                Matches::WithinAbs(ColorRGBAf::Red));
            REQUIRE_THAT(ColorRGBAf::fromInterp(ColorRGBAf::Red, ColorRGBAf::Green, 1.0f),
                Matches::WithinAbs(ColorRGBAf::Green));
            REQUIRE_THAT(ColorRGBAf::fromInterp(ColorRGBAf::Black, ColorRGBAf::White, 0.5f),
                Matches::WithinAbs(ColorRGBAf(0.5f, 1.0f)));
        }

        // Setters

        SECTION("set(Real r, Real g, Real b)")
        {
            ColorRGBAf c;
            c.set(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(1.0f, 2.0f, 3.0f)));
        }

        SECTION("set(const ColorRGBA& b)")
        {
            ColorRGBAf c;
            c.set(ColorRGBAf::Red);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf::Red));
            c.set(ColorRGBAf::Green);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf::Green));
            c.set(ColorRGBAf::Blue);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf::Blue));
            c.set(ColorRGBAf(1.0f, 2.0f, 3.0f));
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(1.0f, 2.0f, 3.0f)));
        }

        SECTION("interp(const ColorRGBA& a, const ColorRGBA& b, Real ratio)")
        {
            ColorRGBAf c;
            c.interp(ColorRGBAf::Red, ColorRGBAf::Green, 0.0f);
            REQUIRE_THAT(c,
                Matches::WithinAbs(ColorRGBAf::Red));

            c.interp(ColorRGBAf::Red, ColorRGBAf::Green, 1.0f);
            REQUIRE_THAT(c,
                Matches::WithinAbs(ColorRGBAf::Green));

            c.interp(ColorRGBAf::Black, ColorRGBAf::White, 0.5f);
            REQUIRE_THAT(c,
                Matches::WithinAbs(ColorRGBAf(0.5f, 1.0f)));
        }

    	// Assignments

        SECTION("operator+=(const ColorRGBA &c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            c += ColorRGBAf(10.0f, 11.0f, 12.0f);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(11.0f, 13.0f, 15.0f)));
        }

        SECTION("operator-=(const ColorRGBA &c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            c -= ColorRGBAf(10.0f, 11.0f, 12.0f);
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(-9.0f, -9.0f, -9.0f)));
        }

        SECTION("operator*=(Real k)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            c *= 3;
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(3.0f, 6.0f, 9.0f)));
        }

        SECTION("operator/=(Real k)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            c /= 2;
            REQUIRE_THAT(c, Matches::WithinAbs(ColorRGBAf(0.5f, 1.0f, 1.5f)));
        }

        // Arithmetic operators

        SECTION("operator+ (const ColorRGBA& c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(c + ColorRGBAf(10.0f, 11.0f, 12.0f),
                Matches::WithinAbs(ColorRGBAf(11.0f, 13.0f, 15.0f)));
        }

        SECTION("operator- ()")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(-c, Matches::WithinAbs(ColorRGBAf(-1.0f, -2.0f, -3.0f)));
        }

        SECTION("operator+ (const ColorRGBA &c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(c - ColorRGBAf(10.0f, 11.0f, 12.0f),
                Matches::WithinAbs(ColorRGBAf(-9.0f, -9.0f, -9.0f)));
        }

        SECTION("operator* (Real k)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(c * 2, Matches::WithinAbs(ColorRGBAf(2.0f, 4.0f, 6.0f)));
        }

        SECTION("operator/ (Real k)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE_THAT(c / 0.5f, Matches::WithinAbs(ColorRGBAf(2.0f, 4.0f, 6.0f)));
        }

    	// Comparison operators

        SECTION("operator== (const ColorRGBA &c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE(c == c);
            REQUIRE(c == ColorRGBAf(1.0f, 2.0f, 3.0f));
        }

        SECTION("operator!= (const ColorRGBA &c)")
        {
            ColorRGBAf c(1.0f, 2.0f, 3.0f);
            REQUIRE(!(c != c));
            REQUIRE(!(c != ColorRGBAf(1.0f, 2.0f, 3.0f)));
        }

        //  Functions

        SECTION("toHSV()")
        {
            REQUIRE(ColorRGBAf::Black.toHSV() == ColorHSVf::Black);
            REQUIRE(ColorRGBAf::Red.toHSV() == ColorHSVf::Red);
            REQUIRE(ColorRGBAf::Green.toHSV() == ColorHSVf::Green);
            REQUIRE(ColorRGBAf::Blue.toHSV() == ColorHSVf::Blue);
            REQUIRE(ColorRGBAf::White.toHSV() == ColorHSVf::White);

            REQUIRE(ColorRGBAf(255, 255, 0).toHSV() == ColorHSVf(60.0f, 1.0f, 1.0f));
            REQUIRE(ColorRGBAf(0, 255, 255).toHSV() == ColorHSVf(180.0f, 1.0f, 1.0f));
            REQUIRE(ColorRGBAf(255, 0, 255).toHSV() == ColorHSVf(300.0f, 1.0f, 1.0f));

            REQUIRE_THAT(ColorRGBAf(128, 128, 64).toHSV(),
                Matches::WithinAbs(ColorHSVf(60.0f, 0.5f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(64, 128, 128).toHSV(),
                Matches::WithinAbs(ColorHSVf(180.0f, 0.5f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(128, 64, 128).toHSV(),
                Matches::WithinAbs(ColorHSVf(300.0f, 0.5f, 0.502f)));

            REQUIRE_THAT(ColorRGBAf(128, 64, 32).toHSV(),
                Matches::WithinAbs(ColorHSVf(20.0f, 0.75f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(128, 32, 64).toHSV(),
                Matches::WithinAbs(ColorHSVf(340.0f, 0.75f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(64, 128, 32).toHSV(),
                Matches::WithinAbs(ColorHSVf(100.0f, 0.75f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(32, 128, 64).toHSV(),
                Matches::WithinAbs(ColorHSVf(140.0f, 0.75f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(64, 32, 128).toHSV(),
                Matches::WithinAbs(ColorHSVf(260.0f, 0.75f, 0.502f)));
            REQUIRE_THAT(ColorRGBAf(32, 64, 128).toHSV(),
                Matches::WithinAbs(ColorHSVf(220.0f, 0.75f, 0.502f)));
        }

        SECTION("data()")
        {
            ColorRGBAf c = ColorRGBAf::Red;
            const float* cdata = c.data();
            float* data = c.data();

            REQUIRE(cdata == data);
            REQUIRE(cdata[0] == 1.0f);
            REQUIRE(cdata[1] == 0.0f);
            REQUIRE(cdata[2] == 0.0f);
        }

        SECTION("cast()")
        {
            REQUIRE(ColorRGBAf::Black.cast<double>() == ColorRGBAd::Black);
            REQUIRE(ColorRGBAf::Red.cast<double>() == ColorRGBAd::Red);
            REQUIRE(ColorRGBAf::Green.cast<double>() == ColorRGBAd::Green);
            REQUIRE(ColorRGBAf::Blue.cast<double>() == ColorRGBAd::Blue);
            REQUIRE(ColorRGBAf::White.cast<double>() == ColorRGBAd::White);

            REQUIRE(ColorRGBAd::Black.cast<float>() == ColorRGBAf::Black);
            REQUIRE(ColorRGBAd::Red.cast<float>() == ColorRGBAf::Red);
            REQUIRE(ColorRGBAd::Green.cast<float>() == ColorRGBAf::Green);
            REQUIRE(ColorRGBAd::Blue.cast<float>() == ColorRGBAf::Blue);
            REQUIRE(ColorRGBAd::White.cast<float>() == ColorRGBAf::White);
        }

        SECTION("random()")
        {
            ColorRGBAf c = ColorRGBAf::random();
        }

    }
}
