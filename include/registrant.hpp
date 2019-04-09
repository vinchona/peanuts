#pragma once

#ifndef REGISTRANT_HPP
#define REGISTRANT_HPP

#include <functional>
#include <vector>

namespace peanuts
{

template<typename... Args>
struct Test
{
  std::function<void(Args...)> function;
  char const* description;
};

template<class T>
struct Registrant
{
  ~Registrant() = default;
  Registrant(Registrant const&) = delete;
  Registrant& operator=(Registrant const&) = delete;
  Registrant(Registrant&&) = delete;
  Registrant& operator=(Registrant&&) = delete;
  static auto& instance()
  {
    static peanuts::Registrant<T> registrant{};
    return registrant;
  }

   std::vector<T> registered;

private:
  Registrant() = default;
};

} // namespace peanuts

#endif /* __REGISTRANT__ */
