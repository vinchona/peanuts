#include "peanuts.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

#define MAYBE_UNUSED(var) (void)(var)

static void safe_main(int arg_count, char* arg_value[])
{
  MAYBE_UNUSED(arg_count);
  MAYBE_UNUSED(arg_value);
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
