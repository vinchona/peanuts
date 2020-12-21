#include <command-line.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <registrant.hpp>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace carryall;
using namespace std;

struct Application
{
  vector<int> tests{};
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
  auto select = [&application](queue<string>& line) {
    if (line.empty())
      throw runtime_error{"Unexpected end of line"};
    auto const word = line.front();
    line.pop();

    stringstream ss{word};
    ss.unsetf(ios::dec);
    ss.unsetf(ios::hex);
    int test;
    ss >> test;
    if (ss.fail() || (ss.tellg() != streampos(-1)))
      throw runtime_error{"Expected 'int', got 'string': '" + word + "'"};
    application.tests.push_back(test);
  };
  command_line.add_user_command("--select", "Execute selected test", select);

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
        throw runtime_error{string{"No such test: "} + to_string(test)};
      cout << "[" << test << "]: " << tests[test].description << endl;
      tests[test].function;
    }
    return;
  }

  int number = 0;
  for (auto const& test : tests)
  {
    cout << "[" << number++ << "]: " << test.description << endl;
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
  catch (runtime_error const& error)
  {
    cerr << endl << "Exception caught: " << error.what() << endl;
    return EXIT_FAILURE;
  }
}
