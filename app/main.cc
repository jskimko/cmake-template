#include <example/example.hh>

int main(int argc, char *argv[]) {
  std::string s;

  fmt::format_to(std::back_inserter(s), "{}", argv[0]);
  for (int i=1; i<argc; i++) {
    fmt::format_to(std::back_inserter(s), " {}", argv[i]);
  }

  example::log::log("{}", s);
  return 0;
}
