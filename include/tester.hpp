#pragma once

#ifndef TESTER_HPP
#define TESTER_HPP

#include <functional>
#include <memory>
#include <vector>

namespace peanuts
{

struct Tester
{
  ~Tester();
  Tester(Tester const&) = delete;
  Tester& operator=(Tester const&) = delete;
  Tester(Tester&&) = delete;
  Tester& operator=(Tester&&) = delete;
  static auto& instance()
  {
    static peanuts::Tester peanuts{};
    return peanuts;
  }

  int add(std::function<void(void)> function, char const* description);
  int count();
  std::vector<char const*> descriptions();
  void execute();

private:
  struct Implementation;
  std::unique_ptr<Implementation> implementation;
  Tester();
};
} // namespace peanuts

#endif
