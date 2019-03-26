#include <cstdlib>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tester.hpp>

struct Application
{
  bool show_usage = false;
  bool exit = false;
  std::vector<size_t> tests{};
};

static void usage(char* name)
{
  std::cout << "Usage: " << name << " [OPTION]..." << std::endl;
  std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
  std::cout << std::endl;
  std::cout << "--help" << '\t' << "This help" << std::endl;
  std::cout << "--registered" << '\t' << "Tests registered" << std::endl;
  std::cout << "--test" << '\t' << "Single test" << std::endl;
}

static Application parse_command_line(std::deque<std::string> command_line)
{
  Application application{};
  while (!command_line.empty())
  {
    auto const command = command_line.front();
    if (command == "--help")
    {
      application.show_usage = true;
      application.exit = true;
      return application;
    }

    if (command == "--registered")
    {
      auto tests = peanuts::Tester::instance().tests();
      std::cout << tests.size() << " tests registered:" << std::endl;
      std::cout << "--" << std::endl;
      size_t number = 0;
      for (auto const& test : tests)
        std::cout << "[" << number++ << "]: " << test.description << std::endl;
      std::cout << "--" << std::endl;
      application.exit = true;
      return application;
    }

    if (command == "--test")
    {
      command_line.pop_front();
      if (command_line.empty())
      {
        std::cout << "Missing argument to '" << command << "'" << std::endl;
        application.exit = true;
        return application;
      }

      std::stringstream ss{command_line.front()};
      ss.unsetf(std::ios::dec);
      ss.unsetf(std::ios::hex);
      size_t test;
      ss >> test;
      application.tests.push_back(test);
      command_line.pop_front();
      continue;
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
  std::deque<std::string> command_line{};

  for (int i = 1; i < arg_count; ++i)
    command_line.push_back(arg_value[i]);

  auto application = parse_command_line(command_line);
  if (application.show_usage)
    usage(arg_value[0]);

  if (application.exit)
    return;

  auto tests = peanuts::Tester::instance().tests();
  if (!application.tests.empty())
  {
    for (auto const& test : application.tests)
    {
      if (test >= tests.size())
        throw std::runtime_error{std::string{"No such test: "} + std::to_string(test)};
      std::cout << "[" << test << "]: " << tests[test].description << std::endl;
      tests[test].function;
    }
    return;
  }

  size_t number = 0;
  for (auto const& test : tests)
  {
    std::cout << "[" << number++ << "]: " << test.description << std::endl;
    test.function();
  }
}

int main(int arg_count, char* arg_value[])
{
  try
  {
    safe_main(arg_count, arg_value);
    return EXIT_SUCCESS;
  }
  catch (std::runtime_error const& error)
  {
    std::cerr << std::endl << "Exception caught: " << error.what() << std::endl;
    return EXIT_FAILURE;
  }
}
