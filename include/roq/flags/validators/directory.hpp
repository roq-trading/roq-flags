/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <absl/flags/flag.h>

#include <string>

namespace roq {
namespace flags {
namespace validators {

struct ROQ_PUBLIC Directory final {
  using value_type = std::string;

  Directory() = default;
  Directory(value_type const &value) : value_{value} {}

  operator value_type const &() const { return value_; }

  bool empty() const { return std::empty(value_); }

  static bool required() { return true; };

  // abseil

  static std::string unparse(Directory const &);
  static bool parse(absl::string_view &, Directory *&, std::string *&);

 private:
  value_type value_;
};

inline std::string AbslUnparseFlag(roq::flags::validators::Directory const &flag) {
  using value_type = std::remove_cvref<decltype(flag)>::type;
  return value_type::unparse(flag);
}

inline bool AbslParseFlag(absl::string_view &text, roq::flags::validators::Directory *&flag, std::string *&error) {
  using value_type = std::remove_cvref<decltype(*flag)>::type;
  return value_type::parse(text, flag, error);
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
