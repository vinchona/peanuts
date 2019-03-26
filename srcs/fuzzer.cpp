#include "fuzzer.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <string>
#include <sstream>

struct Application
{
  bool show_usage = false;
  bool exit = false;
  size_t size = 0;
  size_t trials = 1;
  peanuts::Fuzzer::Combinatorial combinatorial = peanuts::Fuzzer::Combinatorial::random;
};


static void usage(char* name)
{
  std::cout << "Usage: " << name << " [OPTION]..." << std::endl;
  std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
  std::cout << std::endl;
  std::cout << "--help" << '\t' << "This help" << std::endl;
  std::cout << "--size" << '\t' << "Number of random characters" << std::endl;
  std::cout << "--trials" << '\t' << "Number of trials" << std::endl;
  std::cout << "--combinatorial" << '\t' << "Type of fuzzing:" << std::endl;
  std::cout << '\t' << '\t' << "  - random (default)" << std::endl;
  std::cout << '\t' << '\t' << "  - combination_with_repetitions" << std::endl;
  std::cout << '\t' << '\t' << "  - combination_without_repetitions" << std::endl;
  std::cout << '\t' << '\t' << "  - permutation_with_repetitions" << std::endl;
  std::cout << '\t' << '\t' << "  - permutation_without_repetitions" << std::endl;
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

    if (command == "--size")
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
      size_t size;
      ss >> size;
      application.size = size;
      command_line.pop_front();
      continue;
    }

    if (command == "--trials")
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
      size_t trials;
      ss >> trials;
      application.trials = trials;
      command_line.pop_front();
      continue;
    }

    if (command == "--combinatorial")
    {
      command_line.pop_front();
      if (command_line.empty())
      {
        std::cout << "Missing argument to '" << command << "'" << std::endl;
        application.exit = true;
        return application;
      }

      std::string combinatorial{command_line.front()};
      if (combinatorial == "random")
      {
        application.combinatorial = peanuts::Fuzzer::Combinatorial::random;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "combination_with_repetitions")
      {
        application.combinatorial = peanuts::Fuzzer::Combinatorial::combination_with_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "combination_without_repetitions")
      {
        application.combinatorial = peanuts::Fuzzer::Combinatorial::combination_without_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "permutation_with_repetitions")
      {
        application.combinatorial = peanuts::Fuzzer::Combinatorial::permutation_with_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "permutation_without_repetitions")
      {
        application.combinatorial = peanuts::Fuzzer::Combinatorial::permutation_without_repetitions;
        command_line.pop_front();
        continue;
      }

      std::cout << "Unknown combinatorial: " << combinatorial << std::endl;
      std::cout << "Known value:" << std::endl
        << "  - random (default)" << std::endl
        << "  - combination_with_repetitions" << std::endl
        << "  - combination_without_repetitions" << std::endl
        << "  - permutation_with_repetitions" << std::endl
        << "  - permutation_without_repetitions" << std::endl;
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
  peanuts::Fuzzer::instance().execute(application.trials, application.combinatorial, application.size);
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
