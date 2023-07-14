/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/validators/required_path.hpp"

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

std::string RequiredPath::unparse(RequiredPath const &flag) {
  return absl::UnparseFlag(flag.value_);
}

bool RequiredPath::parse(absl::string_view &text, RequiredPath *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error))
    return false;
  if (std::empty((*flag).value_)) {
    *error = "can not be empty"s;
    return false;
  }
  return true;
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
