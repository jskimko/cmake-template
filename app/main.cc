#include "example/example.hh"
#include <sstream>

int main(int argc, char *argv[]) {
  std::stringstream ss;

  ss << argv[0];
  for (int i=1; i<argc; i++) {
    ss << " " << argv[i];
  }

  example::log::log("{}", ss.view());
  return 0;
}
