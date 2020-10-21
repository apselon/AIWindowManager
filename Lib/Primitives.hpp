namespace Primitives {

class Rect {
private:
    double pos_x = 0;
    double pos_y = 0;

    double width  = 0;
    double height = 0;

public:
    Rect() = default;
    Rect(double pos_x, double pos_y, double width, double height);
    bool contains(double x, double y);
    void draw();
};

class Label {
    
};

};
