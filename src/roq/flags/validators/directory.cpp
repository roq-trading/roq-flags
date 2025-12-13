/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/flags/validators/directory.hpp"

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

std::string Directory::unparse(Directory const &flag) {
  return absl::UnparseFlag(flag.value_);
}

bool Directory::parse(absl::string_view &text, Directory *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error)) {
    return false;
  }
  if (std::empty((*flag).value_)) {
    *error = "can not be empty"s;
    return false;
  }
  return true;
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
