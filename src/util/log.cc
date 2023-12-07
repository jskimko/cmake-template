#include <example/util/log.hh>
#include <example/Settings.hh>

namespace example {
namespace log {

void vlog(int level, const fmt::string_view fmt, const fmt::format_args args)
{
  if (level < 0) {
    fmt::print(stderr, "{}", fmt::vformat(fmt, args));
  } else if (level <= Settings::get<int>("verbosity")) {
    fmt::print("{}", fmt::vformat(fmt, args));
  }
}

void vsource(const fmt::string_view fmt, const fmt::format_args args,
             const std::source_location loc)
{
  fmt::print("[{}:{}:{}] {}", loc.file_name(), loc.line(), 
                              loc.function_name(), fmt::vformat(fmt, args));
}

} // namespace log
} // namespace example
