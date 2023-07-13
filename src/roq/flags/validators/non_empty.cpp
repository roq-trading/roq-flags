/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/validators/non_empty.hpp"

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

std::string NonEmpty::unparse(NonEmpty const &flag) {
  return absl::UnparseFlag(flag.value_);
}

bool NonEmpty::parse(absl::string_view &text, NonEmpty *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error))
    return false;
  if (std::empty((*flag).value_)) {
    *error = "can not be empty"s;
    return false;
  }
  return true;
}

std::string AbslUnparseFlag(NonEmpty const &flag) {
  return NonEmpty::unparse(flag);
}

bool AbslParseFlag(absl::string_view &text, NonEmpty *&flag, std::string *&error) {
  return NonEmpty::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
