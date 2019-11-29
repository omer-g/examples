// omer-g@github

/*
    VECTOR OPTIMIZATION IN C++14

    emplace_back() with rvalue (xvalue in C++17) stil calls copy constructor.
    A move constructor allows to point directly to the object and avoid copies.

    reserve(num) reduces need to resize and copy elements when an element is added.
*/

#include <iostream>
#include <vector>

struct Point {
    float x, y;
    Point(float x, float y): x(x), y(y) {}

    Point(const Point& other): x(other.x), y(other.y) {
        std::cout << "Copied" << std::endl;
    }

    // (2) THEN UNCOMMENT THIS TO OPTIMIZE FURTHER:
    // Point(const Point&& other) {}          // Move constructor   
};

int main(){
    std::cout << "C++ version: " << __cplusplus << std::endl;
    
    std::vector<Point> v;

    // (1) FIRST UNCOMMENT THIS TO OPTIMIZE:
    // v.reserve(3);

    // Without optimization there are 6 calls to copy constructor
    // With optimization there are no calls
    v.emplace_back(Point(1,2));
    v.emplace_back(Point(3,4));
    v.emplace_back(Point(5,6));

    return 0;
}