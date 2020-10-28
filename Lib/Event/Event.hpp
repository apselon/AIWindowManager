template <typename T>
struct Pair {
    T x = 0;
    T y = 0;

    Pair() = default;
    Pair(const T& x, const T& y): x(x), y(y) {};
};

union Event {
    Pair<double> mouse_pos = Pair<double>();
};
