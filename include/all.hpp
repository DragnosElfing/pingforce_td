#pragma once

// Ez egy precompiled header fájl.

// STL
#include <cmath>
#include <vector>
#include <functional>
#include <optional>
#include <utility>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>
#include <ctime>
#include <ios>
#include <limits>
#include <filesystem>
#include <stdexcept>
#include <random>
#include <fstream>

// SFML
#if not defined(_PFTD_TEST) && not defined(CPORTA)
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#endif

// Own
#include "utils/logger.hpp"
#include "utils/substitute_types.hpp"
