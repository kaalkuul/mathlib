#include "utils.h"

using namespace mathlib;

TEST_CASE("AABB3", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(AABB3f::Real) == sizeof(float));
        REQUIRE(sizeof(AABB3d::Real) == sizeof(double));
    }

    // Constants

    SECTION("AABB3f::One")
    {
        REQUIRE(AABB3f::One.inf.x == -0.5f);
        REQUIRE(AABB3f::One.inf.y == -0.5f);
        REQUIRE(AABB3f::One.inf.z == -0.5f);
        REQUIRE(AABB3f::One.sup.x == 0.5f);
        REQUIRE(AABB3f::One.sup.y == 0.5f);
        REQUIRE(AABB3f::One.sup.z == 0.5f);
    }

    // Constructors

    SECTION("AABB3()")
    {
        AABB3f box;
    }

    SECTION("AABB3(const Vec3<Real>& inf, const Vec3<Real>& sup)")
    {
        AABB3f box;
        box = AABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE(box.inf == Vec3f::Zero);
        REQUIRE(box.sup == Vec3f(1, 2, 3));
    }

    // Setters

    SECTION("set(const Vec3<Real>& point)")
    {
        AABB3f box;
        box.set(Vec3f(1, 2, 3));
        REQUIRE(box.inf == Vec3f(1, 2, 3));
        REQUIRE(box.sup == Vec3f(1, 2, 3));
    }

    SECTION("set(const Vec3<Real>& inf, const Vec3<Real>& sup)")
    {
        AABB3f box;
        box.set(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE(box.inf == Vec3f::Zero);
        REQUIRE(box.sup == Vec3f(1, 2, 3));
    }

    SECTION("set(const CAABB3<Real>& box)")
    {
        AABB3f box;
        box.set(CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
        REQUIRE(box.inf == Vec3f(-0.5f, -1.0f, -1.5f));
        REQUIRE(box.sup == Vec3f(0.5f, 1.0f, 1.5f));
    }

    SECTION("set(int count, const Vec3<Real>* points)")
    {
        Vec3f points[] = {
            Vec3f(-10, -10, -10),
            Vec3f(-1, -1, -1),
            Vec3f(1, 1, 1),
            Vec3f(10, 10, 10)
        };

        AABB3f box;
        box.set(4, points);
        REQUIRE(box.inf == Vec3f(-10, -10, -10));
        REQUIRE(box.sup == Vec3f(10, 10, 10));
    }

    SECTION("set(int count, const Vec3<Real>* points, int stride)")
    {
        Vec3f points[] = {
            Vec3f::OneX * 1000,
            Vec3f(-10, -10, -10),
            Vec3f::OneX * 1000,
            Vec3f(-1, -1, -1),
            Vec3f::OneX * 1000,
            Vec3f(1, 1, 1),
            Vec3f::OneX * 1000,
            Vec3f(10, 10, 10),
            Vec3f::OneX * 1000,
        };

        AABB3f box;
        box.set(4, &points[1], sizeof(Vec3f)*2);
        REQUIRE(box.inf == Vec3f(-10, -10, -10));
        REQUIRE(box.sup == Vec3f(10, 10, 10));
    }

    SECTION("add(const Vec3<Real>& point)")
    {
        AABB3f box;
        box.set(Vec3f::Zero)
            .add(Vec3f(1, 1, 1))
            .add(Vec3f(-1, -1, -1))
            .add(Vec3f::Zero);
        REQUIRE(box.inf == Vec3f(-1, -1, -1));
        REQUIRE(box.sup == Vec3f(1, 1, 1));
    }

    // Create from

    SECTION("from(const Vec3<Real>& point)")
    {
        AABB3f box = AABB3f::from(Vec3f(1, 2, 3));
        REQUIRE(box.inf == Vec3f(1, 2, 3));
        REQUIRE(box.sup == Vec3f(1, 2, 3));
    }

    SECTION("from(const Vec3<Real>& inf, const Vec3<Real>& sup)")
    {
        AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE(box.inf == Vec3f::Zero);
        REQUIRE(box.sup == Vec3f(1, 2, 3));
    }

    SECTION("from(const CAABB3<Real>& box)")
    {
        AABB3f box = AABB3f::from(CAABB3f(Vec3f::Zero, Vec3f(1, 2, 3)));
        REQUIRE(box.inf == Vec3f(-0.5f, -1.0f, -1.5f));
        REQUIRE(box.sup == Vec3f(0.5f, 1.0f, 1.5f));
    }

    SECTION("from(int count, const Vec3<Real>* points)")
    {
        Vec3f points[] = {
            Vec3f(-10, -10, -10),
            Vec3f(-1, -1, -1),
            Vec3f(1, 1, 1),
            Vec3f(10, 10, 10)
        };

        AABB3f box = AABB3f::from(4, points);
        REQUIRE(box.inf == Vec3f(-10, -10, -10));
        REQUIRE(box.sup == Vec3f(10, 10, 10));
    }

    SECTION("from(int count, const Vec3<Real>* points, int stride)")
    {
        Vec3f points[] = {
            Vec3f::OneX * 1000,
            Vec3f(-10, -10, -10),
            Vec3f::OneX * 1000,
            Vec3f(-1, -1, -1),
            Vec3f::OneX * 1000,
            Vec3f(1, 1, 1),
            Vec3f::OneX * 1000,
            Vec3f(10, 10, 10),
            Vec3f::OneX * 1000,
        };

        AABB3f box = AABB3f::from(4, &points[1], sizeof(Vec3f) * 2);
        REQUIRE(box.inf == Vec3f(-10, -10, -10));
        REQUIRE(box.sup == Vec3f(10, 10, 10));
    }

    SECTION("fromIntersection(const AABB3<Real>& a, const AABB3<Real>& b)")
    {
        REQUIRE(AABB3f::fromIntersection(AABB3f::Zero, AABB3f::Zero) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(AABB3f::One, AABB3f::One) == AABB3f::One);
        REQUIRE(AABB3f::fromIntersection(AABB3f::One * 2.0f, AABB3f::One) == AABB3f::One);
        REQUIRE(AABB3f::fromIntersection(AABB3f::One, AABB3f::One * 2.0f) == AABB3f::One);
        
        REQUIRE(AABB3f::fromIntersection(AABB3f::One, AABB3f::One + Vec3f(+0.5f, +0.5f, +0.0f))
                == AABB3f::from(Vec3f(+0.0f, +0.0f, -0.5f), Vec3f(+0.5f, +0.5f, +0.5f)));
        
        REQUIRE(AABB3f::fromIntersection(AABB3f::One, AABB3f::One + Vec3f(+1.0f, +1.0f, +0.0f))
                == AABB3f::from(Vec3f(+0.5f, +0.5f, -0.5f), Vec3f(+0.5f, +0.5f, +0.5f)));
        
        REQUIRE(AABB3f::fromIntersection(AABB3f::One, AABB3f::One + Vec3f(+1.0f, +1.0f, +1.0f))
                == AABB3f::from(Vec3f(+0.5f, +0.5f, +0.5f), Vec3f(+0.5f, +0.5f, +0.5f)));

        AABB3f box = AABB3f::One;
        AABB3f box2 = AABB3f::One * 0.1f;

        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(+0.56f, +0.56f, +0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(+0.56f, -0.56f, +0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(-0.56f, -0.56f, +0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(-0.56f, +0.56f, +0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(+0.56f, +0.56f, -0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(+0.56f, -0.56f, -0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(-0.56f, -0.56f, -0.56f)) == AABB3f::Zero);
        REQUIRE(AABB3f::fromIntersection(box, box2 + Vec3f(-0.56f, +0.56f, -0.56f)) == AABB3f::Zero);
    }

    SECTION("fromUnion(const AABB3<Real>& a, const AABB3<Real>& b)")
    {
        REQUIRE(AABB3f::fromUnion(AABB3f::Zero, AABB3f::Zero) == AABB3f::Zero);
        REQUIRE(AABB3f::fromUnion(AABB3f::One, AABB3f::One) == AABB3f::One);
        REQUIRE(AABB3f::fromUnion(AABB3f::One * 2.0f, AABB3f::One) == AABB3f::One * 2.0f);
        REQUIRE(AABB3f::fromUnion(AABB3f::One, AABB3f::One * 2.0f) == AABB3f::One * 2.0f);
    }

    // Assignment operators

    SECTION("operator+= (const Vec3& t)")
    {
        AABB3f box = AABB3f::One;
        box += Vec3f(1, 2, 3);
        REQUIRE(box.inf == Vec3f(0.5f, 1.5f, 2.5f));
        REQUIRE(box.sup == Vec3f(1.5f, 2.5f, 3.5f));
    }

    SECTION("operator-= (const Vec3& t)")
    {
        AABB3f box = AABB3f::One;
        box -= Vec3f(1, 2, 3);
        REQUIRE(box.inf == Vec3f(-1.5f, -2.5f, -3.5f));
        REQUIRE(box.sup == Vec3f(-0.5f, -1.5f, -2.5f));
    }

    SECTION("operator*= (Real k)")
    {
        AABB3f box = AABB3f::One;
        box *= 2.0f;
        REQUIRE(box.inf == Vec3f(-1, -1, -1));
        REQUIRE(box.sup == Vec3f(1, 1, 1));
    }

    SECTION("operator/= (Real k)")
    {
        AABB3f box = AABB3f::One;
        box /= 2.0f;
        REQUIRE(box.inf == Vec3f(-0.25f, -0.25f, -0.25f));
        REQUIRE(box.sup == Vec3f(0.25f, 0.25f, 0.25f));
    }

    // Comparison operators

    SECTION("operator== (const Line3 &rhs)")
    {
        AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE(box == box);
        REQUIRE(box == AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3)));
        REQUIRE(!(box == AABB3f::One));
    }

    SECTION("operator!= (const Line3 &rhs)")
    {
        AABB3f box = AABB3f::from(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE(!(box != box));
        REQUIRE(box != AABB3f::from(Vec3f::OneX, Vec3f(1, 2, 3)));
        REQUIRE(box != AABB3f::from(Vec3f::Zero, Vec3f(3, 2, 1)));
    }

    //  Functions

    SECTION("center() const")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE_THAT(box.center(), Matches::WithinAbs(Vec3f::Zero, 1e-10));
    }

    SECTION("extents() const")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE_THAT(box.extents(), Matches::WithinAbs(Vec3f(0.5f, 0.5f, 0.5f), 1e-10));
    }

    SECTION("size() const")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec3f(1.0f, 1.0f, 1.0f), 1e-10));
    }

    SECTION("innerSphere() const")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE_THAT(box.innerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.5f), 1e-10));
    }

    SECTION("outerSphere() const")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE_THAT(box.outerSphere(), Matches::WithinAbs(Spheref(Vec3f::Zero, 0.866025f), 1e-6));
    }

    SECTION("volume()")
    {
        AABB3f box;
        
        box = AABB3f::One;
        REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        box = AABB3f(Vec3f::Zero, Vec3f(2, 2, 2));
        REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(8.0f, 1e-10));
        box = AABB3f(Vec3f::Zero, Vec3f(1, 2, 3));
        REQUIRE_THAT(box.volume(), Catch::Matchers::WithinAbs(6.0f, 1e-10));
    }

    SECTION("isNull()")
    {
        AABB3f box;

        box = AABB3f::One;
        REQUIRE(!box.isNull());
        box = AABB3f(Vec3f::Zero, Vec3f::Zero);
        REQUIRE(box.isNull());
    }

    SECTION("pointAt(Real t)")
    {
        AABB3f box;

        box = AABB3f::One;

        REQUIRE_THAT(box.pointAt(Vec3f(0.5f, 0.5f, 0.5f)), Matches::WithinAbs(Vec3f::Zero, 1e-10));

        REQUIRE_THAT(box.pointAt(Vec3f(+1, +1, +1)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f(+1,  0, +1)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f( 0,  0, +1)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f( 0, +1, +1)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f(+1, +1,  0)), Matches::WithinAbs(Vec3f(+0.5f, +0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f(+1,  0,  0)), Matches::WithinAbs(Vec3f(+0.5f, -0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f( 0,  0,  0)), Matches::WithinAbs(Vec3f(-0.5f, -0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec3f( 0, +1,  0)), Matches::WithinAbs(Vec3f(-0.5f, +0.5f, -0.5f), 1e-10));
    }

    SECTION("contains(const Vec3<Real>& point)")
    {
        AABB3f box = AABB3f::One;

        REQUIRE(box.contains(Vec3f::Zero));

        REQUIRE(box.contains(Vec3f(+0.5f, +0.5f, +0.5f)));
        REQUIRE(box.contains(Vec3f(+0.5f, -0.5f, +0.5f)));
        REQUIRE(box.contains(Vec3f(-0.5f, -0.5f, +0.5f)));
        REQUIRE(box.contains(Vec3f(-0.5f, +0.5f, +0.5f)));
        REQUIRE(box.contains(Vec3f(+0.5f, +0.5f, -0.5f)));
        REQUIRE(box.contains(Vec3f(+0.5f, -0.5f, -0.5f)));
        REQUIRE(box.contains(Vec3f(-0.5f, -0.5f, -0.5f)));
        REQUIRE(box.contains(Vec3f(-0.5f, +0.5f, -0.5f)));

        REQUIRE(!box.contains(Vec3f(+0.51f, +0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec3f(+0.51f, -0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec3f(-0.51f, -0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec3f(-0.51f, +0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec3f(+0.51f, +0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec3f(+0.51f, -0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec3f(-0.51f, -0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec3f(-0.51f, +0.51f, -0.51f)));
    }

    SECTION("contains(const Sphere<Real>& sphere)")
    {
        AABB3f box = AABB3f::One;
        Spheref sphere = Spheref::One * 0.1f;

        REQUIRE(box.contains(sphere));

        REQUIRE(box.contains(sphere + Vec3f(+0.4f, +0.4f, +0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(+0.4f, -0.4f, +0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(-0.4f, -0.4f, +0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(-0.4f, +0.4f, +0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(+0.4f, +0.4f, -0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(+0.4f, -0.4f, -0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(-0.4f, -0.4f, -0.4f)));
        REQUIRE(box.contains(sphere + Vec3f(-0.4f, +0.4f, -0.4f)));

        REQUIRE(!box.contains(sphere + Vec3f(+0.41f, +0.41f, +0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(+0.41f, -0.41f, +0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(-0.41f, -0.41f, +0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(-0.41f, +0.41f, +0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(+0.41f, +0.41f, -0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(+0.41f, -0.41f, -0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(-0.41f, -0.41f, -0.41f)));
        REQUIRE(!box.contains(sphere + Vec3f(-0.41f, +0.41f, -0.41f)));
    }

    SECTION("contains(const AABB3<Real>& box)")
    {
        AABB3f box = AABB3f::One;
        AABB3f box2 = AABB3f::One * 0.1f;

        REQUIRE(box.contains(box2));

        REQUIRE(box.contains(box2 + Vec3f(+0.45f, +0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(+0.45f, -0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(-0.45f, -0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(-0.45f, +0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(+0.45f, +0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(+0.45f, -0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(-0.45f, -0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec3f(-0.45f, +0.45f, -0.45f)));

        REQUIRE(!box.contains(box2 + Vec3f(+0.46f, +0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(+0.46f, -0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(-0.46f, -0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(-0.46f, +0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(+0.46f, +0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(+0.46f, -0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(-0.46f, -0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec3f(-0.46f, +0.46f, -0.46f)));
    }

    SECTION("hits(Real& t, const Ray3<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y, Coord::Z);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next3D(U);
        Coord W = next3D(V);

        AABB3f box(Vec3f(-S, -S, -S), Vec3f(S, S, S));
        float t;
        
        SECTION("U out and towards")
        {
            const float T = D - S;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start, direction)) == true);
                REQUIRE(t == T);
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U in to out")
        {
            Vec3f start = Vec3f::Zero;
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start, direction)) == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start, direction)) == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U out and towards")
        {
            Vec3f start0 = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR).moved(V, DIR).normalized();

            Vec3f starts[] = {
                start0,
                start0.moved(U, DIR*S),
                start0.moved(U, DIR*S*2),
                start0.moved(V, DIR*S),
                start0.moved(V, DIR*S*2)
            };

            int index = GENERATE(0, 1, 2, 3, 4);
            
            Vec3f start = starts[index];
            float T = sqrtf(4.0f*4.0f*2.0f) * S;
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Ray3f::from(start, direction)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinAbs(T, S / 1000.0));
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.hits(t, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }
    }

    SECTION("hits(Real& t, const Line3<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y, Coord::Z);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next3D(U);
        Coord W = next3D(V);

        AABB3f box(Vec3f(-S, -S, -S), Vec3f(S, S, S));
        float t;
        
        SECTION("U out, across and out")
        {
            const float T = 0.4f;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f end = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Line3f::from(start, end)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinRel(T, 0.0001f));
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U in to out")
        {
            Vec3f start = Vec3f::Zero;
            Vec3f end = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Line3f::from(start, end)) == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U out to in")
        {
            const float T = 0.8f;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f end = Vec3f::Zero;
            
            SECTION("V in, W in") {
                REQUIRE(box.hits(t, Line3f::from(start, end)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinRel(T, 0.0001f));
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec3f end = start.moved(U, S);
            
            SECTION("V in, W in") {
                bool result = box.hits(t, Line3f::from(start, end));
                REQUIRE(result == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U and V out and towards diagonally")
        {
            Vec3f start0 = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);

            Vec3f starts[] = {
                start0,
                start0.moved(U, DIR*S),
                start0.moved(U, DIR*S*2),
                start0.moved(V, DIR*S),
                start0.moved(V, DIR*S*2)
            };

            float t2s[] = {
                0.6f,
                0.5f,
                0.4f,
                0.5f,
                0.4f
            };

            int index = GENERATE(0, 1, 2, 3, 4);
            
            Vec3f start = starts[index];
            Vec3f end = start.moved(U, DIR*D*2.0f).moved(V, DIR*D*2.0f);
            float T = 0.4f;
            
            SECTION("V in, W in") {
                bool result = box.hits(t, Line3f::from(start, end));
                REQUIRE(result == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinAbs(T, 0.0001));
            }

            SECTION("V in, W out") {
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.hits(t, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }
    }

    SECTION("intersects(const AABB3<Real>& box)")
    {
        AABB3f box = AABB3f::One;
        AABB3f box2 = AABB3f::One * 0.1f;

        REQUIRE(box.intersects(box2));

        REQUIRE(box.intersects(box2 + Vec3f(+0.45f, +0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.45f, -0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.45f, -0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.45f, +0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.45f, +0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.45f, -0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.45f, -0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.45f, +0.45f, -0.45f)));

        REQUIRE(box.intersects(box2 + Vec3f(+0.46f, +0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.46f, -0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.46f, -0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.46f, +0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.46f, +0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(+0.46f, -0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.46f, -0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec3f(-0.46f, +0.46f, -0.46f)));

        REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, +0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, -0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, -0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, +0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, +0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(+0.56f, -0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, -0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec3f(-0.56f, +0.56f, -0.56f)));
    }

    SECTION("intersects(Real& t1, Real& t2, const Ray3<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y, Coord::Z);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next3D(U);
        Coord W = next3D(V);

        AABB3f box(Vec3f(-S, -S, -S), Vec3f(S, S, S));
        float t1, t2;
        
        SECTION("U out and towards")
        {
            const float T1 = D - S;
            const float T2 = D + S;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start, direction)) == true);
                REQUIRE(t1 == T1);
                REQUIRE(t2 == T2);
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U in to out")
        {
            const float T1 = 0.0f;
            const float T2 = S;
            
            Vec3f start = Vec3f::Zero;
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start, direction)) == true);
                REQUIRE(t1 == T1);
                REQUIRE(t2 == T2);
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start, direction)) == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(V, -D), direction)) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }

        SECTION("U out and towards")
        {
            Vec3f start0 = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);
            Vec3f direction = Vec3f::Zero.moved(U, DIR).moved(V, DIR).normalized();

            Vec3f starts[] = {
                start0,
                start0.moved(U, DIR*S),
                start0.moved(U, DIR*S*2),
                start0.moved(V, DIR*S),
                start0.moved(V, DIR*S*2)
            };

            float t2s[] = {
                sqrtf(6.0f*6.0f*2.0f),
                sqrtf(5.0f*5.0f*2.0f),
                sqrtf(4.0f*4.0f*2.0f),
                sqrtf(5.0f*5.0f*2.0f),
                sqrtf(4.0f*4.0f*2.0f)
            };

            int index = GENERATE(0, 1, 2, 3, 4);
            
            Vec3f start = starts[index];
            float T1 = sqrtf(4.0f*4.0f*2.0f) * S;
            float T2 = t2s[index] * S;
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start, direction)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinAbs(T1, S / 1000.0));
                REQUIRE_THAT(t2, Catch::Matchers::WithinAbs(T2, S / 1000.0));
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray3f::from(start.moved(W, -D), direction)) == false);
            }
        }
    }

    SECTION("intersects(Real& t1, Real& t2, const Line3<Real>& line)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y, Coord::Z);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next3D(U);
        Coord W = next3D(V);

        AABB3f box(Vec3f(-S, -S, -S), Vec3f(S, S, S));
        float t1, t2;
        
        SECTION("U out, across and out")
        {
            const float T1 = 0.4f;
            const float T2 = 0.6f;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f end = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U in to out")
        {
            const float T1 = 0.0f;
            const float T2 = 0.2f;
            
            Vec3f start = Vec3f::Zero;
            Vec3f end = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U out to in")
        {
            const float T1 = 0.8f;
            const float T2 = 1.0f;
            
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec3f end = Vec3f::Zero;
            
            SECTION("V in, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec3f start = Vec3f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec3f end = start.moved(U, S);
            
            SECTION("V in, W in") {
                bool result = box.intersects(t1, t2, Line3f::from(start, end));
                REQUIRE(result == false);
            }

            SECTION("V out, W in") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }

        SECTION("U and V out and towards diagonally")
        {
            Vec3f start0 = Vec3f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);

            Vec3f starts[] = {
                start0,
                start0.moved(U, DIR*S),
                start0.moved(U, DIR*S*2),
                start0.moved(V, DIR*S),
                start0.moved(V, DIR*S*2)
            };

            float t2s[] = {
                0.6f,
                0.5f,
                0.4f,
                0.5f,
                0.4f
            };

            int index = GENERATE(0, 1, 2, 3, 4);
            
            Vec3f start = starts[index];
            Vec3f end = start.moved(U, DIR*D*2.0f).moved(V, DIR*D*2.0f);
            float T1 = 0.4f;
            float T2 = t2s[index];
            
            SECTION("V in, W in") {
                bool result = box.intersects(t1, t2, Line3f::from(start, end));
                REQUIRE(result == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinAbs(T1, 0.0001));
                REQUIRE_THAT(t2, Catch::Matchers::WithinAbs(T2, 0.0001));
            }

            SECTION("V in, W out") {
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, +D), end.moved(W, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line3f::from(start.moved(W, -D), end.moved(W, -D))) == false);
            }
        }
    }

    SECTION("cast()")
    {
        REQUIRE(AABB3f::One.cast<double>() == AABB3d::One);

        REQUIRE(AABB3d::One.cast<float>() == AABB3f::One);
    }

    SECTION("Matches::WithinAbs")
    {
        REQUIRE_THAT(AABB3f::One, Matches::WithinAbs(AABB3f::One));
    }
}
