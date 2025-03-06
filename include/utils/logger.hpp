#pragma once

#include <iostream>

#define print(x) std::cout << x << '\n'
#define where() print("[CALLED IN] " << __PRETTY_FUNCTION__)
