#include "gtest_lite.h"
#include "memtrace.h"

int main()
{
    #ifdef CPORTA
    std::cout << "CPORTA-n vagyunk.\n";
    #endif

    TEST(test1, core)
        SUCCEED();
    END

    return 0;
}