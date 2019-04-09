#pragma once

#ifndef REGISTRANT_HPP
#define REGISTRANT_HPP

#include <functional>
#include <memory>
#include <vector>

namespace peanuts
{
template<typename... Args>
struct Registrant
{
  Registrant(Registrant const&) = delete;
  Registrant& operator=(Registrant const&) = delete;
  Registrant(Registrant&&) = delete;
  Registrant& operator=(Registrant&&) = delete;
  static auto& instance()
  {
    static peanuts::Registrant<Args...> registrant{};
    return registrant;
  }

  class Test
  {
    public:
    std::function<void(Args...)> function;
    char const* description;
  };

  std::vector<Test> tests;
private:
  Registrant() = default;
};

} // namespace peanuts

#endif /* __REGISTRANT__ */
