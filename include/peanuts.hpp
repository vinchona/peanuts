#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <fuzzer.hpp>
#include <tester.hpp>

#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void);                                              \
  static peanuts::Tester::Test PEANUTS_CONCATENATES(gTestVariable, suffix){                                            \
      PEANUTS_CONCATENATES(peanut_unique_function, suffix), description};                                              \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Tester::instance().add(PEANUTS_CONCATENATES(gTestVariable, suffix));                                    \
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
