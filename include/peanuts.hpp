#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <exception>
#include <functional>
#include <iostream>
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

  int add_unittest(std::function<void(void)> function, char const* description);
  int count_unittests();
  void execute_unittests();

  int add_fuzztest(std::function<void(char const*, size_t)> function, char const* description);
  int count_fuzztests();
  void execute_fuzztests();

private:
  Peanuts() = default;
  struct UnitTest
  {
    std::function<void(void)> function;
    char const* description;
  };
  struct FuzzTest
  {
    std::function<void(char const*, size_t)> function;
    char const* description;
  };

  std::vector<UnitTest> unittests;
  std::vector<FuzzTest> fuzztests;
};

} // namespace peanuts

#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void);                                              \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Peanuts::instance().add_unittest(PEANUTS_CONCATENATES(peanut_unique_function, suffix), description);    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(char const* peanuts_fuzz_data,                      \
                                                                   size_t peanuts_fuzz_size);                          \
  static void PEANUTS_CONCATENATES(peanut_try_catch_unique_function, suffix)(char const* peanuts_fuzz_data,            \
                                                                             size_t peanuts_fuzz_size)                 \
  {                                                                                                                    \
    try                                                                                                                \
    {                                                                                                                  \
      PEANUTS_CONCATENATES(peanut_unique_function, suffix)(peanuts_fuzz_data, peanuts_fuzz_size);                      \
    }                                                                                                                  \
    catch (std::exception const& error)                                                                                \
    {                                                                                                                  \
      std::cerr << error.what() << std::endl;                                                                          \
    }                                                                                                                  \
  }                                                                                                                    \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) = peanuts::Peanuts::instance().add_fuzztest(               \
      PEANUTS_CONCATENATES(peanut_try_catch_unique_function, suffix), description);                                    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(char const* peanuts_fuzz_data,                      \
                                                                   size_t peanuts_fuzz_size)

#define PEANUTS_UNITTEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, __LINE__)
#define PEANUTS_FUZZTEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, __LINE__)

#endif /* __PEANUTS__ */
