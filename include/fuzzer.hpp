#pragma once

#ifndef FUZZER_HPP
#define FUZZER_HPP

#include <functional>
#include <memory>
#include <vector>

namespace peanuts
{

struct Fuzzer
{
  ~Fuzzer();
  Fuzzer(Fuzzer const&) = delete;
  Fuzzer& operator=(Fuzzer const&) = delete;
  Fuzzer(Fuzzer&&) = delete;
  Fuzzer& operator=(Fuzzer&&) = delete;
  static auto& instance()
  {
    static peanuts::Fuzzer peanuts{};
    return peanuts;
  }

  struct Test
  {
    std::function<void(size_t, char const*)> function;
    char const* description;
  };

  int add(Test test);
  int count();
  std::vector<char const*> descriptions();

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
  struct Implementation;
  std::unique_ptr<Implementation> implementation;
  Fuzzer();
};

} // namespace peanuts

#endif /* __FUZZER__ */
