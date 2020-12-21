#include <command-line.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <registrant.hpp>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace carryall;

struct Application
{
  std::vector<int> tests{};
};

static void show_registered()
{
  auto tests = peanuts::Registrant<peanuts::Test<>>::instance().registered;
  std::cout << tests.size() << " tests registered:" << std::endl;
  std::cout << "--" << std::endl;
  int number = 0;
  for (auto const& test : tests)
    std::cout << "[" << number++ << "]: " << test.description << std::endl;
  std::cout << "--" << std::endl;
}

static bool parse_command_line(int arg_count, char* arg_value[], Application& application)
{
  CommandLine command_line{};
  bool help{false};
  command_line.add_flag_command("--help", "This help", help, true);
  bool show{false};
  command_line.add_flag_command("--show", "Show registered tests via the 'peanuts' API", show, true);
  auto select = [&application](std::queue<std::string>& line) {
    if (line.empty())
      throw std::runtime_error{"Unexpected end of line"};
    auto const word = line.front();
    line.pop();

    std::stringstream ss{word};
    ss.unsetf(std::ios::dec);
    ss.unsetf(std::ios::hex);
    int test;
    ss >> test;
    if (ss.fail() || (ss.tellg() != std::streampos(-1)))
      throw std::runtime_error{"Expected 'int', got 'string': '" + word + "'"};
    application.tests.push_back(test);
  };
  command_line.add_user_command("--select", "Execute selected test", select);

  std::queue<std::string> line{};

  for (int i = 1; i < arg_count; ++i)
    line.push(arg_value[i]);

  command_line.parse(line);

  if (help)
  {
    std::cout << "Usage: " << arg_value[0] << " [OPTION]..." << std::endl;
    std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
    command_line.usage(std::cout);
    return false;
  }

  if (show)
  {
    show_registered();
    return false;
  }

  return true;
}

static void safe_main(int arg_count, char* arg_value[])
{
  Application application{};

  auto should_continue = parse_command_line(arg_count, arg_value, application);
  if (!should_continue)
    return;

  auto const tests = peanuts::Registrant<peanuts::Test<>>::instance().registered;
  if (!application.tests.empty())
  {
    for (auto const& test : application.tests)
    {
      if ((size_t)test >= tests.size())
        throw std::runtime_error{std::string{"No such test: "} + std::to_string(test)};
      std::cout << "[" << test << "]: " << tests[test].description << std::endl;
      tests[test].function;
    }
    return;
  }

  int number = 0;
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
