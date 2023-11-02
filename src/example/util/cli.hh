#ifndef EXAMPLE_UTIL_CLI_HH
#define EXAMPLE_UTIL_CLI_HH

#include <cxxopts.hpp>
#include <string>

namespace example {

using namespace cxxopts;

class CLIParser : public cxxopts::Options {
public:
  CLIParser(std::string program = "example",
            std::string help = "example - an example project\n");
  ParseResult parse(int argc, char *argv[]);
};

} // namespace example

#endif // EXAMPLE_UTIL_CLI_HH
