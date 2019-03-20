#include "peanuts.hpp"

#include <climits>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <memory>

peanuts::Tester::Tester() : implementation{std::make_unique<Implementation>()}
{
}

peanuts::Tester::~Tester() = default;

struct peanuts::Tester::Implementation
{
  struct Test
  {
    std::function<void(void)> function;
    char const* description;
  };
  std::vector<Test> tests;
};

int peanuts::Tester::add(std::function<void(void)> function, char const* description)
{
  peanuts::Tester::Implementation::Test test = {function, description};
  implementation->tests.push_back(test);
  return implementation->tests.size() - 1;
}

int peanuts::Tester::count() { return implementation->tests.size(); }

void peanuts::Tester::execute()
{
  for (auto const& test : implementation->tests)
  {
    std::cout << test.description << std::endl;
    test.function();
  }
}

peanuts::Fuzzer::Fuzzer() : implementation{std::make_unique<Implementation>()}
{
}

peanuts::Fuzzer::~Fuzzer() = default;

struct peanuts::Fuzzer::Implementation
{
  struct Test
  {
    std::function<void(size_t, char const*)> function;
    char const* description;
  };

  std::vector<Test> tests;

  void safe_execution(size_t size, char const* data);
  void execute_random(size_t trial, size_t size);
};

int peanuts::Fuzzer::add(std::function<void(size_t, char const*)> function, char const* description)
{
  peanuts::Fuzzer::Implementation::Test test = {function, description};
  implementation->tests.push_back(test);
  return implementation->tests.size() - 1;
}

int peanuts::Fuzzer::count() { return implementation->tests.size(); }

void peanuts::Fuzzer::execute(size_t trials, Combinatorial combinatorial, size_t size)
{
  switch(combinatorial)
  {
    case Combinatorial::random:
      {
        implementation->execute_random(trials, size);
        break;
      }
    default:
      {
        for (size_t trial = 0; trial < trials; trial++)
          implementation->safe_execution(0, nullptr);
        break;
      }
  }
}

void peanuts::Fuzzer::Implementation::safe_execution(size_t size, char const* data)
{
  for (auto const& test : tests)
  {
    try
    {
      test.function(size, data);
    }
    catch (std::exception const& exception)
    {
      std::cerr << exception.what() << std::endl;
    }
  }
}

void peanuts::Fuzzer::Implementation::execute_random(size_t trials, size_t size)
{
  std::mt19937 generator{size};
  std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (size_t trial = 0; trial < trials; trial++)
  {
    std::string data{};
    for (size_t character = 0; character < size; character++)
      data += std::string{distribution(generator)};

    safe_execution(data.size(), data.c_str());
  }
}


