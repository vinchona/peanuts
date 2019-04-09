#include <registrant.hpp>
#include <cstdlib>
#include <climits>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <random>
#include <vector>

struct Application
{
  enum struct Combinatorial
  {
    random,
    combination_with_repetitions,
    combination_without_repetitions,
    permutation_with_repetitions,
    permutation_without_repetitions,
  };

  bool show_usage = false;
  bool exit = false;
  size_t size = 256;
  size_t trials = 1;
  Application::Combinatorial combinatorial = Application::Combinatorial::random;
};

static void usage(char* name)
{
  std::cout << "Usage: " << name << " [OPTION]..." << std::endl;
  std::cout << "Execute tests registered via the 'peanuts' API" << std::endl;
  std::cout << std::endl;
  std::cout << "--help" << '\t' << "This help" << std::endl;
  std::cout << "--registered" << '\t' << "Tests registered" << std::endl;
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

    if (command == "--registered")
    {
      auto tests = peanuts::Registrant<size_t, char const*>::instance().tests;
      std::cout << tests.size() << " tests registered:" << std::endl;
      std::cout << "--" << std::endl;
      size_t number = 0;
      for (auto const& test : tests)
        std::cout << "[" << number++ << "]: " << test.description << std::endl;
      std::cout << "--" << std::endl;
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
        application.combinatorial = Application::Combinatorial::random;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "combination_with_repetitions")
      {
        application.combinatorial = Application::Combinatorial::combination_with_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "combination_without_repetitions")
      {
        application.combinatorial = Application::Combinatorial::combination_without_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "permutation_with_repetitions")
      {
        application.combinatorial = Application::Combinatorial::permutation_with_repetitions;
        command_line.pop_front();
        continue;
      }

      if (combinatorial == "permutation_without_repetitions")
      {
        application.combinatorial = Application::Combinatorial::permutation_without_repetitions;
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
  return application;
}

static void safe_execution(std::vector<peanuts::Registrant<size_t, char const*>::Test> tests, size_t size, char const* data)
{
  size_t number = 0;
  for (auto const& test : tests)
  {
    std::cout << "[" << number++ << "]: " << test.description << std::endl;
    try
    {
      test.function(size, data);
    }
    catch (std::exception const& exception)
    {
      std::cerr << exception.what() << std::endl;
    }
  }
}

static void execute_dummy(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests)
{
  for (size_t trial = 0; trial < trials; trial++)
    safe_execution(tests, 0, nullptr);
}

static void execute_random(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests, size_t size)
{
  std::mt19937 generator{size};
  std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (size_t trial = 0; trial < trials; trial++)
  {
    std::cout << "Trial: " << trial << std::endl;
    std::string data{};
    for (size_t character = 0; character < size; character++)
      data += std::string{distribution(generator)};

    safe_execution(tests, data.size(), data.c_str());
  }
}

static void execute_combination_with_repetitions(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests) { execute_dummy(trials, tests); }

static void execute_combination_without_repetitions(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests) { execute_dummy(trials, tests); }

static void execute_permutation_with_repetitions(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests) { execute_dummy(trials, tests); }

static void execute_permutation_without_repetitions(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests) { execute_dummy(trials, tests); }

static void execute(size_t trials, std::vector<peanuts::Registrant<size_t, char const*>::Test> tests, Application::Combinatorial combinatorial, size_t size)
{
  switch (combinatorial)
  {
    case Application::Combinatorial::random:
      {
        execute_random(trials, tests, size);
        break;
      }
    case Application::Combinatorial::combination_with_repetitions:
      {
        execute_combination_with_repetitions(trials, tests);
        break;
      }
    case Application::Combinatorial::combination_without_repetitions:
      {
        execute_combination_without_repetitions(trials, tests);
        break;
      }
    case Application::Combinatorial::permutation_with_repetitions:
      {
        execute_permutation_with_repetitions(trials, tests);
        break;
      }
    case Application::Combinatorial::permutation_without_repetitions:
      {
        execute_permutation_without_repetitions(trials, tests);
        break;
      }
    default:
      {
        execute_dummy(trials, tests);
        break;
      }
  }
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

  auto tests = peanuts::Registrant<size_t, char const*>::instance().tests;

  std::cout << "You have " << tests.size() << " fuzztests" << std::endl;
  execute(application.trials, tests, application.combinatorial, application.size);
}

void testfuzz(size_t, char const*)
{
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
