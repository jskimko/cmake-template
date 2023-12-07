#ifndef EXAMPLE_UTIL_LOG_HH
#define EXAMPLE_UTIL_LOG_HH

#include <example/config.hh>
#include <source_location>
#include <fmt/core.h>

namespace example {
namespace log {

enum Level {
  ERROR = -10,
  NONE = 0,
  INFO = 10,
  DEBUG = 20,
  TRACE = 30
};

void vlog(int level, const fmt::string_view fmt, const fmt::format_args args);

template <typename... T>
void log(int level, const fmt::format_string<T...> fmt, T&&... args)
{ if constexpr(EXAMPLE_ENABLE_LOGGING) vlog(level, fmt, fmt::make_format_args(args...)); }

template <typename... T>
void error(const fmt::format_string<T...> fmt, T&&... args)
{ if constexpr(EXAMPLE_ENABLE_LOGGING) vlog(Level::ERROR, fmt, fmt::make_format_args(args...)); }

template <typename... T>
void info(const fmt::format_string<T...> fmt, T&&... args)
{ if constexpr(EXAMPLE_ENABLE_LOGGING) vlog(Level::INFO, fmt, fmt::make_format_args(args...)); }

template <typename... T>
void debug(const fmt::format_string<T...> fmt, T&&... args)
{ if constexpr(EXAMPLE_ENABLE_LOGGING) vlog(Level::DEBUG, fmt, fmt::make_format_args(args...)); }

template <typename... T>
void trace(const fmt::format_string<T...> fmt, T&&... args)
{ if constexpr(EXAMPLE_ENABLE_LOGGING) vlog(Level::TRACE, fmt, fmt::make_format_args(args...)); }

void vsource(const fmt::string_view fmt, const fmt::format_args args,
             const std::source_location loc);

template <typename... T>
struct source {
  source(const fmt::format_string<T...> fmt, T&&... args,
         const std::source_location loc = std::source_location::current()) {
    vsource(fmt, fmt::make_format_args(args...), loc);
  }
};

template <typename... T>
source(const fmt::format_string<T...>, T&&...) -> source<T...>;

} // namespace log
} // namespace example

#endif // EXAMPLE_UTIL_LOG_HH

