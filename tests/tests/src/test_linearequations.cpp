#include "utils.h"

namespace {

    using namespace mathlib;

    TEST_CASE("TriDiagonal", "")
    {
        SECTION("solve(const Real* a, const Real* b, const Real* c, const Real* r, Real* u, int n)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f };
                float b[] = { 1.0f, 1.0f };
                float c[] = { 1.0f };
                float r[] = { 1.0f, 1.0f };
                float u[2];
                REQUIRE(!TriDiagonalf::solve(a, b, c, r, u, 2));
            }

            SECTION("Case 1")
            {
                float a[] = { 1.0f };
                float b[] = { 2.0f, 2.0f };
                float c[] = { 1.0f };
                float r[] = { 1.0f, 1.0f };
                float u[2];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 2));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(1.0f/3.0f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(1.0f/3.0f, 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f };
                float b[] = { 2.0f, 7.0f };
                float c[] = { 1.0f };
                float r[] = { 1.0f, 1.0f };
                float u[2];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 2));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(0.5f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(0.0f, 1e-6));
            }

            SECTION("Case 3")
            {
                float a[] = { 1.0f, 1.0f };
                float b[] = { 2.0f, 2.0f, 2.0f };
                float c[] = { 1.0f , 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 3));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(0.5f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(0.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(0.5f, 1e-6));
            }

            SECTION("Case 4")
            {
                float a[] = { 2.0f, 2.0f };
                float b[] = { 2.0f, 2.0f, 7.0f };
                float c[] = { 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 3));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(3.0f / 5.0f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(-1.0f / 5.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(1.0f / 5.0f, 1e-6));
            }

            SECTION("Case 5")
            {
                float a[] = { 1.0f, 1.0f, 1.0f };
                float b[] = { 4.0f, 2.0f, 2.0f, 6.5f };
                float c[] = { 1.0f, 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                float u[4];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 4));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(11.0f / 58.0f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(7.0f / 29.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(19.0f / 58.0f, 1e-6));
                REQUIRE_THAT(u[3], Catch::Matchers::WithinAbs(3.0f / 29.0f, 1e-6));
            }
        }

        SECTION("solve(const Real* a, const Real* b, const Real* c, const Real* r, Vec3<Real>* u, int n)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f };
                float b[] = { 1.0f, 1.0f };
                float c[] = { 1.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                Vec3f u[2];
                REQUIRE(!TriDiagonalf::solve(a, b, c, r, u, 2));
            }

            SECTION("Case 1")
            {
                float a[] = { 1.0f };
                float b[] = { 2.0f, 2.0f };
                float c[] = { 1.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                Vec3f u[2];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 2));
                REQUIRE_THAT(u[0], Matches::WithinAbs(Vec3f::OneX * (1.0f / 3.0f), 1e-6));
                REQUIRE_THAT(u[1], Matches::WithinAbs(Vec3f::OneX * (1.0f / 3.0f), 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f };
                float b[] = { 2.0f, 7.0f };
                float c[] = { 1.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                Vec3f u[2];
                REQUIRE(TriDiagonalf::solve(a, b, c, r, u, 2));
                REQUIRE_THAT(u[0], Matches::WithinAbs(Vec3f::OneX * 0.5f, 1e-6));
                REQUIRE_THAT(u[1], Matches::WithinAbs(Vec3f::Zero, 1e-6));
            }
        }

        SECTION("solveCyclic(const Real* a, const Real* b, const Real* c, Real alpha, Real beta, const Real* r, Real* x, int n)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f, 1.0f };
                float b[] = { 1.0f, 1.0f, 1.0f };
                float c[] = { 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(!TriDiagonalf::solveCyclic(a, b, c, 1.0f, 1.0f, r, u, 3));
            }

            SECTION("Case 1")
            {
                float a[] = { 1.0f, 1.0f };
                float b[] = { 2.0f, 2.0f, 2.0f };
                float c[] = { 1.0f , 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(TriDiagonalf::solveCyclic(a, b, c, 0.0f, 0.0f, r, u, 3));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(0.5f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(0.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(0.5f, 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f, 2.0f };
                float b[] = { 2.0f, 2.0f, 7.0f };
                float c[] = { 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(TriDiagonalf::solveCyclic(a, b, c, 0.0f, 0.0f, r, u, 3));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(3.0f / 5.0f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(-1.0f / 5.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(1.0f / 5.0f, 1e-6));
            }

            SECTION("Case 3")
            {
                float a[] = { 1.0f, 1.0f };
                float b[] = { 2.0f, 2.0f, 2.0f };
                float c[] = { 1.0f , 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f };
                float u[3];
                REQUIRE(TriDiagonalf::solveCyclic(a, b, c, 1.0f, 1.0f, r, u, 3));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(0.25f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(0.25f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(0.25f, 1e-6));
            }

            SECTION("Case 4")
            {
                float a[] = { 1.0f, 1.0f, 1.0f };
                float b[] = { 2.0f, 2.0f, 2.0f, 2.0f };
                float c[] = { 1.0f, 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                float u[4];
                REQUIRE(TriDiagonalf::solveCyclic(a, b, c, 3.0f, 3.0f, r, u, 4));
                REQUIRE_THAT(u[0], Catch::Matchers::WithinAbs(1.0f / 7.0f, 1e-6));
                REQUIRE_THAT(u[1], Catch::Matchers::WithinAbs(2.0f / 7.0f, 1e-6));
                REQUIRE_THAT(u[2], Catch::Matchers::WithinAbs(2.0f / 7.0f, 1e-6));
                REQUIRE_THAT(u[3], Catch::Matchers::WithinAbs(1.0f / 7.0f, 1e-6));
            }
        }
    }

    TEST_CASE("GaussJordan", "")
    {
        SECTION("solve(Real* a, int n, Real* b, int m)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                float r[] = { 1.0f, 1.0f };
                REQUIRE(!GaussJordanf::solve(a, 2, r, 1));
            }

            SECTION("Case 1")
            {
                float a[] = { 2.0f, 1.0f, 1.0f, 2.0f };
                float r[] = { 1.0f, 1.0f };
                REQUIRE(GaussJordanf::solve(a, 2, r, 1));
                REQUIRE_THAT(r[1], Catch::Matchers::WithinAbs(1.0f / 3.0f, 1e-6));
                REQUIRE_THAT(r[0], Catch::Matchers::WithinAbs(1.0f / 3.0f, 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f, 1.0f, 2.0f, 7.0f };
                float r[] = { 1.0f, 1.0f };
                REQUIRE(GaussJordanf::solve(a, 2, r, 1));
                REQUIRE_THAT(r[0], Catch::Matchers::WithinAbs(0.5f, 1e-6));
                REQUIRE_THAT(r[1], Catch::Matchers::WithinAbs(0.0f, 1e-6));
            }
        }

        SECTION("solve(Real* a, int n, Vec2<Real>* b)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                Vec2f r[] = { Vec2f::OneX, Vec2f::OneX };
                REQUIRE(!GaussJordanf::solve(a, 2, r));
            }

            SECTION("Case 1")
            {
                float a[] = { 2.0f, 1.0f, 1.0f, 2.0f };
                Vec2f r[] = { Vec2f::OneX, Vec2f::OneX };
                REQUIRE(GaussJordanf::solve(a, 2, r));
                REQUIRE_THAT(r[0], Matches::WithinAbs(Vec2f::OneX * (1.0f / 3.0f), 1e-6));
                REQUIRE_THAT(r[1], Matches::WithinAbs(Vec2f::OneX * (1.0f / 3.0f), 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f, 1.0f, 2.0f, 7.0f };
                Vec2f r[] = { Vec2f::OneX, Vec2f::OneX };
                REQUIRE(GaussJordanf::solve(a, 2, r));
                REQUIRE_THAT(r[0], Matches::WithinAbs(Vec2f::OneX * 0.5f, 1e-6));
                REQUIRE_THAT(r[1], Matches::WithinAbs(Vec2f::Zero, 1e-6));
            }
        }

        SECTION("solve(Real* a, int n, Vec3<Real>* b)")
        {
            SECTION("Case 0")
            {
                float a[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                REQUIRE(!GaussJordanf::solve(a, 2, r));
            }

            SECTION("Case 1")
            {
                float a[] = { 2.0f, 1.0f, 1.0f, 2.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                REQUIRE(GaussJordanf::solve(a, 2, r));
                REQUIRE_THAT(r[0], Matches::WithinAbs(Vec3f::OneX * (1.0f / 3.0f), 1e-6));
                REQUIRE_THAT(r[1], Matches::WithinAbs(Vec3f::OneX * (1.0f / 3.0f), 1e-6));
            }

            SECTION("Case 2")
            {
                float a[] = { 2.0f, 1.0f, 2.0f, 7.0f };
                Vec3f r[] = { Vec3f::OneX, Vec3f::OneX };
                REQUIRE(GaussJordanf::solve(a, 2, r));
                REQUIRE_THAT(r[0], Matches::WithinAbs(Vec3f::OneX * 0.5f, 1e-6));
                REQUIRE_THAT(r[1], Matches::WithinAbs(Vec3f::Zero, 1e-6));
            }
        }
    }
}
