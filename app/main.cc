#include "example/example.hh"

int main(int argc, char *argv[]) {
  example::CLIParser cli;
  auto args = cli.parse(argc, argv);
  
  return 0;
}
