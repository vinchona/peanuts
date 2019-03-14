#include "peanuts.hpp"

#include <climits>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <exception>

int peanuts::Tester::add(std::function<void(void)> function, char const* description)
{
  Test test = {function, description};
  tests.push_back(test);
  return tests.size() - 1;
}

int peanuts::Tester::count() { return tests.size(); }

void peanuts::Tester::execute()
{
  for (auto const& test : tests)
  {
    std::cout << test.description << std::endl;
    test.function();
  }
}

int peanuts::Fuzzer::add(std::function<void(size_t, char const*)> function, char const* description)
{
  Test test = {function, description};
  tests.push_back(test);
  return tests.size() - 1;
}

int peanuts::Fuzzer::count() { return tests.size(); }

void peanuts::Fuzzer::execute(Combinatorial combinatorial)
{
  (void)combinatorial;
  for (auto const& test : tests)
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

      try
      {
        test.function(data.length(), data.c_str());
      }
      catch(std::exception const& exception)
      {
        std::cerr << exception.what() << std::endl;
      }
    }
  }
}
