#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <functional>
#include <vector>

namespace peanuts
{

struct Tester
{
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
  void execute();

private:
  Tester() = default;
  struct Test
  {
    std::function<void(void)> function;
    char const* description;
  };
  std::vector<Test> tests;
};

struct Fuzzer
{
  Fuzzer(Fuzzer const&) = delete;
  Fuzzer& operator=(Fuzzer const&) = delete;
  Fuzzer(Fuzzer&&) = delete;
  Fuzzer& operator=(Fuzzer&&) = delete;
  static auto& instance()
  {
    static peanuts::Fuzzer peanuts{};
    return peanuts;
  }

  int add(std::function<void(size_t, char const*)> function, char const* description);
  int count();

  enum struct Combinatorial
  {
    random,
    combination_with_repetitions,
    combination_without_repetitions,
    permutation_with_repetitions,
    permutation_without_repetitions,
  };

  void execute(size_t trials, Combinatorial combinatorial, size_t size);

private:
  Fuzzer() = default;

  struct Test
  {
    std::function<void(size_t, char const*)> function;
    char const* description;
  };

  std::vector<Test> tests;

  void execute_random(size_t seed, size_t max_size);
  void execute_dummy();
};

} // namespace peanuts

#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void);                                              \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Tester::instance().add(PEANUTS_CONCATENATES(peanut_unique_function, suffix), description);              \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(size_t peanuts_fuzz_size,                           \
                                                                   char const* peanuts_fuzz_data);                     \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Fuzzer::instance().add(PEANUTS_CONCATENATES(peanut_unique_function, suffix), description);              \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(size_t peanuts_fuzz_size,                           \
                                                                   char const* peanuts_fuzz_data)

#define PEANUTS_TEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, __LINE__)
#define PEANUTS_FUZZ(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, __LINE__)

#endif /* __PEANUTS__ */
