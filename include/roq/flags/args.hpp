/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/compat.hpp"

#include <span>
#include <string_view>
#include <vector>

#include "roq/args/parser.hpp"

namespace roq {
namespace flags {

struct ROQ_PUBLIC Args final : public args::Parser {
  Args(int argc, char **argv, std::string_view const &description, std::string_view const &version);

  operator std::span<std::string_view const>() const override { return args_; }

 private:
  std::vector<std::string_view> args_;
};

}  // namespace flags
}  // namespace roq
