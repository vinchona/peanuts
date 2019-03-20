#include "peanuts.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;
using namespace peanuts;

#define MAYBE_UNUSED(variable) (void)(variable)

static void usage(char* name)
{
  std::cout << "Usage: " << name << " [OPTION]..." << std::endl;
  std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
  std::cout << std::endl;
  std::cout << "--help" << '\t' << "This help" << std::endl;
  std::cout << "--count" << '\t' << "Number of tests" << std::endl;
  std::cout << "--descriptions" << '\t' << "Describe tests" << std::endl;
}

static bool parse_command_line(vector<string> command_line)
{
  for(auto const & command: command_line)
  {
    if(command == "--help")
      return true;

    if(command == "--count")
    {
      std::cout << Tester::instance().count() << " tests registered" << std::endl;
      continue;
    }

    if(command == "--descriptions")
    {
      for(auto const& description: Tester::instance().descriptions())
        std::cout << description << std::endl;
      continue;
    }

    std::cout << "Unknown command: " << command << std::endl;
    return true;
  }
  return false;
}

static void safe_main(int arg_count, char* arg_value[])
{
  vector<string> command_line{};

  for(int i = 1; i < arg_count; ++i)
    command_line.push_back(arg_value[i]);

  bool exit = parse_command_line(command_line);
  if(exit)
  {
    usage(arg_value[0]);
    return;
  }

  Tester::instance().execute();
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
