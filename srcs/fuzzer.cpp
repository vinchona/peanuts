#include <climits>
#include <command-line.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>
#include <registrant.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace carryall;

struct Application
{
  int size{256};
  int trials{1};
  std::string combinatorial{"random"};
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
  command_line.add_int_command("--size", "Number of random characters", (int&)application.size);
  command_line.add_int_command("--trials", "Number of trials", (int&)application.trials);
  command_line.add_string_command(
      "--combinatorial",
      "Type of fuzzing: 'random', 'combination_with_repetitions', 'combination_without_repetitions', "
      "'permutation_with_repetitions', 'permutation_without_repetitions' (default: 'random')",
      application.combinatorial);
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

static void safe_execution(std::vector<peanuts::Test<size_t, char const*>> tests, int size, char const* data)
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

static void execute_dummy(int trials, std::vector<peanuts::Test<size_t, char const*>> tests)
{
  for (int trial = 0; trial < trials; trial++)
    safe_execution(tests, 0, nullptr);
}

static void execute_random(int trials, std::vector<peanuts::Test<size_t, char const*>> tests, int size)
{
  int seed{size};
  std::mt19937 generator{seed};
  std::uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (int trial = 0; trial < trials; trial++)
  {
    std::cout << "Trial: " << trial << std::endl;
    std::string data{};
    for (int character = 0; character < size; character++)
      data += std::string{distribution(generator)};

    safe_execution(tests, data.size(), data.c_str());
  }
}

static void execute_combination_with_repetitions(int trials, std::vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_combination_without_repetitions(int trials, std::vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_permutation_with_repetitions(int trials, std::vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_permutation_without_repetitions(int trials, std::vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute(int trials, std::vector<peanuts::Test<size_t, char const*>> tests, std::string combinatorial,
                    int size)
{
  if (combinatorial == "random")
    return execute_random(trials, tests, size);
  if (combinatorial == "combination_with_repetitions")
    return execute_combination_with_repetitions(trials, tests);
  if (combinatorial == "combination_without_repetitions")
    return execute_combination_without_repetitions(trials, tests);
  if (combinatorial == "permutation_with_repetitions")
    return execute_permutation_with_repetitions(trials, tests);
  if (combinatorial == "permutation_without_repetitions")
    return execute_permutation_without_repetitions(trials, tests);

  return execute_dummy(trials, tests);
}

static void safe_main(int arg_count, char* arg_value[])
{
  Application application{};

  auto should_continue = parse_command_line(arg_count, arg_value, application);
  if (!should_continue)
    return;

  auto tests = peanuts::Registrant<peanuts::Test<size_t, char const*>>::instance().registered;
  std::cout << "You have " << tests.size() << " fuzztests" << std::endl;
  execute(application.trials, tests, application.combinatorial, application.size);
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
