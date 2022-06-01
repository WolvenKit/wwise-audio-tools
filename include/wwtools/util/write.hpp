#ifndef WWTOOLS_UTIL_WRITE_HPP
#define WWTOOLS_UTIL_WRITE_HPP

#include <cstring>
#include <ostream>

/**
 * @namespace wwtools::util::write
 * @brief helper functions for writing data
 */
namespace wwtools::util::write {
/**
 * @brief write data in reverse
 *
 * @tparam T type to detect size of data
 * @param data data to be written
 * @param os ostream to write data
 */
template <typename T>
inline void big_endian(const char *data, std::ostream &os) {
  char arr_data[sizeof(T)];
  std::memcpy(arr_data, data, sizeof(T));
  for (int i = sizeof(T) - 1; i >= 0; i--)
    os.put(arr_data[i]);
}

/**
 * @brief write data of a certain type in reverse order
 *
 * @tparam T type for data and size
 * @param data data to be written
 * @param os location for data to be written
 */
template <typename T> inline void big_endian(const T &data, std::ostream &os) {
  big_endian<T>(reinterpret_cast<const char *>(&data), os);
}

/**
 * @brief write data to a stream
 *
 * @tparam T type do determine size of data
 * @param data data to be written
 * @param os location for data to be written
 */
template <typename T>
inline void little_endian(const char *data, std::ostream &os) {
  char arr_data[sizeof(T)];
  std::memcpy(arr_data, data, sizeof(T));
  for (int i = 0; i < sizeof(T); i++)
    os.put(arr_data[i]);
}

/**
 * @brief write data of a certain type to a stream
 *
 * @tparam T type for data and size
 * @param data data to be written
 * @param os location for data to be written
 */
template <typename T>
inline void little_endian(const T &data, std::ostream &os) {
  little_endian<T>(reinterpret_cast<const char *>(&data), os);
}

/**
 * @brief wrapper around os::write
 *
 * @param data data to be written
 * @param size the size of the data
 * @param os output stream to write to
 */
inline void raw_data(const char *data, size_t size, std::ostream &os) {
  os.write(data, size);
}
} // namespace wwtools::util::write

#endif // WWTOOLS_UTIL_WRITE_HPP
