#pragma once

#include <vector>
#include <initializer_list>
#include <span>

namespace TeaPacket
{
    template<typename T>
    class SpanView
    {
    private:
        const T* _data = nullptr;
        const size_t _size = 0;

    public:
        constexpr SpanView(const T* data, const size_t size):
        _data(data), _size(size) {}

        constexpr SpanView(const std::vector<T>& other):
        _data(other.data()), _size(other.size()) {}

        constexpr SpanView(const std::span<T>& other):
        _data(other.data()), _size(other.size()) {}

        constexpr SpanView(const std::initializer_list<T>& other):
        _data(other.begin()), _size(other.size()) {}

        template<size_t i>
        constexpr SpanView(const std::array<T,i>& other):
        _data(other.data()), _size(i) {}


        [[nodiscard]] constexpr const T* data() const
        {
            return _data;
        }

        [[nodiscard]] constexpr size_t size() const
        {
            return _size;
        }
    };
}
