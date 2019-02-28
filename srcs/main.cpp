#include "peanuts.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace peanuts;

#define MAYBE_UNUSED(var) (void)(var)

static void test(void) { std::cout << "Add API - OK" << std::endl; }

static void safe_main(int arg_count, char* arg_value[])
{
  MAYBE_UNUSED(arg_count);
  MAYBE_UNUSED(arg_value);
  auto count = Peanuts::instance().add(test, "Adding test width Unittests::add API");
  std::cout << "We have " << count << " unittests" << std::endl;
  Peanuts::instance().execute();
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
