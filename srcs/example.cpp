#include <peanuts.hpp>

#include <cstdio>
#include <iostream>
#include <string>

PEANUTS_TEST("Adding test description") { std::cout << "Executing unittest" << std::endl; }

PEANUTS_TEST("Adding other test description") { std::cout << "Executing other unittest" << std::endl; }

PEANUTS_FUZZ("Adding fuzz decription")
{
  static int count = 0;
  std::cout << "size:" << peanuts_fuzz_size << std::endl;
  std::cout << "data:" << peanuts_fuzz_size << std::endl;
  for (size_t size = 0; size < peanuts_fuzz_size; size++)
    printf("%c", peanuts_fuzz_data[size]);
  std::cout << std::endl;
  count++;
}
