#include <peanuts.hpp>

#include <cstdio>
#include <iostream>

PEANUTS_TEST("Adding test description") { std::cout << "Executing test" << std::endl; }

PEANUTS_TEST("Adding another test description") { std::cout << "Executing another test" << std::endl; }

PEANUTS_FUZZ("Adding fuzz decription")
{
  std::cout << "Executing fuzztest" << std::endl;
  std::cout << "size:" << args.size << std::endl;
  std::cout << "data:";
  for (size_t size = 0; size < args.size; size++)
    ::printf("%c", args.data[size]);
  std::cout << std::endl << std::flush;
}

PEANUTS_FUZZ("Adding another fuzz decription")
{
  std::cout << "Executing another fuzztest" << std::endl;
  std::cout << "size:" << args.size << std::endl;
  std::cout << "data:";
  for (size_t size = 0; size < args.size; size++)
    ::printf("%c", args.data[size]);
  std::cout << std::endl << std::flush;
}
