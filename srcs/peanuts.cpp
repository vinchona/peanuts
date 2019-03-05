#include "peanuts.hpp"

#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

int peanuts::Peanuts::add_unittest(std::function<void(void)> function, char const* description)
{
  UnitTest unittest = {function, description};
  unittests.push_back(unittest);
  return unittests.size() - 1;
}

int peanuts::Peanuts::count_unittests() { return unittests.size(); }

void peanuts::Peanuts::execute_unittests()
{
  for (auto const& test : unittests)
  {
    std::cout << test.description << std::endl;
    test.function();
  }
}

int peanuts::Peanuts::add_fuzztest(std::function<void(char const*, size_t)> function, char const* description)
{
  FuzzTest fuzztest = {function, description};
  fuzztests.push_back(fuzztest);
  return fuzztests.size() - 1;
}

int peanuts::Peanuts::count_fuzztests() { return fuzztests.size(); }

void peanuts::Peanuts::execute_fuzztests()
{
  for (auto const& test : fuzztests)
  {
    std::cout << test.description << std::endl;
    test.function("fuzzed data", strlen("fuzzed data") + 1);
  }
}
