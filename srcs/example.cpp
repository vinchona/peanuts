#include <peanuts.hpp>

#include <cassert>
#include <iostream>

PEANUTS_TEST("Adding test description") { std::cout << "Executing unittest" << std::endl; }

PEANUTS_TEST("Adding other test description") { std::cout << "Executing other unittest" << std::endl; }

PEANUTS_FUZZ("Adding fuzz decription")
{
  static int count = 0;
  std::cout << "Executing fuzz test[" << count << "]" << std::endl;
  std::cout << "size:" << peanuts_fuzz_size << std::endl;
  std::cout << "data:" << peanuts_fuzz_data << std::endl;
  count++;
}
