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

  void execute_random(size_t trials, size_t size);
  void execute_combination_with_repetitions(size_t trials);
  void execute_combination_without_repetitions(size_t trials);
  void execute_permutation_with_repetitions(size_t trials);
  void execute_permutation_without_repetitions(size_t trials);

  void execute_dummy(size_t trials);
private:
  void safe_execution(size_t size, char const* data);
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
    case Combinatorial::combination_with_repetitions:
      {
        implementation->execute_combination_with_repetitions(trials);
        break;
      }
    case Combinatorial::combination_without_repetitions:
      {
        implementation->execute_combination_without_repetitions(trials);
        break;
      }
    case Combinatorial::permutation_with_repetitions:
      {
        implementation->execute_permutation_with_repetitions(trials);
        break;
      }
    case Combinatorial::permutation_without_repetitions:
      {
        implementation->execute_permutation_without_repetitions(trials);
        break;
      }
    default:
      {
        implementation->execute_dummy(trials);
        break;
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

void peanuts::Fuzzer::Implementation::execute_combination_with_repetitions(size_t trials)
{
  execute_dummy(trials);
}

void peanuts::Fuzzer::Implementation::execute_combination_without_repetitions(size_t trials)
{
  execute_dummy(trials);
}

void peanuts::Fuzzer::Implementation::execute_permutation_with_repetitions( size_t trials)
{
  execute_dummy(trials);
}

void peanuts::Fuzzer::Implementation::execute_permutation_without_repetitions(size_t trials)
{
  execute_dummy(trials);
}

void peanuts::Fuzzer::Implementation::execute_dummy(size_t trials)
{
  for (size_t trial = 0; trial < trials; trial++)
    safe_execution(0, nullptr);
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


