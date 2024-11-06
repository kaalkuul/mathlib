#include "utils.h"

using namespace mathlib;


TEST_CASE("Frustum", "")
{
    Vec3f cube[] = {
        Vec3f(+1, +1, +1),
        Vec3f(+1, -1, +1),
        Vec3f(-1, -1, +1),
        Vec3f(-1, +1, +1),
        Vec3f(+1, +1, -1),
        Vec3f(+1, -1, -1),
        Vec3f(-1, -1, -1),
        Vec3f(-1, +1, -1),
    };
    Frustumf frustum;

    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(Frustumf::Real) == sizeof(float));
        REQUIRE(sizeof(Frustumd::Real) == sizeof(double));
    }

    SECTION("set(const Vec3<Real>* corners)")
    {
        SECTION("plane normals are ok")
        {
            frustum.set(cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].normal, Matches::WithinAbs(-Vec3f::OneZ));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].normal, Matches::WithinAbs(Vec3f::OneZ));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].normal, Matches::WithinAbs(-Vec3f::OneX));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].normal, Matches::WithinAbs(Vec3f::OneY));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].normal, Matches::WithinAbs(Vec3f::OneX));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].normal, Matches::WithinAbs(-Vec3f::OneY));
        }

        SECTION("corners are on planes")
        {
            frustum.set(cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
        }
    }

    SECTION("set(const Mat34<Real>& ltw, const Vec3<Real>* corners)")
    {
        Mat34f ltw = Mat34f::from(Coord::Z, Constantsf::PI);

        SECTION("plane normals are ok")
        {
            frustum.set(ltw, cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].normal, Matches::WithinAbs(-Vec3f::OneZ));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].normal, Matches::WithinAbs(Vec3f::OneZ));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].normal, Matches::WithinAbs(Vec3f::OneX));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].normal, Matches::WithinAbs(-Vec3f::OneY));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].normal, Matches::WithinAbs(-Vec3f::OneX));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].normal, Matches::WithinAbs(Vec3f::OneY));
        }

        SECTION("corners are on planes")
        {
            frustum.set(ltw, cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
        }
    }

    SECTION("set(const Mat4<Real>& ltw, const Vec3<Real>* corners)")
    {
        Mat4f ltw = Mat4f::from(Coord::Z, Constantsf::PI);

        SECTION("plane normals are ok")
        {
            frustum.set(ltw, cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].normal, Matches::WithinAbs(-Vec3f::OneZ));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].normal, Matches::WithinAbs(Vec3f::OneZ));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].normal, Matches::WithinAbs(Vec3f::OneX));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].normal, Matches::WithinAbs(-Vec3f::OneY));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].normal, Matches::WithinAbs(-Vec3f::OneX));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].normal, Matches::WithinAbs(Vec3f::OneY));
        }

        SECTION("corners are on planes")
        {
            frustum.set(ltw, cube);

            // Far clipping plane
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[0].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Near clipping plane
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[1].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Left plane
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[2].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Top plane
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[3]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[3].distance(frustum.corners[7]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Right plane
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[0]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[4]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[4].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));

            // Bottom plane
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[1]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[2]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[5]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
            REQUIRE_THAT(frustum.planes[5].distance(frustum.corners[6]), Catch::Matchers::WithinAbs(0.0f, 0.0001f));
        }
    }

    SECTION("contains(const Vec3<Real>& p)")
    {
        SECTION("cube contains its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(frustum.contains(cube[i]));
            }
        }

        SECTION("cube contains its corners moved inwards")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(frustum.contains(cube[i] * 0.5f));
            }
        }

        SECTION("cube does not contain its corners moved outwards")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(!frustum.contains(cube[i] * 1.5f));
            }
        }
    }

    SECTION("contains(const Vec4<Real>& p)")
    {
        SECTION("cube contains its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(frustum.contains(Vec4f(cube[i])));
            }
        }

        SECTION("cube contains its corners moved inwards")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(frustum.contains(Vec4f(cube[i] * 0.5f)));
            }
        }

        SECTION("cube does not contain its corners moved outwards")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                REQUIRE(!frustum.contains(Vec4f(cube[i] * 1.5f)));
            }
        }
    }

    SECTION("contains(const Sphere<Real>& sphere)")
    {
        SECTION("cube contains its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i], 0.0f);
                REQUIRE(frustum.contains(sphere));
            }
        }

        SECTION("cube contains spheres moved moved inwards from its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i] * 0.9f, 0.1f);
                REQUIRE(frustum.contains(sphere));
            }
        }

        SECTION("cube does not contain spheres moved moved outwards from its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i] * 0.91f, 0.1f);
                REQUIRE(!frustum.contains(sphere));
            }
        }
    }

    SECTION("intersects(const Sphere<Real>& sphere)")
    {
        SECTION("cube intersects with its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i], 0.0f);
                REQUIRE(frustum.intersects(sphere));
            }
        }

        SECTION("cube intersects with spheres tangent to its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i] * 1.5f, 0.5f);
                REQUIRE(frustum.intersects(sphere));
            }
        }

        SECTION("cube does not intersect with spheres moved moved outwards from its corners")
        {
            frustum.set(cube);
            for (int i = 0; i < 8; i++)
            {
                Spheref sphere(cube[i] * 1.51f, 0.5f);
                REQUIRE(!frustum.intersects(sphere));
            }
        }
        
        SECTION("Matches::WithinAbs")
        {
            frustum.set(cube);
            REQUIRE_THAT(frustum, Matches::WithinAbs(frustum));
        }
    }
}

