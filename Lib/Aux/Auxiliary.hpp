#include <list>

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
