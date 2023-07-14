/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/flags/flag.h>

#include <string>
#include <type_traits>

namespace roq {
namespace flags {
namespace validators {

template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
struct ROQ_PUBLIC NonZero final {
  using value_type = T;

  NonZero() = default;
  NonZero(value_type const &value) : value_{value} {}  // NOLINT

  operator value_type const &() const { return value_; }

  bool empty() const { return value_ == value_type{}; }

  static bool required() { return true; };

  // abseil

  static std::string unparse(NonZero const &flag) { return absl::UnparseFlag(flag.value_); }

  static bool parse(absl::string_view &text, NonZero *&flag, std::string *&error) {
    using namespace std::literals;
    if (!absl::ParseFlag(text, &(*flag).value_, error))
      return false;
    if ((*flag).value_ == value_type{}) {
      *error = "not non-zero"s;
      return false;
    }
    return true;
  }

 private:
  value_type value_;
};

template <typename T>
inline std::string AbslUnparseFlag(roq::flags::validators::NonZero<T> const &flag) {
  return NonZero<T>::unparse(flag);
}

template <typename T>
inline bool AbslParseFlag(absl::string_view &text, roq::flags::validators::NonZero<T> *&flag, std::string *&error) {
  return NonZero<T>::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
