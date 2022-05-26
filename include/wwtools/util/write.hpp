#ifndef WWTOOLS_UTIL_WRITE_HPP
#define WWTOOLS_UTIL_WRITE_HPP

#include <ostream>

namespace wwtools::util::write {
    template<typename T>
    inline void big_endian(const char *data, std::ostream& os) {
        char arr_data[sizeof(T)];
        std::memcpy(arr_data, data, sizeof(T));
        for (int i = sizeof(T) - 1; i >= 0; i--)
            os.put(arr_data[i]);
    }

    template<typename T>
    inline void big_endian(const T& data, std::ostream& os) {
        big_endian<T>(reinterpret_cast<const char *>(&data), os);
    }

    template<typename T>
    inline void little_endian(const char *data, std::ostream& os) {
        char arr_data[sizeof(T)];
        std::memcpy(arr_data, data, sizeof(T));
        for (int i = 0; i < sizeof(T); i++)
            os.put(arr_data[i]);
    }

    template<typename T>
    inline void little_endian(const T& data, std::ostream& os) {
        little_endian<T>(reinterpret_cast<const char *>(&data), os);
    }

    inline void raw_data(const char *data, size_t size, std::ostream& os) {
        os.write(data, size);
    }
} // namespace wwtools::util::write

#endif // WWTOOLS_UTIL_WRITE_HPP
