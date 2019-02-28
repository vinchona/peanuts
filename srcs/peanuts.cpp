#include "peanuts.hpp"

#include <functional>
#include <iostream>
#include <vector>

int peanuts::Unittests::add(std::function<void(void)> function, char const* description)
{
  Tests test = {function, description};
  tests.push_back(test);
  return ++count;
}

void peanuts::Unittests::execute()
{
  for (auto const& test : tests)
  {
    std::cout << test.description << std::endl;
    test.function();
  }
}
