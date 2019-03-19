#include "peanuts.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace peanuts;

#define MAYBE_UNUSED(var) (void)(var)

static int test_id = 0;
static void test(size_t, char const*) { std::cout << "Fuzz[" << test_id << "]: Add API" << std::endl; }

static void safe_main(int arg_count, char* arg_value[])
{
  MAYBE_UNUSED(arg_count);
  MAYBE_UNUSED(arg_value);
  test_id = Fuzzer::instance().add(test, "Adding test with Unittests::add API");
  std::cout << "You have " << Fuzzer::instance().count() << " unittests" << std::endl;
  Fuzzer::instance().execute(20, Fuzzer::Combinatorial::random, 256);
  return;
}

int main(int arg_count, char* arg_value[])
{
  try
  {
    safe_main(arg_count, arg_value);
    return EXIT_SUCCESS;
  }
  catch (runtime_error const& error)
  {
    cerr << endl << "Exception caught: " << error.what() << endl;
    return EXIT_FAILURE;
  }
}
