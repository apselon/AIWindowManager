#pragma once

#include <list>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

template <typename T>
struct Vector2 {
    T x = {};
    T y = {};

    Vector2() = default;
    Vector2(T x, T y): x(x), y(y) {};

};

using Vector2d = Vector2<double>;
using Vector2sz = Vector2<unsigned long>;

using std::list;
using std::queue;
