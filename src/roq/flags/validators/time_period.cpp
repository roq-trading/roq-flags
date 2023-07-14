/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/validators/time_period.hpp"

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

TimePeriod::TimePeriod(std::chrono::nanoseconds value) : value_{absl::FromChrono(value)} {
}

TimePeriod::operator std::chrono::nanoseconds() const {
  return absl::ToChronoNanoseconds(value_);
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

}  // namespace validators
}  // namespace flags
}  // namespace roq
