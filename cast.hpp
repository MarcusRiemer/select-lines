#ifndef CAST_HPP
#define CAST_HPP

#include <sstream>

/* Taken from ranisalt on github because I didn't want external dependencies
 * https://gist.github.com/ranisalt/7bb2af8b7fa21dd7eeb2b4e8f7aef156 */

/* fallback */
template <class T> T lexical_cast(const std::string &str) {
  static std::istringstream
      ss; /* reusing has severe (positive) impact on performance */
  T value;
  ss.str(str);
  ss >> value;
  ss.clear();
  return value;
}

/* trivial conversion */
template <> std::string lexical_cast(const std::string &str) { return str; }

/* conversions that exist in stl */
template <> float lexical_cast(const std::string &str) {
  return std::strtof(str.c_str(), nullptr);
}
template <> long lexical_cast(const std::string &str) {
  return std::strtol(str.c_str(), nullptr, 0);
}
template <> long long lexical_cast(const std::string &str) {
  return std::strtoll(str.c_str(), nullptr, 0);
}
template <> unsigned long lexical_cast(const std::string &str) {
  return std::strtoul(str.c_str(), nullptr, 0);
}
template <> unsigned long long lexical_cast(const std::string &str) {
  return std::strtoull(str.c_str(), nullptr, 0);
}

/* conversions that need to be truncated */
template <> short lexical_cast(const std::string &str) {
  return static_cast<short>(lexical_cast<long>(str));
}
template <> int lexical_cast(const std::string &str) {
  return static_cast<int>(lexical_cast<long>(str));
}
template <> unsigned short lexical_cast(const std::string &str) {
  return static_cast<unsigned short>(lexical_cast<unsigned long>(str));
}
template <> unsigned int lexical_cast(const std::string &str) {
  return static_cast<unsigned int>(lexical_cast<unsigned long>(str));
}

#endif // CAST_HPP
