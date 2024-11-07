#pragma once

#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>


#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/internal/catch_enforce.hpp>

#include "mathlib.h"

#include "mathlib_testlib.h"

const float CPI6 = 0.86602f;
const float SPI6 = 0.50000f;

const float CPI4 = 0.70711f;
const float SPI4 = 0.70711f;

const float CPI3 = 0.50000f;
const float SPI3 = 0.86602f;

const int N_TEST_RUNS = 1000;
