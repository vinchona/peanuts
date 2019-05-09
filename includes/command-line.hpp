#pragma once

#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <ostream>
#include <queue>
#include <string>
#include <functional>
#include <memory>

namespace peanuts
{
  struct CommandLine{
    ~CommandLine();
    CommandLine();

    CommandLine(CommandLine const&);
    CommandLine& operator=(CommandLine const&);

    CommandLine(CommandLine &&);
    CommandLine& operator=(CommandLine &&);

    void add_int_command(std::string name, std::string description, int &value) ;
    void add_string_command(std::string name, std::string description, std::string &value) ;
    void add_flag_command(std::string name, std::string description, bool &value, bool flag) ;
    void add_user_command(std::string name, std::string description,
        std::function<void(std::queue<std::string> &line)> parse) ;
    void usage(std::ostream &stream) const;
    void parse(std::queue<std::string> &line) const;

    private:
    struct Implementation;
    std::unique_ptr<Implementation> implementation;
  };


} // namespace peanuts

#endif /* __COMMAND_LINE__ */
