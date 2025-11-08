//==============================================================================
// File        : MathTransform.h
// Description : A 3-dimensional vector class template supporting arithmetic operations,
//               normalization, dot/cross products, and interoperability with DirectX types.
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// Project Settings:
// - C/C++ Compiler Additional Options can be set via the project properties.
//   ([Project Properties] Å® [C/C++] Å® [Command Line] Å® Additional Options)
//    For C++17 and later support, use: /Zc:__cplusplus
//==============================================================================
#pragma once

#include <memory>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <stdexcept>
#include <initializer_list>
#include <limits>
#include <DirectXMath.h>

#define IX_PI (3.141592654f)

#if __cplusplus >= 202002L
#define IX_CONSTEXPR20 inline constexpr
#else
#define IX_CONSTEXPR20 inline
#endif

#if __cplusplus >= 201703L
#define IX_CONSTEXPR17 inline constexpr
#define IX_NODISCARD [[nodiscard]]
#define IX_IF_CONSTEXPR if constexpr
#else
#define IX_CONSTEXPR17 inline
#define IX_NODISCARD
#define IX_IF_CONSTEXPR if
#endif

#if __cplusplus >= 201402L
#define IX_CONSTEXPR14 inline constexpr
#else
#define IX_CONSTEXPR14 inline
#endif

#undef min
#undef max

namespace math {  

    template<typename T = float>
    class vector2 {
        static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
            "vector2<T>: T must be numeric (int, float, double), bool not allowed");

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        static constexpr size_type dimension = 2;

    public:
        T x, y;

        IX_CONSTEXPR14 vector2() noexcept : x(0), y(0) {}
        IX_CONSTEXPR14 vector2(T nx, T ny) noexcept : x(nx), y(ny) {}
        IX_CONSTEXPR14 vector2(const vector2& v) noexcept = default;
        explicit vector2(const DirectX::XMFLOAT2& v) noexcept : x(v.x), y(v.y) {}

        IX_NODISCARD IX_CONSTEXPR14 bool operator==(const vector2& v) const noexcept { return x == v.x && y == v.y; }
        IX_NODISCARD IX_CONSTEXPR14 bool operator!=(const vector2& v) const noexcept { return !(*this == v); }

        IX_CONSTEXPR14 vector2& operator=(const vector2& v) noexcept = default;
        IX_CONSTEXPR14 vector2& operator+=(const vector2& v) noexcept { x += v.x; y += v.y; return *this; }
        IX_CONSTEXPR14 vector2& operator-=(const vector2& v) noexcept { x -= v.x; y -= v.y; return *this; }
        IX_CONSTEXPR14 vector2& operator*=(T s) noexcept { x *= s; y *= s; return *this; }
        IX_CONSTEXPR17 vector2& operator/=(T s) { *this = *this / s; return *this; }

        IX_NODISCARD IX_CONSTEXPR17 vector2 operator-() const noexcept { return vector2(-x, -y); }
        IX_NODISCARD IX_CONSTEXPR17 vector2 operator+(const vector2& v) const noexcept { return vector2(x + v.x, y + v.y); }
        IX_NODISCARD IX_CONSTEXPR17 vector2 operator-(const vector2& v) const noexcept { return vector2(x - v.x, y - v.y); }
        IX_NODISCARD IX_CONSTEXPR17 vector2 operator*(T s) const noexcept { return vector2(x * s, y * s); } // Ç±ÇÍÇæÇØÉGÉâÅ[
        IX_NODISCARD IX_CONSTEXPR17 vector2 operator*(const vector2& v) const noexcept { return vector2(x * v.x, y * v.y); }

        IX_CONSTEXPR17 reference operator[](size_type i) noexcept { return (i == 0 ? x : y); }
        IX_CONSTEXPR17 const_reference operator[](size_type i) const noexcept { return (i == 0 ? x : y); }

        IX_CONSTEXPR20 reference at(size_type i) { if (i >= dimension) throw std::out_of_range("vector2::at()"); return (i == 0 ? x : y); }
        IX_CONSTEXPR20 const_reference at(size_type i) const { if (i >= dimension) throw std::out_of_range("vector2::at()"); return (i == 0 ? x : y); }

        IX_CONSTEXPR17 pointer begin() noexcept { return &x; }
        IX_CONSTEXPR17 pointer end() noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer begin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer end() const noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer cbegin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer cend() const noexcept { return &x + dimension; }

        IX_CONSTEXPR17 void zero() noexcept { x = y = T(0); }

        IX_NODISCARD IX_CONSTEXPR14 T dot(const vector2& v) const noexcept { return x * v.x + y * v.y; }

#if __cplusplus >= 202002L
        IX_NODISCARD IX_CONSTEXPR20 T length() const requires std::is_floating_point_v<T> {
            return std::sqrt(x * x + y * y);
        }

        IX_NODISCARD IX_CONSTEXPR20 T lengthSquared() const requires std::is_floating_point_v<T> {
            return x * x + y * y;
        }
        IX_NODISCARD IX_CONSTEXPR20 vector2 operator/(T s) const requires std::is_floating_point_v<T> {
            return (s != T(0)) ? vector2(x / s, y / s) : vector2(T(0), T(0));
        }
        IX_CONSTEXPR20 void normalize() requires std::is_floating_point_v<T> {
            T len = length();
            if (len > std::numeric_limits<T>::epsilon()) *this /= len;
        }

        IX_NODISCARD IX_CONSTEXPR20 vector2 normalized() const requires std::is_floating_point_v<T> {
            T len = length();
            return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector2(T(0), T(0));
        }
#else
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR20 T length() const noexcept {
            return std::sqrt(x * x + y * y);
        }
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR20 T lengthSquared() const noexcept {
            return x * x + y * y;
        }
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector2 operator/(T s) const {
            return (s != T(0)) ? vector2(x / s, y / s) : vector2(T(0), T(0));
        }
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_CONSTEXPR17 void normalize() {
            T len = length();
            if (len > std::numeric_limits<T>::epsilon()) *this /= len;
        }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector2 normalized() const {
            T len = length();
            return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector2(T(0), T(0));
        }
#endif
        DirectX::XMVECTOR toXMVECTOR() const noexcept { return DirectX::XMVectorSet(x, y, 0, 0); }
    };

    template<typename T = float>
    class vector3 {
        static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
            "vector3<T>: T must be numeric (int, float, double), bool not allowed");

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        static constexpr size_type dimension = 3;

    public:
        T x, y, z;

        IX_CONSTEXPR14 vector3() noexcept : x(0), y(0), z(0) {}
        IX_CONSTEXPR14 vector3(T nx, T ny, T nz) noexcept : x(nx), y(ny), z(nz) {}
        IX_CONSTEXPR14 vector3(const vector3& v) noexcept = default;
        explicit vector3(const DirectX::XMFLOAT3& v) noexcept : x(v.x), y(v.y), z(v.z) {}

        IX_NODISCARD IX_CONSTEXPR14 bool operator==(const vector3& v) const noexcept { return x == v.x && y == v.y && z == v.z; }
        IX_NODISCARD IX_CONSTEXPR14 bool operator!=(const vector3& v) const noexcept { return !(*this == v); }

        IX_CONSTEXPR14 vector3& operator=(const vector3& v) noexcept = default;
        IX_CONSTEXPR14 vector3& operator+=(const vector3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
        IX_CONSTEXPR14 vector3& operator-=(const vector3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
        IX_CONSTEXPR14 vector3& operator*=(T s) noexcept { x *= s; y *= s; z *= s; return *this; }
        IX_CONSTEXPR17 vector3& operator/=(T s) { *this = *this / s; return *this; }

        IX_NODISCARD IX_CONSTEXPR17 vector3 operator-() const noexcept { return vector3(-x, -y, -z); }
        IX_NODISCARD IX_CONSTEXPR17 vector3 operator+(const vector3& v) const noexcept { return vector3(x + v.x, y + v.y, z + v.z); }
        IX_NODISCARD IX_CONSTEXPR17 vector3 operator-(const vector3& v) const noexcept { return vector3(x - v.x, y - v.y, z - v.z); }
        IX_NODISCARD IX_CONSTEXPR17 vector3 operator*(T s) const noexcept { return vector3(x * s, y * s, z * s); }
        IX_NODISCARD IX_CONSTEXPR17 vector3 operator*(const vector3& v) const noexcept { return vector3(x * v.x, y * v.y, z * v.z); }

        IX_CONSTEXPR17 reference operator[](size_type i) noexcept { return (i == 0 ? x : (i == 1 ? y : z)); }
        IX_CONSTEXPR17 const_reference operator[](size_type i) const noexcept { return (i == 0 ? x : (i == 1 ? y : z)); }

        IX_CONSTEXPR20 reference at(size_type i) { if (i >= dimension) throw std::out_of_range("vector3::at()"); return (i == 0 ? x : (i == 1 ? y : z)); }
        IX_CONSTEXPR20 const_reference at(size_type i) const { if (i >= dimension) throw std::out_of_range("vector3::at()"); return (i == 0 ? x : (i == 1 ? y : z)); }

        IX_CONSTEXPR17 pointer begin() noexcept { return &x; }
        IX_CONSTEXPR17 pointer end() noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer begin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer end() const noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer cbegin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer cend() const noexcept { return &x + dimension; }

        IX_CONSTEXPR17 void zero() noexcept { x = y = z = T(0); }

        IX_NODISCARD IX_CONSTEXPR14 T dot(const vector3& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
        IX_NODISCARD IX_CONSTEXPR14 vector3 cross(const vector3& v) const noexcept { return vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

#if __cplusplus >= 202002L
        IX_NODISCARD IX_CONSTEXPR20 T length() const requires std::is_floating_point_v<T> { return std::sqrt(x * x + y * y + z * z); }
        IX_NODISCARD IX_CONSTEXPR20 T lengthSquared() const requires std::is_floating_point_v<T> { return x * x + y * y + z * z; }
        IX_NODISCARD IX_CONSTEXPR20 vector3 operator/(T s) const requires std::is_floating_point_v<T> { return (s != T(0)) ? vector3(x / s, y / s, z / s) : vector3(T(0), T(0), T(0)); }
        IX_CONSTEXPR20 void normalize() requires std::is_floating_point_v<T> { T len = length(); if (len > std::numeric_limits<T>::epsilon()) *this /= len; }
        IX_NODISCARD IX_CONSTEXPR20 vector3 normalized() const requires std::is_floating_point_v<T> { T len = length(); return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector3(T(0), T(0), T(0)); }
#else
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 T length() const noexcept { return std::sqrt(x * x + y * y + z * z); }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 T lengthSquared() const noexcept { return x * x + y * y + z * z; }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector3 operator/(T s) const { return (s != T(0)) ? vector3(x / s, y / s, z / s) : vector3(T(0), T(0), T(0)); }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_CONSTEXPR17 void normalize() { T len = length(); if (len > std::numeric_limits<T>::epsilon()) *this /= len; }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector3 normalized() const { T len = length(); return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector3(T(0), T(0), T(0)); }
#endif
        DirectX::XMVECTOR toXMVECTOR() const noexcept { return DirectX::XMVectorSet(x, y, z, 0); }
    };

    template<typename T = float>
    class vector4 {
        static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
            "vector4<T>: T must be numeric (int, float, double), bool not allowed");

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        static constexpr size_type dimension = 4;

    public:
        T x, y, z, w;

        IX_CONSTEXPR14 vector4() noexcept : x(0), y(0), z(0), w(0) {}
        IX_CONSTEXPR14 vector4(T nx, T ny, T nz, T nw) noexcept : x(nx), y(ny), z(nz), w(nw) {}
        IX_CONSTEXPR14 vector4(const vector4& v) noexcept = default;
        explicit vector4(const DirectX::XMFLOAT4& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}

        IX_NODISCARD IX_CONSTEXPR14 bool operator==(const vector4& v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
        IX_NODISCARD IX_CONSTEXPR14 bool operator!=(const vector4& v) const noexcept { return !(*this == v); }

        IX_CONSTEXPR14 vector4& operator=(const vector4& v) noexcept = default;
        IX_CONSTEXPR14 vector4& operator+=(const vector4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
        IX_CONSTEXPR14 vector4& operator-=(const vector4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
        IX_CONSTEXPR14 vector4& operator*=(T s) noexcept { x *= s; y *= s; z *= s; w *= s; return *this; }
        IX_CONSTEXPR17 vector4& operator/=(T s) { *this = *this / s; return *this; }

        IX_NODISCARD IX_CONSTEXPR17 vector4 operator-() const noexcept { return vector4(-x, -y, -z, -w); }
        IX_NODISCARD IX_CONSTEXPR17 vector4 operator+(const vector4& v) const noexcept { return vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
        IX_NODISCARD IX_CONSTEXPR17 vector4 operator-(const vector4& v) const noexcept { return vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
        IX_NODISCARD IX_CONSTEXPR17 vector4 operator*(T s) const noexcept { return vector4(x * s, y * s, z * s, w * s); }
        IX_NODISCARD IX_CONSTEXPR17 vector4 operator*(const vector4& v) const noexcept { return vector4(x * v.x, y * v.y, z * v.z, w * v.w); }

        IX_CONSTEXPR17 reference operator[](size_type i) noexcept { return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w))); }
        IX_CONSTEXPR17 const_reference operator[](size_type i) const noexcept { return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w))); }

        IX_CONSTEXPR20 reference at(size_type i) { if (i >= dimension) throw std::out_of_range("vector4::at()"); return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w))); }
        IX_CONSTEXPR20 const_reference at(size_type i) const { if (i >= dimension) throw std::out_of_range("vector4::at()"); return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w))); }

        IX_CONSTEXPR17 pointer begin() noexcept { return &x; }
        IX_CONSTEXPR17 pointer end() noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer begin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer end() const noexcept { return &x + dimension; }
        IX_CONSTEXPR17 const_pointer cbegin() const noexcept { return &x; }
        IX_CONSTEXPR17 const_pointer cend() const noexcept { return &x + dimension; }

        IX_CONSTEXPR17 void zero() noexcept { x = y = z = w = T(0); }

        IX_NODISCARD IX_CONSTEXPR14 T dot(const vector4& v) const noexcept { return x * v.x + y * v.y + z * v.z + w * v.w; }

#if __cplusplus >= 202002L
        IX_NODISCARD IX_CONSTEXPR20 T length() const requires std::is_floating_point_v<T> { return std::sqrt(x * x + y * y + z * z + w * w); }
        IX_NODISCARD IX_CONSTEXPR20 T lengthSquared() const requires std::is_floating_point_v<T> { return x * x + y * y + z * z + w * w; }
        IX_NODISCARD IX_CONSTEXPR20 vector4 operator/(T s) const requires std::is_floating_point_v<T> { return (s != T(0)) ? vector4(x / s, y / s, z / s, w / s) : vector4(T(0), T(0), T(0), T(0)); }
        IX_CONSTEXPR20 void normalize() requires std::is_floating_point_v<T> { T len = length(); if (len > std::numeric_limits<T>::epsilon()) *this /= len; }
        IX_NODISCARD IX_CONSTEXPR20 vector4 normalized() const requires std::is_floating_point_v<T> { T len = length(); return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector4(T(0), T(0), T(0), T(0)); }
#else
        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 T length() const noexcept { return std::sqrt(x * x + y * y + z * z + w * w); }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 T lengthSquared() const noexcept { return x * x + y * y + z * z + w * w; }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector4 operator/(T s) const { return (s != T(0)) ? vector4(x / s, y / s, z / s, w / s) : vector4(T(0), T(0), T(0), T(0)); }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_CONSTEXPR17 void normalize() { T len = length(); if (len > std::numeric_limits<T>::epsilon()) *this /= len; }

        template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
        IX_NODISCARD IX_CONSTEXPR17 vector4 normalized() const { T len = length(); return (len > std::numeric_limits<T>::epsilon()) ? *this / len : vector4(T(0), T(0), T(0), T(0)); }
#endif
        DirectX::XMVECTOR toXMVECTOR() const noexcept { return DirectX::XMVectorSet(x, y, z, w); }
    };

#if __cplusplus >= 202002L
    template<typename Vec, typename T = typename Vec::value_type>
        requires std::is_floating_point_v<T>
    IX_NODISCARD IX_CONSTEXPR20 auto normalize(const Vec& v) noexcept {
        T len = T(0);
        IX_IF_CONSTEXPR(Vec::dimension >= 1) len += v.x * v.x;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) len += v.y * v.y;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) len += v.z * v.z;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) len += v.w * v.w;
        len = std::sqrt(len);
        if (len < std::numeric_limits<typename Vec::value_type>::epsilon()) return v;
        Vec result;
        IX_IF_CONSTEXPR(Vec::dimension >= 1) result.x = v.x / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) result.y = v.y / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) result.z = v.z / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) result.w = v.w / len;
        return result;
    }
    template<typename Vec, typename T = typename Vec::value_type>
        requires std::is_floating_point_v<T>
    IX_NODISCARD IX_CONSTEXPR20 auto angleBetween(const Vec& a, const Vec& b) noexcept {
        T mag = length(a) * length(b);
        if (mag < std::numeric_limits<T>::epsilon()) return T(0);
        T cosTheta = std::clamp(dot(a, b) / mag, T(-1), T(1));
        return std::acos(cosTheta);
    }
    template<typename Vec, typename T = typename Vec::value_type>
        requires std::is_floating_point_v<T>
    IX_NODISCARD IX_CONSTEXPR17 Vec lerp(const Vec& a, const Vec& b, T t) noexcept {
        Vec result;
        IX_IF_CONSTEXPR(Vec::dimension >= 1) result.x = a.x + (b.x - a.x) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) result.y = a.y + (b.y - a.y) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) result.z = a.z + (b.z - a.z) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) result.w = a.w + (b.w - a.w) * t;
        return result;
    }
#elif __cplusplus >= 201703L
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR20 auto normalize(const Vec& v) noexcept {
        T len = T(0);
        IX_IF_CONSTEXPR(Vec::dimension >= 1) len += v.x * v.x;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) len += v.y * v.y;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) len += v.z * v.z;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) len += v.w * v.w;
        len = std::sqrt(len);
        if (len < std::numeric_limits<typename Vec::value_type>::epsilon()) return v;
        Vec result;
        IX_IF_CONSTEXPR(Vec::dimension >= 1) result.x = v.x / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) result.y = v.y / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) result.z = v.z / len;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) result.w = v.w / len;
        return result;
    }
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR20 auto angleBetween(const Vec& a, const Vec& b) noexcept {
        T mag = length(a) * length(b);
        if (mag < std::numeric_limits<T>::epsilon()) return T(0);
        T cosTheta = std::clamp(dot(a, b) / mag, T(-1), T(1));
        return std::acos(cosTheta);
    }
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR17 Vec lerp(const Vec& a, const Vec& b, T t) noexcept {
        Vec result;
        IX_IF_CONSTEXPR(Vec::dimension >= 1) result.x = a.x + (b.x - a.x) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 2) result.y = a.y + (b.y - a.y) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 3) result.z = a.z + (b.z - a.z) * t;
        IX_IF_CONSTEXPR(Vec::dimension >= 4) result.w = a.w + (b.w - a.w) * t;
        return result;
    }
#else
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR20 auto normalize(const Vec& v) noexcept {
        T len = T(0);
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            len += v[i] * v[i];
        }
        len = std::sqrt(len);
        if (len < std::numeric_limits<typename Vec::value_type>::epsilon()) return v;
        Vec result;
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            result[i] = v[i] / len;
        }
        return result;
    }
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR20 auto angleBetween(const Vec& a, const Vec& b) noexcept {
        T mag = length(a) * length(b);
        if (mag < std::numeric_limits<T>::epsilon()) return T(0);
        T cosTheta = dot(a, b) / mag;
        if (cosTheta < T(-1)) cosTheta = T(-1);
        else if (cosTheta > T(1)) cosTheta = T(1);
        return std::acos(cosTheta);
    }
    template<typename Vec, typename T = typename Vec::value_type, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    IX_NODISCARD IX_CONSTEXPR17 Vec lerp(const Vec& a, const Vec& b, T t) noexcept {
        Vec result;
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            result[i] = a[i] + (b[i] - a[i]) * t;
        }
        return result;
    }
#endif
    template<typename Vec>
    IX_NODISCARD IX_CONSTEXPR17 Vec vmin(const Vec& a, const Vec& b) noexcept {
        Vec result;
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            result[i] = std::min(a[i], b[i]);
        }
        return result;
    }
    template<typename Vec>
    IX_NODISCARD IX_CONSTEXPR17 Vec vmax(const Vec& a, const Vec& b) noexcept {
        Vec result;
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            result[i] = std::max(a[i], b[i]);
        }
        return result;
    }
    template<typename Vec>
    IX_NODISCARD IX_CONSTEXPR17 Vec operator*(typename Vec::value_type s, const Vec& v) noexcept {
        return v * s;
    }

    template<typename Vec, typename T = typename Vec::value_type>
    IX_NODISCARD IX_CONSTEXPR17 T dot(const Vec& a, const Vec& b) noexcept {
        T result = T(0);
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            result += a[i] * b[i];
        }
        return result;
    }
    template<typename Vec, typename T = typename Vec::value_type>
    IX_NODISCARD IX_CONSTEXPR20 auto length(const Vec& v) noexcept {
        T len = T(0);
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            len += v[i] * v[i];
        }
        return std::sqrt(len);
    }
    template<typename Vec>
    IX_NODISCARD IX_CONSTEXPR20 auto distance(const Vec& a, const Vec& b) noexcept {
        Vec diff;
        for (size_t i = 0; i < Vec::dimension; ++i)
        {
            diff[i] = a[i] - b[i];
        }
        return length(diff);
    }

    template<typename T = float>
    IX_NODISCARD inline vector3<T> fromXMVECTOR(const DirectX::XMVECTOR& v) noexcept {
        DirectX::XMFLOAT3 f3;
        DirectX::XMStoreFloat3(&f3, v);
        return vector3<T>(f3.x, f3.y, f3.z);
    }
    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> cross(const vector3<T>& a, const vector3<T>& b) noexcept {
        vector3<T> result;
        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;
        return result;
    }
    template<typename Vec>
    IX_NODISCARD IX_CONSTEXPR17 Vec zero() noexcept { Vec result; result.zero(); return result; }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> forward() noexcept { return vector3<T>(0, 0, -1); }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> backward() noexcept { return vector3<T>(0, 0, 1); }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> up() noexcept { return vector3<T>(0, 1, 0); }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> down() noexcept { return vector3<T>(0, -1, 0); }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> right() noexcept { return vector3<T>(1, 0, 0); }

    template<typename T = float>
    IX_NODISCARD IX_CONSTEXPR17 vector3<T> left() noexcept { return vector3<T>(-1, 0, 0); }

    class matrix {
        DirectX::XMMATRIX m_Matrix;

        explicit matrix(const DirectX::XMMATRIX& mat) : m_Matrix(mat) {}

    public:
        matrix() : m_Matrix(DirectX::XMMatrixIdentity()) {}

        static matrix Identity() {
            return matrix(DirectX::XMMatrixIdentity());
        }

        static matrix Translation(const vector3<float>& t) {
            return matrix(DirectX::XMMatrixTranslation(t.x, t.y, t.z));
        }

        static matrix Scaling(const vector3<float>& s) {
            return matrix(DirectX::XMMatrixScaling(s.x, s.y, s.z));
        }

        static matrix Rotation(const vector3<float>& r) {
            return matrix(DirectX::XMMatrixRotationRollPitchYaw(r.x, r.y, r.z));
        }

        static matrix RotationX(float angle) {
            return matrix(DirectX::XMMatrixRotationX(angle));
        }

        static matrix RotationY(float angle) {
            return matrix(DirectX::XMMatrixRotationY(angle));
        }

        static matrix RotationZ(float angle) {
            return matrix(DirectX::XMMatrixRotationZ(angle));
        }

        static matrix LookAtLH(const vector3<float>& eye, const vector3<float>& target, const vector3<float>& up) {
            return matrix(DirectX::XMMatrixLookAtLH(eye.toXMVECTOR(), target.toXMVECTOR(), up.toXMVECTOR()));
        }

        static matrix PerspectiveFovLH(float fovY, float aspect, float nearZ, float farZ) {
            return matrix(DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ));
        }

        static matrix OrthographicLH(float width, float height, float nearZ, float farZ) {
            return matrix(DirectX::XMMatrixOrthographicLH(width, height, nearZ, farZ));
        }

        static matrix OrthographicOffCenterLH(float left, float right, float bottom, float top, float nearZ, float farZ) {
            return matrix(DirectX::XMMatrixOrthographicOffCenterLH(left, right, bottom, top, nearZ, farZ));
        }

        matrix Transposed() const {
            return matrix(DirectX::XMMatrixTranspose(m_Matrix));
        }

        matrix Inverse() const {
            return matrix(DirectX::XMMatrixInverse(nullptr, m_Matrix));
        }

        vector3<float> TransformPoint(const vector3<float>& v) const {
            DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(v.toXMVECTOR(), m_Matrix);
            return math::fromXMVECTOR(result);
        }

        vector3<float> TransformVector(const vector3<float>& v) const {
            DirectX::XMVECTOR result = DirectX::XMVector3TransformNormal(v.toXMVECTOR(), m_Matrix);
            return math::fromXMVECTOR(result);
        }

        matrix operator*(const matrix& rhs) const {
            return matrix(DirectX::XMMatrixMultiply(m_Matrix, rhs.m_Matrix));
        }

        matrix& operator*=(const matrix& rhs) {
            m_Matrix = DirectX::XMMatrixMultiply(m_Matrix, rhs.m_Matrix);
            return *this;
        }

        bool operator==(const matrix& rhs) const {
            for (int i = 0; i < 4; ++i)
            {
                DirectX::XMVECTOR rowA = m_Matrix.r[i];
                DirectX::XMVECTOR rowB = rhs.m_Matrix.r[i];
                if (!DirectX::XMVector4NearEqual(rowA, rowB, DirectX::XMVectorReplicate(1e-5f)))
                    return false;
            }
            return true;
        }

        bool operator!=(const matrix& rhs) const {
            return !(*this == rhs);
        }

        static matrix FromXMMATRIX(const DirectX::XMMATRIX& xm) {
            return matrix(xm);
        }

        DirectX::XMMATRIX ToXMMATRIX() const {
            return m_Matrix;
        }

        void ToFloat4x4(float out[4][4]) const {
            DirectX::XMFLOAT4X4 tmp;
            DirectX::XMStoreFloat4x4(&tmp, m_Matrix);
            std::memcpy(out, &tmp, sizeof(float) * 16);
        }
    };

    template<typename Vec, typename T = typename Vec::value_type>
    class transform {
        static_assert((Vec::dimension == 2 || Vec::dimension == 3) &&
            std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
            "vector<T, N>: N must be 2 or 3, T must be numeric (int, float, double), bool not allowed");

    public:
        using rotation_type = std::conditional_t<(Vec::dimension >= 3), Vec, T>;

    public:
        Vec position;
        Vec scale;
        rotation_type rotation;

        IX_CONSTEXPR14 transform() noexcept : position{}, scale{}, rotation{} {}
        IX_CONSTEXPR14 transform(const Vec& pos, const Vec& sca, const rotation_type& rot) noexcept : position(pos), scale(sca), rotation(rot) {}
        IX_CONSTEXPR14 transform(const transform& t) noexcept = default;

        IX_CONSTEXPR17 void zero() noexcept { position = {}; scale = {}; rotation = {}; }

        matrix toMatrix() const {
            matrix S = matrix::Scaling(scale);
            matrix R = matrix::Rotation(rotation);
            matrix T = matrix::Translation(position);
            return S * R * T;
        }
    };

    using vector2f = vector2<float>;
    using vector3f = vector3<float>;
    using vector4f = vector4<float>;
} // namespace math
