/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/flags/flag.h>

#include <absl/time/time.h>

#include <chrono>
#include <string>

namespace roq {
namespace flags {
namespace validators {

struct ROQ_PUBLIC TimePeriod final {
  using value_type = absl::Duration;

  TimePeriod() = default;
  TimePeriod(std::chrono::nanoseconds);                       // NOLINT
  TimePeriod(absl::Duration const &value) : value_{value} {}  // NOLINT

  operator value_type const &() const { return value_; }

  bool empty() const { return value_ == absl::Duration{}; }

  static bool required() { return false; }

  operator std::chrono::nanoseconds() const;
  operator std::chrono::milliseconds() const;

  // abseil

  static std::string unparse(TimePeriod const &);
  static bool parse(absl::string_view &, TimePeriod *&, std::string *&);

 private:
  value_type value_ = {};
};

inline std::string AbslUnparseFlag(roq::flags::validators::TimePeriod const &flag) {
  using value_type = std::remove_cvref<decltype(flag)>::type;
  return value_type::unparse(flag);
}

inline bool AbslParseFlag(absl::string_view &text, roq::flags::validators::TimePeriod *&flag, std::string *&error) {
  using value_type = std::remove_cvref<decltype(*flag)>::type;
  return value_type::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
