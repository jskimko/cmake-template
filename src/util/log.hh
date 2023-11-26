#ifndef EXAMPLE_UTIL_LOG_HH
#define EXAMPLE_UTIL_LOG_HH

#include <source_location>
#include <fmt/core.h>

namespace example {
namespace log {

void vlog(const fmt::string_view fmt, const fmt::format_args args,
          const std::source_location loc);

template <typename... T>
struct log {
  log(const fmt::format_string<T...> fmt, T&&... args,
      const std::source_location loc = std::source_location::current()) {
    vlog(fmt, fmt::make_format_args(args...), loc);
  }
};

template <typename... T>
log(const fmt::format_string<T...>, T&&...) -> log<T...>;

} // namespace log
} // namespace example

#endif // EXAMPLE_UTIL_LOG_HH

