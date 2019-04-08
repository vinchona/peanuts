#include "peanuts.hpp"

#include <memory>
#include <vector>

peanuts::Tester::Tester() : implementation{std::make_unique<Implementation>()} {}

peanuts::Tester::~Tester() = default;

struct peanuts::Tester::Implementation
{
  std::vector<Test> tests;
};

size_t peanuts::Tester::add(Test test)
{
  implementation->tests.push_back(test);
  return implementation->tests.size() - 1;
}

std::vector<peanuts::Tester::Test> peanuts::Tester::tests() { return implementation->tests; }

peanuts::Fuzzer::Fuzzer() : implementation{std::make_unique<Implementation>()} {}

peanuts::Fuzzer::~Fuzzer() = default;

struct peanuts::Fuzzer::Implementation
{
  std::vector<Test> tests;
};

size_t peanuts::Fuzzer::add(Test test)
{
  implementation->tests.push_back(test);
  return implementation->tests.size() - 1;
}

std::vector<peanuts::Fuzzer::Test> peanuts::Fuzzer::tests()
{
  return implementation->tests;
}
