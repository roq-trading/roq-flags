/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/strings/string_view.h>

#include <string>

namespace roq {
namespace flags {
namespace utils {

struct ROQ_PUBLIC NonEmpty final {
  NonEmpty() = default;
  NonEmpty(std::string const &value) : value_(value) {}  // NOLINT

  operator std::string const &() const { return value_; }

  static std::string unparse(NonEmpty const &flag) { return flag.unparse_helper(); }

  static bool parse(absl::string_view text, NonEmpty *flag, std::string *error) {
    return (*flag).parse_helper(text, *error);
  }

 protected:
  std::string unparse_helper() const;
  bool parse_helper(std::string_view const &text, std::string &error);

 private:
  std::string value_;
};

}  // namespace utils
}  // namespace flags
}  // namespace roq
