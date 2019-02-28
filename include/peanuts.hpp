#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <functional>
#include <vector>

namespace peanuts
{

struct Peanuts
{

  Peanuts(Peanuts const&) = delete;
  Peanuts& operator=(Peanuts const&) = delete;
  Peanuts(Peanuts&&) = delete;
  Peanuts& operator=(Peanuts&&) = delete;
  static auto& instance()
  {
    static peanuts::Peanuts peanuts{};
    return peanuts;
  }

  int add(std::function<void(void)> function, char const* description);
  void execute();

private:
  Peanuts() = default;
  struct Test
  {
    std::function<void(void)> function;
    char const* description;
  };
  std::vector<Test> tests;
  int count = 0;
};

} // namespace peanuts

#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE(description, suffix)                                                           \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)();                                                  \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Peanuts::instance().add(PEANUTS_CONCATENATES(peanut_unique_function, suffix), description);             \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)()

#define PEANUTS_UNITTEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE(description, __LINE__)

#endif /* __PEANUTS__ */
