#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <functional>
#include <vector>

namespace peanuts
{

#define CONCATENATES2(a, b) a##b
#define CONCATENATES(a, b) CONCATENATES2(a, b)

struct Unittests
{

  Unittests(Unittests const&) = delete;
  Unittests& operator=(Unittests const&) = delete;
  Unittests(Unittests&&) = delete;
  Unittests& operator=(Unittests&&) = delete;
  static auto& instance()
  {
    static peanuts::Unittests unittests{};
    return unittests;
  }

  int add(std::function<void(void)> function, char const* description);
  void execute();

private:
  Unittests() = default; // Disallow instantion outside of the class
  struct Tests
  {
    std::function<void(void)> function;
    char const* description;
  };
  std::vector<Tests> tests;
  int count = 0;
};

#define unittest_with_suffix(description, suffix)                                                                      \
  static void CONCATENATES(unittest_function, suffix)();                                                               \
  static auto CONCATENATES(execute_, suffix) =                                                                         \
      peanuts::Unittests::instance().add(CONCATENATES(unittest_function, suffix), description);                        \
  static void CONCATENATES(unittest_function, suffix)()

#define unittest(description) unittest_with_suffix(description, __LINE__)

} // namespace peanuts

#endif /* __PEANUTS__ */
