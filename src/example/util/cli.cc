#include "example/util/cli.hh"
#include "example/util/log.hh"
#include "example/util/except.hh"
#include "example/config.hh"

namespace example {

CLIParser::CLIParser(std::string program, std::string help)
  : cxxopts::Options(std::move(program), std::move(help))
{
  try {
    set_width(100);

    add_options()
      ("v,verbose", "set verbose level (trace|debug|info|warn|err|critical|off)", 
        cxxopts::value<std::string>()->default_value(EXAMPLE_DEFAULT_VERBOSE_LEVEL), "LEVEL")
      ("h,help", "print help message")
    ;

    add_options("positional")
      ("pos", "a positional arg", 
        cxxopts::value<std::string>())
    ;
    parse_positional({"pos"});
    positional_help("pos");
    show_positional_help();

  } catch (cxxopts::exceptions::specification const &e) {
    throw Exception(e.what());
  }
}

ParseResult 
CLIParser::parse(int argc, char *argv[])
{
  log::set_pattern("%v");

  auto usage = [this]() {
    log::info("{}", help());
    std::exit(0);
  };

  if (argc == 1) { usage(); }

  cxxopts::ParseResult args;
  try {
    args = cxxopts::Options::parse(argc, argv);
  } catch (cxxopts::exceptions::parsing const &e) {
    throw Exception(e.what());
  }

  if (args.count("help")) { usage(); }

  // set verbose level
  auto before = log::get_level();
  log::set_level(log::level::from_str(args["verbose"].as<std::string>()));
  if (log::get_level() == log::level::off && before != log::level::off) {
    log::error("invalid verbose level: {}\n", args["verbose"].as<std::string>());
    std::exit(1);
  }

  return args;
}

} // namespace example

