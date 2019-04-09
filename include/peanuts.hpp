#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <registrant.hpp>

#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void); \
  static peanuts::Test<> PEANUTS_CONCATENATES(gTestVariable, suffix) = {                                            \
  PEANUTS_CONCATENATES(peanut_unique_function, suffix), description}; \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Registrant<peanuts::Test<>>::instance().registered.insert(peanuts::Registrant<peanuts::Test<>>::instance().registered.end(), PEANUTS_CONCATENATES(gTestVariable, suffix));                                    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(void)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(size_t size, char const* data); \
  static peanuts::Test<size_t, char const*> PEANUTS_CONCATENATES(gTestVariable, suffix){                                            \
	  PEANUTS_CONCATENATES(peanut_unique_function, suffix), description};					       \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Registrant<peanuts::Test<size_t, char const*>>::instance().registered.insert(peanuts::Registrant<peanuts::Test<size_t, char const*>>::instance().registered.end(), PEANUTS_CONCATENATES(gTestVariable, suffix));                                    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(size_t peanuts_size, char const* peanuts_data)

#define PEANUTS_TEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, __LINE__)
#define PEANUTS_FUZZ(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, __LINE__)

#endif /* __PEANUTS__ */
