#pragma once

#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <functional>
#include <memory>
#include <ostream>
#include <queue>
#include <string>

struct CommandLine final
{
  ~CommandLine();
  CommandLine();

  CommandLine(CommandLine const&) = delete;
  CommandLine& operator=(CommandLine const&) = delete;

  CommandLine(CommandLine&&) = delete;
  CommandLine& operator=(CommandLine&&) = delete;

  void add_int_command(std::string name, std::string description, int& value);
  void add_string_command(std::string name, std::string description, std::string& value);
  void add_flag_command(std::string name, std::string description, bool& value, bool flag);
  void add_user_command(std::string name, std::string description,
                        std::function<void(std::queue<std::string>& line)> parse);
  void usage(std::ostream& stream) const;
  void parse(std::queue<std::string>& line) const;

private:
  struct Implementation;
  std::unique_ptr<Implementation> implementation;
};

#endif /* __COMMAND_LINE__ */
