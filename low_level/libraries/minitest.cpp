#include "minitest.hpp"
void Test::addTest(const std::string &testName, std::function<void()> test)
{
    tests.push_back(std::tuple<std::string, std::function<void()>>(testName, test));
}

void Test::run()
{
    if (tests.empty())
    {
        std::cerr << "No tests to run" << std::endl;
        return;
    }
    auto startAll = std::chrono::high_resolution_clock::now();

    for (auto test : tests)
    {
        auto start = std::chrono::high_resolution_clock::now();
        try
        {
            std::get<1>(test)();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << std::get<0>(test) << " passed in " << duration.count() << " milliseconds" << std::endl;
        }
        catch (const std::exception &e)
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cerr << std::get<0>(test) << " failed in " << duration.count() << " milliseconds" << std::endl;
            std::cerr << e.what() << '\n';
        }
    }

    auto endAll = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durationAll = endAll - startAll;
    std::cout << "All tests completed in " << durationAll.count() << " milliseconds" << std::endl;
}

Test::Test() {}



Test testSuite;  // Definición de testSuite