/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/utils/non_empty.hpp"

#include <absl/flags/marshalling.h>

#include <iterator>

using namespace std::literals;

namespace roq {
namespace flags {
namespace utils {

std::string NonEmpty::unparse_helper() const {
  return absl::UnparseFlag(value_);
}

bool NonEmpty::parse_helper(std::string_view const &text, std::string &error) {
  if (!absl::ParseFlag(text, &value_, &error))
    return false;
  if (std::empty(value_)) {
    error = "can not be empty"s;
    return false;
  }
  return true;
}

}  // namespace utils
}  // namespace flags
}  // namespace roq
