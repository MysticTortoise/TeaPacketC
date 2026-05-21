#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <cstdlib>
#include <functional>

namespace TeaPacket::Graphics::GX2
{
    template <typename T>
    class MEM2Resource
    {
    private:
        T* data = nullptr;
        int alignment = 0;
        bool Allocate()
        {
            DeAllocate();
            data = static_cast<T*>(std::aligned_alloc(alignment, sizeof(T)));
            return data == nullptr;
        }

        void DeAllocate()
        {
            if (data == nullptr) { return; }
            std::free(data);
        }

    public:
        // No Copy
        MEM2Resource& operator=(const MEM2Resource& other) = delete;
        MEM2Resource(const MEM2Resource& other) = delete;

        // Constructors
        MEM2Resource() = default;

        explicit MEM2Resource(const int alignment) : alignment(alignment)
        {
            Allocate();
        }

        ~MEM2Resource()
        {
            DeAllocate();
        }

        MEM2Resource(MEM2Resource&& other) noexcept
        {
            std::swap(alignment, other.alignment);
            std::swap(data, other.data);
        }

        T& operator*()
        {
            assert(data != nullptr);
            // ReSharper disable once CppDFANullDereference
            return *data;
        }

        const T& operator*() const
        {
            assert(data != nullptr);
            // ReSharper disable once CppDFANullDereference
            return *data;
        }

        [[nodiscard]] T* get() const
        {
            return data;
        }

        explicit operator bool() const
        {
            return data != nullptr;
        }
    };

    template <>
    class MEM2Resource<void>
    {
    private:
        void* data = nullptr;
        int alignment = 0;
        size_t size = 0;
        bool Allocate()
        {
            DeAllocate();
            data = std::aligned_alloc(alignment, size);
            return data != nullptr;
        }

        void DeAllocate() const
        {
            if (data == nullptr) { return; }
            std::free(data);
        }

    public:
        // No Copy
        MEM2Resource& operator=(const MEM2Resource& other) = delete;
        MEM2Resource(const MEM2Resource& other) = delete;

        // Constructors
        MEM2Resource() = default;

        explicit MEM2Resource(const int alignment, const size_t size) : alignment(alignment), size(size)
        {
            assert(Allocate());
        }

        ~MEM2Resource()
        {
            DeAllocate();
        }

        MEM2Resource(MEM2Resource&& other) noexcept
        {
            std::swap(alignment, other.alignment);
            std::swap(data, other.data);
            std::swap(size, other.size);
        }

        [[nodiscard]] void* get() const
        {
            return data;
        }

        explicit operator bool() const
        {
            return data != nullptr;
        }
    };
}
