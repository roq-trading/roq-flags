/* Copyright (c) 2017-2026, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/flags/flag.h>

#include <string>

#include "roq/utils/math.hpp"

namespace roq {
namespace flags {
namespace validators {

template <typename T>
  requires std::is_integral_v<T>
struct ROQ_PUBLIC PowerOfTwo final {
  using value_type = T;

  PowerOfTwo() = default;
  PowerOfTwo(value_type const &value) : value_{value} {}

  operator value_type() const { return value_; }

  bool empty() const { return value_ != value_type{}; }

  static bool required() { return true; };

  // abseil

  static std::string unparse(PowerOfTwo const &flag) { return absl::UnparseFlag(flag.value_); }

  static bool parse(absl::string_view &text, PowerOfTwo *&flag, std::string *&error) {
    using namespace std::literals;
    if (!absl::ParseFlag(text, &(*flag).value_, error)) {
      return false;
    }
    if (!((*flag).value_ > 0) || !utils::power_of_two((*flag).value_)) {
      *error = "not power of two"s;
      return false;
    }
    return true;
  }

 private:
  value_type value_;
};

template <typename T>
inline std::string AbslUnparseFlag(roq::flags::validators::PowerOfTwo<T> const &flag) {
  using value_type = std::remove_cvref_t<decltype(flag)>;
  return value_type::unparse(flag);
}

template <typename T>
inline bool AbslParseFlag(absl::string_view &text, roq::flags::validators::PowerOfTwo<T> *&flag, std::string *&error) {
  using value_type = std::remove_cvref_t<decltype(*flag)>;
  return value_type::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
