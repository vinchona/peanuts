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

  size_t add(Test test);
  std::vector<Test> tests();

private:
  struct Implementation;
  std::unique_ptr<Implementation> implementation;
  Fuzzer();
};

} // namespace peanuts

#endif /* __FUZZER__ */
