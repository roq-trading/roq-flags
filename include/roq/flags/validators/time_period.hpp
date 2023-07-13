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

struct TimePeriod final {
  using value_type = absl::Duration;

  TimePeriod() = default;
  TimePeriod(std::chrono::nanoseconds);                       // NOLINT
  TimePeriod(absl::Duration const &value) : value_{value} {}  // NOLINT

  operator value_type const &() const { return value_; }

  bool empty() const { return value_ == absl::Duration{}; }

  static bool required() { return false; }

  // utilities
  operator std::chrono::milliseconds() const;

  // abseil
  static std::string unparse(TimePeriod const &);
  static bool parse(absl::string_view &, TimePeriod *&, std::string *&);

 private:
  value_type value_ = {};
};

// abseil
extern std::string ROQ_PUBLIC AbslUnparseFlag(TimePeriod const &);
extern bool ROQ_PUBLIC AbslParseFlag(absl::string_view &, TimePeriod *&, std::string *&);

}  // namespace validators
}  // namespace flags
}  // namespace roq
