#pragma once

#include <cstddef>
#include <array>
#include <stdexcept>
#include <iostream>
#include <vector>

namespace dj {
    class string_view {

    public:
        constexpr string_view() noexcept : _data(nullptr), _size(0) {}
        constexpr string_view(const char *str) : _data(str),
            _size(_length(str)) {}
    constexpr string_view(const char *str, const size_t &len) : _data(str), _size(len) {}

    // Size functions
    inline constexpr size_t size() const noexcept { return _size; }
    inline constexpr size_t length() const noexcept { return _size; }
    inline constexpr bool empty() const noexcept { return _size == 0; }

    // Element access
    constexpr char operator[](const size_t &pos) const {
        return (pos < _size) ? _data[pos] : throw std::out_of_range("Index out of range");
    }

    inline constexpr char front() const { return _data[0]; }
    inline constexpr char back() const { return _data[_size - 1]; }
    inline constexpr const char* data() const noexcept { return _data; }

    // Substring
    constexpr string_view substr(const size_t &pos, const size_t &count = npos) const {
        if (pos > _size) throw std::out_of_range("pos out of range");
        return string_view(_data + pos, (count > _size - pos) ? _size - pos : count);
    }

    // Iterators
    inline constexpr const char* begin() const noexcept { return _data; }
    inline constexpr const char* end() const noexcept { return _data + _size; }

    // Comparison operators
    constexpr bool operator==(const string_view& other) const noexcept {
        return _size== other._size && std::char_traits<char>::compare(_data, other._data, _size) == 0;
    }

    constexpr bool operator!=(const string_view& other) const noexcept {
        return !(*this == other);
    }

    // Output stream support
    friend std::ostream& operator<<(std::ostream& os, const string_view& sv) {
        return os.write(sv._data, sv._size);
    }

    // Find function (supports multi-character delimiter)
    size_t find(const string_view& needle, const size_t &start = 0) const {
        if (needle._size == 0 || _size < needle._size || start >= _size) return npos;
        for (size_t i = start; i <= _size - needle._size; ++i) {
            if (std::char_traits<char>::compare(_data + i, needle._data, needle._size) == 0) {
                return i;
            }
        }
        return npos;
    }

    // Split function with multi-character delimiter
    std::vector<string_view> split(const string_view& delimiter) const noexcept {
        std::vector<string_view> result;
        size_t start = 0, pos = 0;
        size_t delimiter_size = delimiter.size();

        while ((pos = find(delimiter, start)) != npos) {
            result.emplace_back(_data + start, pos - start);
            start = pos + delimiter_size;
        }

        if (start < _size) {
            result.emplace_back(_data + start, _size - start);
        }

        return result;
    }

    static bool contains(const char* chars, char c) noexcept {
        while (*chars) {
            if (*chars == c) return true;
            ++chars;
        }
        return false;
    }

    // Constants
    static constexpr size_t npos = -1;

    private:
        const char* _data;
        size_t _size;


    // Returns the length of the string_view
    constexpr static size_t _length(const char *str) {
        size_t len = 0;
        while (str && str[len] != '\0')
            ++len;
        return len;
    }

    };

}
