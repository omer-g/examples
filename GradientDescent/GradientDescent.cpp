// omer-g@github

/* GRADIENT DESCENT ALGORITHM */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "GradientDescent.hpp"

void point_to_vars(const Point &p, double &x, double &y, double &z){
    x = std::get<0>(p);
    y = std::get<1>(p);
    z = std::get<2>(p);
}

std::ostream& operator<<(std::ostream& stream, const Point &p){
    stream << "(" << std::get<0>(p) << ", " <<
        std::get<1>(p) << ", " <<
        std::get<2>(p) << ")";
    return stream;
}

Point operator+(const Point& a, const Point& b){
    double ax, ay, az, bx, by, bz;
    point_to_vars(a, ax, ay, az);
    point_to_vars(b, bx, by, bz); 
    return std::make_tuple(ax + bx, ay + by, az + bz);
}

Point operator*(const double &c, const Point& p){
    double x, y, z;
    point_to_vars(p, x, y, z);
    return std::make_tuple(x * c, y * c, z * c);
}

Point step_descent(const Point &p, Point(&gradient)(const Point&), double step){
    Point delta = step * gradient(p);
    return p + delta;
}

Point gradient_descent(const Point &p, double(&function)(const Point&), Point(&gradient)(const Point&),
                        double step, int iterations){
    Point curr_p = p;
    for (int i = 0; i < iterations; i++){
        curr_p = step_descent(curr_p, gradient, step);
    }
    std::cout <<
        "step: "        << std::setw(7)     << step << 
        " iterations: " << std::setw(5)     << iterations << 
        " minimum: "    << std::setw(15)    << function(curr_p) << 
        " point: "      << std::setw(10)    << curr_p <<
        std::endl;
    return curr_p;
}


// USE EXAMPLE:

// f(x, y, z) = x^2 + y^2 + z^2
double f(const Point &p){
    double x, y, z;
    point_to_vars(p, x, y, z);
    return pow(x,2) + pow(y,2) + pow(z,2);
}

// df(x, y, z) = (2x, 2y, 2z)
Point df(const Point &p){
    double x, y, z;
    point_to_vars(p, x, y, z);
    return std::make_tuple(2*x, 2*y, 2*z);
}

int main(){
    Point p(1,2,1);
    std::cout << "f(" << p << ") = " << f(p) << std::endl;

    Point m1 = gradient_descent(p, f, df, -1, 50);
    Point m2 = gradient_descent(p, f, df, -0.1, 50);
    Point m3 = gradient_descent(p, f, df, -0.01, 50);
    Point m4 = gradient_descent(p, f, df, -0.0001, 50);
    
    std::cout << "lowest minimum: " << std::min<double>({f(m1), f(m2), f(m3), f(m4)}) << std::endl;
    
    return 0;
}
