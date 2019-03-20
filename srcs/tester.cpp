#include <tester.hpp>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using namespace peanuts;

#define MAYBE_UNUSED(variable) (void)(variable)

struct Application
{
  bool show_usage = false;
  bool exit = false;
};

static void usage(char* name)
{
  std::cout << "Usage: " << name << " [OPTION]..." << std::endl;
  std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
  std::cout << std::endl;
  std::cout << "--help" << '\t' << "This help" << std::endl;
  std::cout << "--registered" << '\t' << "Tests registered" << std::endl;
}

static Application parse_command_line(vector<string> command_line)
{
  Application application{};
  for (auto const& command : command_line)
  {
    if (command == "--help")
    {
      application.show_usage = true;
      application.exit = true;
      return application;
    }

    if (command == "--registered")
    {
      auto tests = Tester::instance().tests();
      std::cout << tests.size() << " tests registered" << std::endl;
      std::cout << "--" << std::endl;
      size_t number = 0;
      for (auto const& test : tests)
        std::cout << "[" << number++ << "]: " << test.description << std::endl;
      std::cout << "--" << std::endl;
      application.exit = true;
      return application;
    }

    std::cout << "Unknown command: " << command << std::endl;
    application.exit = true;
    return application;
  }
  application.exit = false;
  return application;
}

static void safe_main(int arg_count, char* arg_value[])
{
  vector<string> command_line{};

  for (int i = 1; i < arg_count; ++i)
    command_line.push_back(arg_value[i]);

  auto application = parse_command_line(command_line);
  if (application.show_usage)
    usage(arg_value[0]);

  if (application.exit)
    return;

  auto tests = Tester::instance().tests();
  size_t number = 0;
  for (auto const& test : tests)
  {
    std::cout << "[" << number++ << "]: " << test.description << std::endl;
    test.function();
  }
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
