#include <peanuts.hpp>

#include <iostream>

PEANUTS_UNITTEST("Adding test description") { std::cout << "Executing unittest" << std::endl; }

PEANUTS_UNITTEST("Adding other test description") { std::cout << "Executing other unittest" << std::endl; }

PEANUTS_FUZZTEST("Adding fuzz decription")
{
  std::cout << "Executing fuzz test" << std::endl;
  if (peanuts_fuzz_data != nullptr && peanuts_fuzz_size != 0)
  {
    std::cout << "data:" << peanuts_fuzz_data << std::endl;
    std::cout << "size:" << peanuts_fuzz_size << std::endl;
  }
}
