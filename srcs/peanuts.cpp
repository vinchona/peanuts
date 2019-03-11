#include "peanuts.hpp"

#include <climits>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>
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
    for (size_t seed = 0; seed < 1000; seed++)
    {
      std::mt19937 size_generator{seed};
      std::uniform_int_distribution<> size_distribution{INT_MIN, INT_MAX};
      char length = size_distribution(size_generator);
      std::string data{};
      std::mt19937 random_value{length};
      std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
      for (char value = 0; value < length; value++)
        data += std::string{distribution(random_value)};
      test.function(data.c_str(), data.length());
    }
  }
}
