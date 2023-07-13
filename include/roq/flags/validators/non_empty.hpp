/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/flags/flag.h>

#include <string>

namespace roq {
namespace flags {
namespace validators {

struct ROQ_PUBLIC NonEmpty final {
  using value_type = std::string;

  NonEmpty() = default;
  NonEmpty(value_type const &value) : value_{value} {}  // NOLINT

  operator value_type const &() const { return value_; }

  bool empty() const { return std::empty(value_); }

  static bool required() { return true; };

  // abseil
  static std::string unparse(NonEmpty const &);
  static bool parse(absl::string_view &, NonEmpty *&, std::string *&);

 private:
  value_type value_;
};

// abseil
extern std::string ROQ_PUBLIC AbslUnparseFlag(NonEmpty const &);
extern bool ROQ_PUBLIC AbslParseFlag(absl::string_view &, NonEmpty *&, std::string *&);

}  // namespace validators
}  // namespace flags
}  // namespace roq
