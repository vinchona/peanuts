#include "peanuts.hpp"

#include <climits>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

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

void peanuts::Fuzzer::execute(size_t trials, Combinatorial combinatorial, size_t size)
{
  for (size_t trial = 0; trial < trials; trial++)
  {
    switch(combinatorial)
    {
      case Combinatorial::random: execute_random(trial, size); break;
      default: execute_dummy(); break;
    }
  }
}

void peanuts::Fuzzer::execute_random(size_t seed, size_t size_max)
{
  std::mt19937 size_generator{seed};
  std::uniform_int_distribution<size_t> size_distribution{0, size_max};
  size_t length = size_distribution(size_generator);
  std::string data{};
  std::mt19937 random_value{length};
  std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (size_t value = 0; value < length; value++)
    data += std::string{distribution(random_value)};
  for (auto const& test : tests)
  {
    try
    {
      test.function(data.size(), data.c_str());
    }
    catch (std::exception const& exception)
    {
      std::cerr << exception.what() << std::endl;
    }
  }
}

void peanuts::Fuzzer::execute_dummy()
{
  for (auto const& test : tests)
  {
    try
    {
      test.function(0, nullptr);
    }
    catch (std::exception const& exception)
    {
      std::cerr << exception.what() << std::endl;
    }
  }
}


