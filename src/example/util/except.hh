#ifndef EXAMPLE_UTIL_EXCEPTION_HH
#define EXAMPLE_UTIL_EXCEPTION_HH

#include <stdexcept>

namespace example {

class Exception : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

} // namespace example

#endif // EXAMPLE_UTIL_EXCEPTION_HH
