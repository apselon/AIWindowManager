#pragma once

#include <list>
#include <queue>
#include <vector>
#include <cmath>

constexpr double EPS = 0.1;

#pragma GCC diagnostic ignored "-Weffc++"
template <typename T>
struct Vector2 {
    T x = {};
    T y = {};

    Vector2() = default;
    Vector2(T x, T y): x(x), y(y) {};

    bool operator ||(const Vector2& another) const {
        return fabs(x * another.y - another.x * y) <= EPS;    
    }

    Vector2 operator -(const Vector2& another) const {
        return {x - another.x, y - another.y};
    }

    Vector2 operator +(const Vector2& another) const {
        return {x + another.x, y + another.y};
    }

    const Vector2& operator +=(const Vector2& another) {
        x += another.x;
        y += another.y;

        return *this;
    }

    T operator ^(const Vector2& another) const {
        return x * another.x +  y * another.y;
    }

    Vector2 operator *(const Vector2& another) const {
        return {x * another.x, y * another.y};
    }

    Vector2 operator *(const T& mul) const {
        return {x * mul, y * mul};
    }
};
#pragma GCC diagnostic pop

using Vector2d = Vector2<int64_t>;

using std::list;
using std::queue;
using std::vector;
