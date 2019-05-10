#pragma once

#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

namespace peanuts
{
struct Validator
{
  template <typename T, typename U>
    static
    bool is_equal(T&& expected, U&& actual)
    {
      return (expected == (T)actual);
    }

  template <typename T, typename U>
    static
    bool is_not_equal(T&& expected, U&& actual)
    {
      return (expected != (T)actual);
    }
};

} // namespace peanuts

#endif /* __VALIDATOR__ */
