#pragma once

#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

namespace peanuts
{

template <typename T, typename U> struct Validator
{
  bool is_equals(T const expected, U actual)
  {
    if (expected == (T)actual)
      return true;
    return false;
  }

  bool is_not_equals(T const expected, U actual)
  {
    if (expected != (T)actual)
      return true;
    return false;
  }
};

} // namespace peanuts

#endif /* __VALIDATOR__ */
