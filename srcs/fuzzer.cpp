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
using namespace std;

struct Application
{
  int size{256};
  int trials{1};
  string combinatorial{"random"};
};

static void show_registered()
{
  auto tests = peanuts::Registrant<peanuts::Test<>>::instance().registered;
  cout << tests.size() << " tests registered:" << endl;
  cout << "--" << endl;
  int number = 0;
  for (auto const& test : tests)
    cout << "[" << number++ << "]: " << test.description << endl;
  cout << "--" << endl;
}

static bool parse_command_line(int arg_count, char* arg_value[], Application& application)
{
  CommandLine command_line{};
  bool help{false};
  command_line.add_flag_command("--help", "This help", help, true);
  bool show{false};
  command_line.add_flag_command("--show", "Show registered tests via the 'peanuts' API", show, true);
  command_line.add_int_command("--size", "Number of random characters (default: 256)", application.size);
  command_line.add_int_command("--trials", "Number of trials (default: 1)", application.trials);
  command_line.add_string_command(
      "--combinatorial",
      "Type of fuzzing: 'random', 'combinations_with_repetition', 'combinations_without_repetition', "
      "'permutations_with_repetition', 'permutations_without_repetition' (default: 'random')",
      application.combinatorial);
  queue<string> line{};

  for (int i = 1; i < arg_count; ++i)
    line.push(arg_value[i]);

  command_line.parse(line);

  if (help)
  {
    cout << "Usage: " << arg_value[0] << " [OPTION]..." << endl;
    cout << "Execute tests registered via the 'peanuts' API" << endl;
    command_line.usage(cout);
    return false;
  }

  if (show)
  {
    show_registered();
    return false;
  }

  return true;
}

static void safe_execution(vector<peanuts::Test<size_t, char const*>> tests, int size, char const* data)
{
  int number = 0;
  for (auto const& test : tests)
  {
    cout << "[" << number++ << "]: " << test.description << endl;
    try
    {
      test.function(size, data);
    }
    catch (exception const& exception)
    {
      cerr << exception.what() << endl;
    }
  }
}

static void execute_dummy(int trials, vector<peanuts::Test<size_t, char const*>> tests)
{
  for (int trial = 0; trial < trials; trial++)
    safe_execution(tests, 0, nullptr);
}

static void execute_random(int trials, vector<peanuts::Test<size_t, char const*>> tests, int size)
{
  size_t seed{static_cast<size_t>(size)};
  mt19937 generator{seed};
  uniform_int_distribution<char> distribution{CHAR_MIN, CHAR_MAX};
  for (int trial = 0; trial < trials; trial++)
  {
    cout << "Trial: " << trial << endl;
    string data{};
    for (int character = 0; character < size; character++)
      data += string{distribution(generator)};

    safe_execution(tests, data.size(), data.c_str());
  }
}

static void execute_combinations_with_repetition(int trials, vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_combinations_without_repetition(int trials, vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_permutations_with_repetition(int trials, vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute_permutations_without_repetition(int trials, vector<peanuts::Test<size_t, char const*>> tests)
{
  execute_dummy(trials, tests);
}

static void execute(int trials, vector<peanuts::Test<size_t, char const*>> tests, string combinatorial, int size)
{
  if (combinatorial == "random")
    return execute_random(trials, tests, size);
  if (combinatorial == "combinations_with_repetition")
    return execute_combinations_with_repetition(trials, tests);
  if (combinatorial == "combinations_without_repetition")
    return execute_combinations_without_repetition(trials, tests);
  if (combinatorial == "permutations_with_repetition")
    return execute_permutations_with_repetition(trials, tests);
  if (combinatorial == "permutations_without_repetition")
    return execute_permutations_without_repetition(trials, tests);

  return execute_dummy(trials, tests);
}

static void safe_main(int arg_count, char* arg_value[])
{
  Application application{};

  auto should_continue = parse_command_line(arg_count, arg_value, application);
  if (!should_continue)
    return;

  auto tests = peanuts::Registrant<peanuts::Test<size_t, char const*>>::instance().registered;
  cout << "You have " << tests.size() << " fuzztests" << endl;
  execute(application.trials, tests, application.combinatorial, application.size);
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
