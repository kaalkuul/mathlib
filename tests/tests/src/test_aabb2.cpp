#include "utils.h"

using namespace mathlib;

TEST_CASE("AABB2", "")
{
    // Types

    SECTION("Real")
    {
        REQUIRE(sizeof(AABB2f::Real) == sizeof(float));
        REQUIRE(sizeof(AABB2d::Real) == sizeof(double));
    }

    // Constants

    SECTION("Vec2f::Zero")
    {
        REQUIRE(Vec2f::Zero.x == 0.0f);
        REQUIRE(Vec2f::Zero.y == 0.0f);
    }

    SECTION("AABB2f::One")
    {
        REQUIRE(AABB2f::One.inf.x == -0.5f);
        REQUIRE(AABB2f::One.inf.y == -0.5f);
        REQUIRE(AABB2f::One.sup.x == 0.5f);
        REQUIRE(AABB2f::One.sup.y == 0.5f);
    }

    // Constructors

    SECTION("AABB2()")
    {
        AABB2f box;
    }

    SECTION("AABB2(const Vec2<Real>& inf, const Vec2<Real>& sup)")
    {
        AABB2f box;
        box = AABB2f(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE(box.inf == Vec2f::Zero);
        REQUIRE(box.sup == Vec2f(1, 2));
    }

    // Setters

    SECTION("set(const Vec2<Real>& point)")
    {
        AABB2f box;
        box.set(Vec2f(1, 2));
        REQUIRE(box.inf == Vec2f(1, 2));
        REQUIRE(box.sup == Vec2f(1, 2));
    }

    SECTION("set(const Vec2<Real>& inf, const Vec2<Real>& sup)")
    {
        AABB2f box;
        box.set(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE(box.inf == Vec2f::Zero);
        REQUIRE(box.sup == Vec2f(1, 2));
    }

    SECTION("set(const CAABB2<Real>& box)")
    {
        AABB2f box;
        box.set(CAABB2f(Vec2f::Zero, Vec2f(1, 2)));
        REQUIRE(box.inf == Vec2f(-0.5f, -1.0f));
        REQUIRE(box.sup == Vec2f(0.5f, 1.0f));
    }

    SECTION("set(int count, const Vec2<Real>* points)")
    {
        Vec2f points[] = {
            Vec2f(-10, -10),
            Vec2f(-1, -1),
            Vec2f(1, 1),
            Vec2f(10, 10)
        };

        AABB2f box;
        box.set(4, points);
        REQUIRE(box.inf == Vec2f(-10, -10));
        REQUIRE(box.sup == Vec2f(10, 10));
    }

    SECTION("set(int count, const Vec2<Real>* points, int stride)")
    {
        Vec2f points[] = {
            Vec2f::OneX * 1000,
            Vec2f(-10, -10),
            Vec2f::OneX * 1000,
            Vec2f(-1, -1),
            Vec2f::OneX * 1000,
            Vec2f(1, 1),
            Vec2f::OneX * 1000,
            Vec2f(10, 10),
            Vec2f::OneX * 1000,
        };

        AABB2f box;
        box.set(4, &points[1], sizeof(Vec2f)*2);
        REQUIRE(box.inf == Vec2f(-10, -10));
        REQUIRE(box.sup == Vec2f(10, 10));
    }

    SECTION("add(const Vec2<Real>& point)")
    {
        AABB2f box;
        box.set(Vec2f::Zero)
            .add(Vec2f(1, 1))
            .add(Vec2f(-1, -1))
            .add(Vec2f::Zero);
        REQUIRE(box.inf == Vec2f(-1, -1));
        REQUIRE(box.sup == Vec2f(1, 1));
    }

    // Create from

    SECTION("from(const Vec2<Real>& point)")
    {
        AABB2f box = AABB2f::from(Vec2f(1, 2));
        REQUIRE(box.inf == Vec2f(1, 2));
        REQUIRE(box.sup == Vec2f(1, 2));
    }

    SECTION("from(const Vec2<Real>& inf, const Vec2<Real>& sup)")
    {
        AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE(box.inf == Vec2f::Zero);
        REQUIRE(box.sup == Vec2f(1, 2));
    }

    SECTION("from(const CAABB2<Real>& box)")
    {
        AABB2f box = AABB2f::from(CAABB2f(Vec2f::Zero, Vec2f(1, 2)));
        REQUIRE(box.inf == Vec2f(-0.5f, -1.0f));
        REQUIRE(box.sup == Vec2f(0.5f, 1.0f));
    }

    SECTION("from(int count, const Vec2<Real>* points)")
    {
        Vec2f points[] = {
            Vec2f(-10, -10),
            Vec2f(-1, -1),
            Vec2f(1, 1),
            Vec2f(10, 10)
        };

        AABB2f box = AABB2f::from(4, points);
        REQUIRE(box.inf == Vec2f(-10, -10));
        REQUIRE(box.sup == Vec2f(10, 10));
    }

    SECTION("from(int count, const Vec2<Real>* points, int stride)")
    {
        Vec2f points[] = {
            Vec2f::OneX * 1000,
            Vec2f(-10, -10),
            Vec2f::OneX * 1000,
            Vec2f(-1, -1),
            Vec2f::OneX * 1000,
            Vec2f(1, 1),
            Vec2f::OneX * 1000,
            Vec2f(10, 10),
            Vec2f::OneX * 1000,
        };

        AABB2f box = AABB2f::from(4, &points[1], sizeof(Vec2f) * 2);
        REQUIRE(box.inf == Vec2f(-10, -10));
        REQUIRE(box.sup == Vec2f(10, 10));
    }

    SECTION("fromIntersection(const AABB2<Real>& a, const AABB2<Real>& b)")
    {
        REQUIRE(AABB2f::fromIntersection(AABB2f::Zero, AABB2f::Zero) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(AABB2f::One, AABB2f::One) == AABB2f::One);
        REQUIRE(AABB2f::fromIntersection(AABB2f::One * 2.0f, AABB2f::One) == AABB2f::One);
        REQUIRE(AABB2f::fromIntersection(AABB2f::One, AABB2f::One * 2.0f) == AABB2f::One);
        
        REQUIRE(AABB2f::fromIntersection(AABB2f::One, AABB2f::One + Vec2f(+0.5f, +0.5f))
                == AABB2f::from(Vec2f(+0.0f, +0.0f), Vec2f(+0.5f, +0.5f)));
        
        REQUIRE(AABB2f::fromIntersection(AABB2f::One, AABB2f::One + Vec2f(+1.0f, +1.0f))
                == AABB2f::from(Vec2f(+0.5f, +0.5f), Vec2f(+0.5f, +0.5f)));

        AABB2f box = AABB2f::One;
        AABB2f box2 = AABB2f::One * 0.1f;

        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(+0.56f, +0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(+0.56f, -0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(-0.56f, -0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(-0.56f, +0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(+0.56f, +0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(+0.56f, -0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(-0.56f, -0.56f)) == AABB2f::Zero);
        REQUIRE(AABB2f::fromIntersection(box, box2 + Vec2f(-0.56f, +0.56f)) == AABB2f::Zero);
    }

    SECTION("fromUnion(const AABB2<Real>& a, const AABB2<Real>& b)")
    {
        REQUIRE(AABB2f::fromUnion(AABB2f::Zero, AABB2f::Zero) == AABB2f::Zero);
        REQUIRE(AABB2f::fromUnion(AABB2f::One, AABB2f::One) == AABB2f::One);
        REQUIRE(AABB2f::fromUnion(AABB2f::One * 2.0f, AABB2f::One) == AABB2f::One * 2.0f);
        REQUIRE(AABB2f::fromUnion(AABB2f::One, AABB2f::One * 2.0f) == AABB2f::One * 2.0f);
    }

    // Assignment operators

    SECTION("operator+= (const Vec2& t)")
    {
        AABB2f box = AABB2f::One;
        box += Vec2f(1, 2);
        REQUIRE(box.inf == Vec2f(0.5f, 1.5f));
        REQUIRE(box.sup == Vec2f(1.5f, 2.5f));
    }

    SECTION("operator-= (const Vec2& t)")
    {
        AABB2f box = AABB2f::One;
        box -= Vec2f(1, 2);
        REQUIRE(box.inf == Vec2f(-1.5f, -2.5f));
        REQUIRE(box.sup == Vec2f(-0.5f, -1.5f));
    }

    SECTION("operator*= (Real k)")
    {
        AABB2f box = AABB2f::One;
        box *= 2.0f;
        REQUIRE(box.inf == Vec2f(-1, -1));
        REQUIRE(box.sup == Vec2f(1, 1));
    }

    SECTION("operator/= (Real k)")
    {
        AABB2f box = AABB2f::One;
        box /= 2.0f;
        REQUIRE(box.inf == Vec2f(-0.25f, -0.25f));
        REQUIRE(box.sup == Vec2f(0.25f, 0.25f));
    }

    // Comparison operators

    SECTION("operator== (const Line3 &rhs)")
    {
        AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE(box == box);
        REQUIRE(box == AABB2f::from(Vec2f::Zero, Vec2f(1, 2)));
        REQUIRE(!(box == AABB2f::One));
    }

    SECTION("operator!= (const Line3 &rhs)")
    {
        AABB2f box = AABB2f::from(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE(!(box != box));
        REQUIRE(box != AABB2f::from(Vec2f::OneX, Vec2f(1, 2)));
        REQUIRE(box != AABB2f::from(Vec2f::Zero, Vec2f(3, 2)));
    }

    // Transformations
    
    SECTION("scaleCentered")
    {
        SECTION("2.0")
        {
            AABB2f box = AABB2f::One;
            box.scaleCentered(2.0f);
            REQUIRE(box.inf == Vec2f(-1, -1));
            REQUIRE(box.sup == Vec2f(1, 1));
        }

        SECTION("0.5")
        {
            AABB2f box = AABB2f::One;
            box.scaleCentered(0.5f);
            REQUIRE(box.inf == Vec2f(-0.25f, -0.25f));
            REQUIRE(box.sup == Vec2f(0.25f, 0.25f));
        }
    }
    
    //  Functions

    SECTION("center() const")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE_THAT(box.center(), Matches::WithinAbs(Vec2f::Zero, 1e-10));
    }

    SECTION("extents() const")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE_THAT(box.extents(), Matches::WithinAbs(Vec2f(0.5f, 0.5f), 1e-10));
    }

    SECTION("size() const")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE_THAT(box.size(), Matches::WithinAbs(Vec2f(1.0f, 1.0f), 1e-10));
    }

    SECTION("innerCircle() const")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE_THAT(box.innerCircle(), Matches::WithinAbs(Circlef(Vec2f::Zero, 0.5f), 1e-10));
    }

    SECTION("outerCircle() const")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE_THAT(box.outerCircle(), Matches::WithinAbs(Circlef(Vec2f::Zero, 0.70710676908493042f), 1e-6));
    }

    SECTION("area()")
    {
        AABB2f box;
        
        box = AABB2f::One;
        REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(1.0f, 1e-10));
        box = AABB2f(Vec2f::Zero, Vec2f(2, 2));
        REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(4.0f, 1e-10));
        box = AABB2f(Vec2f::Zero, Vec2f(1, 2));
        REQUIRE_THAT(box.area(), Catch::Matchers::WithinAbs(2.0f, 1e-10));
    }

    SECTION("isNull()")
    {
        AABB2f box;

        box = AABB2f::One;
        REQUIRE(!box.isNull());
        box = AABB2f(Vec2f::Zero, Vec2f::Zero);
        REQUIRE(box.isNull());
    }

    SECTION("pointAt(const Vec2<Real>& t)")
    {
        AABB2f box;

        box = AABB2f::One;

        REQUIRE_THAT(box.pointAt(Vec2f(0.5f, 0.5f)), Matches::WithinAbs(Vec2f::Zero, 1e-10));

        REQUIRE_THAT(box.pointAt(Vec2f(+1, +1)), Matches::WithinAbs(Vec2f(+0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f(+1,  0)), Matches::WithinAbs(Vec2f(+0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f( 0,  0)), Matches::WithinAbs(Vec2f(-0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f( 0, +1)), Matches::WithinAbs(Vec2f(-0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f(+1, +1)), Matches::WithinAbs(Vec2f(+0.5f, +0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f(+1,  0)), Matches::WithinAbs(Vec2f(+0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f( 0,  0)), Matches::WithinAbs(Vec2f(-0.5f, -0.5f), 1e-10));
        REQUIRE_THAT(box.pointAt(Vec2f( 0, +1)), Matches::WithinAbs(Vec2f(-0.5f, +0.5f), 1e-10));
    }

    SECTION("contains(const Vec2<Real>& point)")
    {
        AABB2f box = AABB2f::One;

        REQUIRE(box.contains(Vec2f::Zero));

        REQUIRE(box.contains(Vec2f(+0.5f, +0.5f)));
        REQUIRE(box.contains(Vec2f(+0.5f, -0.5f)));
        REQUIRE(box.contains(Vec2f(-0.5f, -0.5f)));
        REQUIRE(box.contains(Vec2f(-0.5f, +0.5f)));
        REQUIRE(box.contains(Vec2f(+0.5f, +0.5f)));
        REQUIRE(box.contains(Vec2f(+0.5f, -0.5f)));
        REQUIRE(box.contains(Vec2f(-0.5f, -0.5f)));
        REQUIRE(box.contains(Vec2f(-0.5f, +0.5f)));

        REQUIRE(!box.contains(Vec2f(+0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec2f(+0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec2f(-0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec2f(-0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec2f(+0.51f, +0.51f)));
        REQUIRE(!box.contains(Vec2f(+0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec2f(-0.51f, -0.51f)));
        REQUIRE(!box.contains(Vec2f(-0.51f, +0.51f)));
    }

    SECTION("contains(const AABB2<Real>& box)")
    {
        AABB2f box = AABB2f::One;
        AABB2f box2 = AABB2f::One * 0.1f;

        REQUIRE(box.contains(box2));

        REQUIRE(box.contains(box2 + Vec2f(+0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(+0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(-0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(-0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(+0.45f, +0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(+0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(-0.45f, -0.45f)));
        REQUIRE(box.contains(box2 + Vec2f(-0.45f, +0.45f)));

        REQUIRE(!box.contains(box2 + Vec2f(+0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(+0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(-0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(-0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(+0.46f, +0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(+0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(-0.46f, -0.46f)));
        REQUIRE(!box.contains(box2 + Vec2f(-0.46f, +0.46f)));
    }

    SECTION("hits(Vec2<Real>& hit, Real& t, const Ray2<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next2D(U);

        AABB2f box(Vec2f(-S, -S), Vec2f(S, S));
        float t;
        
        SECTION("U out and towards")
        {
            const float T = D - S;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Ray2f::from(start, direction)) == true);
                REQUIRE(t == T);
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U in to out")
        {
            Vec2f start = Vec2f::Zero;
            Vec2f direction = Vec2f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Ray2f::from(start, direction)) == false);
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Ray2f::from(start, direction)) == false);
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.hits(t, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U out and towards")
        {
            Vec2f start0 = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR).moved(V, DIR).normalized();

            Vec2f starts[] = {
                start0,
                start0.moved(U, DIR*S),
                start0.moved(U, DIR*S*2),
                start0.moved(V, DIR*S),
                start0.moved(V, DIR*S*2)
            };

            int index = GENERATE(0, 1, 2, 3, 4);
            
            Vec2f start = starts[index];
            float T = sqrtf(4.0f*4.0f*2.0f) * S;
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Ray2f::from(start, direction)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinAbs(T, S / 1000.0));
            }
        }
    }

    SECTION("hits(Real& t, const Line2<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next2D(U);

        AABB2f box(Vec2f(-S, -S), Vec2f(S, S));
        float t;
        
        SECTION("U out, across and out")
        {
            const float T = 0.4f;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f end = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Line2f::from(start, end)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinRel(T, 0.0001f));
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U in to out")
        {
            Vec2f start = Vec2f::Zero;
            Vec2f end = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Line2f::from(start, end)) == false);
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U out to in")
        {
            const float T = 0.8f;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f end = Vec2f::Zero;
            
            SECTION("V in") {
                REQUIRE(box.hits(t, Line2f::from(start, end)) == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinRel(T, 0.0001f));
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec2f end = start.moved(U, S);
            
            SECTION("V in") {
                bool result = box.hits(t, Line2f::from(start, end));
                REQUIRE(result == false);
            }

            SECTION("V out") {
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.hits(t, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U and V out and towards diagonally")
        {
            Vec2f start0 = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);

            Vec2f starts[] = {
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
            
            Vec2f start = starts[index];
            Vec2f end = start.moved(U, DIR*D*2.0f).moved(V, DIR*D*2.0f);
            float T = 0.4f;
            
            SECTION("V in") {
                bool result = box.hits(t, Line2f::from(start, end));
                REQUIRE(result == true);
                REQUIRE_THAT(t, Catch::Matchers::WithinAbs(T, 0.0001));
            }
        }
    }

    SECTION("intersects(const AABB2<Real>& box)")
    {
        AABB2f box = AABB2f::One;
        AABB2f box2 = AABB2f::One * 0.1f;

        REQUIRE(box.intersects(box2));

        REQUIRE(box.intersects(box2 + Vec2f(+0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.45f, +0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.45f, -0.45f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.45f, +0.45f)));

        REQUIRE(box.intersects(box2 + Vec2f(+0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.46f, +0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(+0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.46f, -0.46f)));
        REQUIRE(box.intersects(box2 + Vec2f(-0.46f, +0.46f)));

        REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, +0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(+0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, -0.56f)));
        REQUIRE(!box.intersects(box2 + Vec2f(-0.56f, +0.56f)));
    }

    SECTION("intersects(Vec2<Real>& hit, Real& t1, Real& t2, const Ray2<Real>& ray)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next2D(U);

        AABB2f box(Vec2f(-S, -S), Vec2f(S, S));
        float t1, t2;
        
        SECTION("U out and towards")
        {
            const float T1 = D - S;
            const float T2 = D + S;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start, direction)) == true);
                REQUIRE(t1 == T1);
                REQUIRE(t2 == T2);
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U in to out")
        {
            const float T1 = 0.0f;
            const float T2 = S;
            
            Vec2f start = Vec2f::Zero;
            Vec2f direction = Vec3f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start, direction)) == true);
                REQUIRE(t1 == T1);
                REQUIRE(t2 == T2);
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR);
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start, direction)) == false);
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, D), direction)) == false);
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start.moved(V, -D), direction)) == false);
            }
        }

        SECTION("U out and towards")
        {
            Vec2f start0 = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);
            Vec2f direction = Vec2f::Zero.moved(U, DIR).moved(V, DIR).normalized();

            Vec2f starts[] = {
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
            
            Vec2f start = starts[index];
            float T1 = sqrtf(4.0f*4.0f*2.0f) * S;
            float T2 = t2s[index] * S;
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Ray2f::from(start, direction)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinAbs(T1, S / 1000.0));
                REQUIRE_THAT(t2, Catch::Matchers::WithinAbs(T2, S / 1000.0));
            }
        }
    }

    SECTION("intersects(Real& t1, Real& t2, const Line3<Real>& line)")
    {
        auto S = GENERATE(1.0f, 0.001f, 1000.0f);
        auto U = GENERATE(Coord::X, Coord::Y);
        auto DIR = GENERATE(+1.0f, -1.0f);
        
        const float D = S * 5.0f;

        Coord V = next2D(U);

        AABB2f box(Vec2f(-S, -S), Vec2f(S, S));
        float t1, t2;
        
        SECTION("U out, across and out")
        {
            const float T1 = 0.4f;
            const float T2 = 0.6f;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f end = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U in to out")
        {
            const float T1 = 0.0f;
            const float T2 = 0.2f;
            
            Vec2f start = Vec2f::Zero;
            Vec2f end = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U out to in")
        {
            const float T1 = 0.8f;
            const float T2 = 1.0f;
            
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D);
            Vec2f end = Vec2f::Zero;
            
            SECTION("V in") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start, end)) == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinRel(T1, 0.0001f));
                REQUIRE_THAT(t2, Catch::Matchers::WithinRel(T2, 0.0001f));
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U out to out")
        {
            Vec2f start = Vec2f::Zero.moved(U, DIR > 0.0f ? D : -D);
            Vec2f end = start.moved(U, S);
            
            SECTION("V in") {
                bool result = box.intersects(t1, t2, Line2f::from(start, end));
                REQUIRE(result == false);
            }

            SECTION("V out") {
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, +D), end.moved(V, +D))) == false);
                REQUIRE(box.intersects(t1, t2, Line2f::from(start.moved(V, -D), end.moved(V, -D))) == false);
            }
        }

        SECTION("U and V out and towards diagonally")
        {
            Vec2f start0 = Vec2f::Zero.moved(U, DIR > 0.0f ? -D : D).moved(V, DIR > 0.0f ? -D : D);

            Vec2f starts[] = {
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
            
            SECTION("V in") {
                bool result = box.intersects(t1, t2, Line2f::from(start, end));
                REQUIRE(result == true);
                REQUIRE_THAT(t1, Catch::Matchers::WithinAbs(T1, 0.0001));
                REQUIRE_THAT(t2, Catch::Matchers::WithinAbs(T2, 0.0001));
            }
        }
    }

    SECTION("cast()")
    {
        REQUIRE(AABB2f::One.cast<double>() == AABB2d::One);

        REQUIRE(AABB2d::One.cast<float>() == AABB2f::One);
    }

    SECTION("Matches::WithinAbs")
    {
        REQUIRE_THAT(AABB2f::One, Matches::WithinAbs(AABB2f::One));
    }
}

