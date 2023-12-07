#ifndef EXAMPLE_SETTINGS_HH
#define EXAMPLE_SETTINGS_HH

#include <example/util/types.hh>
#include <unordered_map>
#include <type_traits>
#include <string>

namespace example {

class Settings {
public:

  static void set(std::string const &key, std::string val) { strings_[key] = std::move(val); }
  static void set(std::string const &key, int val) { ints_[key] = val; }

  template <typename T>
  static auto get(std::string const &s)
  { 
    if constexpr(std::is_same<T, std::string>::value) {
      return strings_.at(s);
    } else if constexpr(std::is_same<T, int>::value) {
      return ints_.at(s);
    } else {
      throw Exception("invalid key type");
    }
  }

private:
  static std::unordered_map<std::string, std::string> strings_;
  static std::unordered_map<std::string, int> ints_;
};

} // namespace example

#endif // EXAMPLE_SETTINGS_HH

