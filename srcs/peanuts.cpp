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
  std::mt19937 generator{size};
  std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (size_t trial = 0; trial < trials; trial++)
  {
    switch(combinatorial)
    {
	    case Combinatorial::random: execute_random(generator, distribution, size); break;
      default: execute_dummy(); break;
    }
  }
}

void peanuts::Fuzzer::execute_random(std::mt19937& generator, std::uniform_int_distribution<char>& distribution, size_t size)
{
  std::string data{};
  for (size_t character = 0; character < size; character++)
    data += std::string{distribution(generator)};
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


