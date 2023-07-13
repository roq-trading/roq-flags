/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/validators/time_period.hpp"

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

TimePeriod::TimePeriod(const std::chrono::nanoseconds value) : value_{absl::FromChrono(value)} {
}

TimePeriod::operator std::chrono::milliseconds() const {
  return absl::ToChronoMilliseconds(value_);
}

std::string TimePeriod::unparse(TimePeriod const &flag) {
  return absl::AbslUnparseFlag(flag.value_);
}

bool TimePeriod::parse(absl::string_view &text, TimePeriod *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error))
    return false;
  return true;
}

std::string AbslUnparseFlag(TimePeriod const &flag) {
  return TimePeriod::unparse(flag);
}

bool AbslParseFlag(absl::string_view &text, TimePeriod *&flag, std::string *&error) {
  return TimePeriod::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
