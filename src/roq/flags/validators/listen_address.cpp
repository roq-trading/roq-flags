/* Copyright (c) 2017-2026, Hans Erik Thrane */

#include "roq/flags/validators/listen_address.hpp"

#include <charconv>

using namespace std::literals;

namespace roq {
namespace flags {
namespace validators {

// === CONSTANTS ===

namespace {
auto const TCP_PREFIX = "tcp://"sv;
auto const HTTP_PREFIX = "http://";
auto const WS_PREFIX = "ws://";
auto const UNIX_PREFIX = "unix://"sv;
}  // namespace

// === HELPERS ===

namespace {
constexpr auto is_port(auto const &text) {
  uint16_t port = {};
  auto [ptr, ec] = std::from_chars(std::begin(text), std::end(text), port);
  return ec == std::errc{};
}

static_assert(is_port("123"sv));
static_assert(!is_port("/foo/bar"sv));
static_assert(!is_port(""sv));
}  // namespace

//  === IMPLEMENTATION ===

std::string ListenAddress::unparse(ListenAddress const &flag) {
  return absl::UnparseFlag(flag.value_);
}

bool ListenAddress::parse(absl::string_view &text, ListenAddress *&flag, std::string *&error) {
  if (!absl::ParseFlag(text, &(*flag).value_, error)) {
    return false;
  }
  if (std::empty((*flag).value_)) {
    return true;
  }
  if (is_port(text)) {
    return true;
  }
  if (text.starts_with(TCP_PREFIX) || text.starts_with(HTTP_PREFIX) || text.starts_with(WS_PREFIX)) {
    return true;
  }
  auto path = [&]() {
    auto text = (*flag).value_;
    if (text.starts_with(UNIX_PREFIX)) {
      return text.substr(std::size(UNIX_PREFIX));
    }
    return text;
  }();
  if (!path.starts_with('/')) {
    *error = "must be an absolute path"s;
    return false;
  }
  return true;
}

}  // namespace validators
}  // namespace flags
}  // namespace roq
