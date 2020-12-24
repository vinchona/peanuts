#include "command-line.hpp"
#include <iomanip>
#include <map>
#include <sstream>

using namespace std;

struct CommandLine::Implementation
{
  struct Command
  {
    Command(string name, string description, function<void(queue<string>&)> parse)
        : name{name}, description{description}, parse{parse}
    {
    }

    string const name;
    string const description;
    function<void(queue<string>& line)> const parse;
  };

  map<string, Command> commands;
  size_t biggest_commands_name_size() const
  {
    size_t biggest_name_size = 0;
    for (auto command : commands)
      if (command.second.name.size() > biggest_name_size)
        biggest_name_size = command.second.name.size();

    return biggest_name_size;
  }
};

CommandLine::~CommandLine() = default;

CommandLine::CommandLine() : implementation{new Implementation{}} {}

static void throw_if_empty(queue<string> const& line)
{
  if (line.empty())
    throw runtime_error{"Unexpected end of line"};
}

static void throw_if_unexpected_format(stringstream& ss, string expected, string actual, string value)
{
  if (ss.fail() || (ss.tellg() != streampos(-1)))
    throw runtime_error{"Expected '" + expected + "', got '" + actual + "':'" + value + "'"};
}

void CommandLine::add_int_command(string name, string description, int& value)
{
  auto const pop_size = [&](queue<string>& line) -> void {
    throw_if_empty(line);
    auto const word = line.front();
    line.pop();

    stringstream ss{word};
    ss.unsetf(ios::dec);
    ss.unsetf(ios::hex);
    int size;
    ss >> size;
    throw_if_unexpected_format(ss, "int", "string", word);
    value = size;
  };

  auto new_command = Implementation::Command{name + " <int>", description, pop_size};
  implementation->commands.insert(pair<string, Implementation::Command>{name, new_command});
}

void CommandLine::add_string_command(string name, string description, string& value)
{
  auto const pop_string = [&](queue<string>& line) -> void {
    throw_if_empty(line);
    value = line.front();
    line.pop();
  };

  auto new_command = Implementation::Command{name + " <string>", description, pop_string};
  implementation->commands.insert(pair<string, Implementation::Command>{name, new_command});
}

void CommandLine::add_flag_command(string name, string description, bool& value, bool flag)
{
  auto const pop_flag = [&](queue<string>&) -> void { value = flag; };

  auto new_command = Implementation::Command{name, description, pop_flag};
  implementation->commands.insert(pair<string, Implementation::Command>{name, new_command});
}

void CommandLine::add_user_command(string name, string description, function<void(queue<string>& line)> parse)
{
  auto new_command = Implementation::Command{name, description, parse};
  implementation->commands.insert(pair<string, Implementation::Command>{name, new_command});
}

void CommandLine::usage(ostream& stream) const
{
  auto space_between_name_and_description = implementation->biggest_commands_name_size() + 1;
  for (auto const& command : implementation->commands)
  {
    auto fill = space_between_name_and_description + command.second.description.size() - command.second.name.size();
    stream << command.second.name << setw(fill) << command.second.description << endl;
  }
}

void CommandLine::parse(queue<string>& line) const
{
  while (!line.empty())
  {
    auto const word = line.front();
    if (implementation->commands.find(word) == implementation->commands.end())
      throw runtime_error{"Unknown command '" + word + "'"};

    line.pop();

    auto const parser = implementation->commands.at(word).parse;
    if (!parser)
      throw runtime_error{"Missing parsing function for '" + word + "'"};

    parser(line);
  }
}
