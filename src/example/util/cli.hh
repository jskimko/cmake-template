#ifndef EXAMPLE_UTIL_CLI_HH
#define EXAMPLE_UTIL_CLI_HH

#include <cxxopts.hpp>
#include <string>

namespace example {

inline namespace v1 {
using namespace cxxopts;
} // namespace v1

class CLIParser : public Options {
public:
  CLIParser(std::string program = "example",
            std::string help = "example - an example project\n");
  ParseResult parse(int argc, char *argv[]);
};

} // namespace example

#endif // EXAMPLE_UTIL_CLI_HH
