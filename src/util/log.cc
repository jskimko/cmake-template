#include "example/util/log.hh"
#include <cstdio>

namespace example {
namespace log {

void vlog(const fmt::string_view fmt, const fmt::format_args args,
          const std::source_location loc)
{
  fmt::print("[{}:{}:{}] {}\n", loc.file_name(), loc.line(), 
                                loc.function_name(), fmt::vformat(fmt, args));
}

} // namespace log
} // namespace example
