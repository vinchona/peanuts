#pragma once

#ifndef PEANUTS_HPP
#define PEANUTS_HPP

#include <registrant.hpp>


#define PEANUTS_CONCATENATES2(a, b) a##b
#define PEANUTS_CONCATENATES(a, b) PEANUTS_CONCATENATES2(a, b)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(peanuts::Void); \
  static peanuts::Registrant<peanuts::Void>::Test PEANUTS_CONCATENATES(gTestVariable, suffix) = {                                            \
  PEANUTS_CONCATENATES(peanut_unique_function, suffix), description}; \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Registrant<peanuts::Void>::instance().tests.insert(peanuts::Registrant<peanuts::Void>::instance().tests.end(), PEANUTS_CONCATENATES(gTestVariable, suffix));                                    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(peanuts::Void)

#define PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, suffix)                                                  \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(peanuts::Args args); \
  static peanuts::Registrant<peanuts::Args>::Test PEANUTS_CONCATENATES(gTestVariable, suffix){                                            \
	  PEANUTS_CONCATENATES(peanut_unique_function, suffix), description};					       \
  static auto PEANUTS_CONCATENATES(gUnusedVariable, suffix) =                                                          \
      peanuts::Registrant<peanuts::Args>::instance().tests.insert(peanuts::Registrant<peanuts::Args>::instance().tests.end(), PEANUTS_CONCATENATES(gTestVariable, suffix));                                    \
  static void PEANUTS_CONCATENATES(peanut_unique_function, suffix)(peanuts::Args args)

#define PEANUTS_TEST(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_UNITTEST(description, __LINE__)
#define PEANUTS_FUZZ(description) PEANUTS_DECLARE_AND_MAKE_UNIQUE_FUZZTEST(description, __LINE__)

#endif /* __PEANUTS__ */
