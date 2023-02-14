#include <mathlib.h>

using namespace mathlib;

int main(int argc, char* argv[])
{
  Vec3d v = Vec3d::OneX;
  Mat34d m = Mat34d::One;
  Vec3d r = m * v;
  return 0;
}
