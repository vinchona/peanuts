#include "peanuts.hpp"

#include <functional>
#include <iostream>
#include <vector>

int peanuts::Peanuts::add(std::function<void(void)> function, char const* description)
{
  Test test = {function, description};
  tests.push_back(test);
  return ++count;
}

void peanuts::Peanuts::execute()
{
  for (auto const& test : tests)
  {
    std::cout << test.description << std::endl;
    test.function();
  }
}
