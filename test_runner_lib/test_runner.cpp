#include "test_runner.h"

TestRunner::TestRunner()
{
    fail_count = 0;
}

TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        std::cerr << fail_count << " unit tests failed" << std::endl;
        exit(1);
    }
}
