#pragma once

// Zseniálisan egyszerű logger makrókkal.

#ifdef _PFTD_DEBUG

#include <iostream>

#define print(x) std::cout << x << '\n'
#define where() print("[CALLED IN] " << __PRETTY_FUNCTION__)

#else

#define print(x)
#define where()

#endif
