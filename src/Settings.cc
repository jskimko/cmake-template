#include <example/Settings.hh>
#include <example/config.hh>
#include <example/util/log.hh>

namespace example {

std::unordered_map<std::string, std::string> Settings::strings_;
std::unordered_map<std::string, int> Settings::ints_ = {
  {"verbosity", log::EXAMPLE_DEFAULT_VERBOSITY}
};

} // namespace example

