#include "fuzzer.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <string>

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


  std::cout << "You have " << peanuts::Fuzzer::instance().count() << " fuzztests" << std::endl;
  peanuts::Fuzzer::instance().execute(20, peanuts::Fuzzer::Combinatorial::random, 256);
  return;
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
