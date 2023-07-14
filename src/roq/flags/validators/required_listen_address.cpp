/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/flags/validators/required_listen_address.hpp"

#include <charconv>

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

//  === HELPERS ===

namespace {
constexpr auto is_port(auto const &text) {
  uint16_t port = {};
  auto [ptr, ec] = std::from_chars(std::begin(text), std::end(text), port);
  return ec == std::errc{};
}

#if __cplusplus >= 202301L
static_assert(is_port("123"sv));
static_assert(is_port("/foo/bar"sv) == false);
static_assert(is_port(""sv) == false);
#endif
}  // namespace

//  === IMPLEMENTATION ===

std::string RequiredListenAddress::unparse(RequiredListenAddress const &flag) {
  return absl::UnparseFlag(flag.value_);
}

bool RequiredListenAddress::parse(absl::string_view &text, RequiredListenAddress *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error))
    return false;
  if (std::empty((*flag).value_)) {
    *error = "can not be empty"s;
    return true;
  }
  uint16_t port = {};
  auto [ptr, ec] = std::from_chars(std::begin(text), std::end(text), port);
  if (ec == std::errc{}) {  // port
    return true;
  } else {  // unix path
    if ((*flag).value_[0] != '/') {
      *error = "must be an absolute path"s;
      return false;
    }
  }
  return true;
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
