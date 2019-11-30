#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP


/* GRADIENT DESCENT ALGORITHM */


#include <tuple>

typedef std::tuple<double, double, double> Point;

// Positive step value for ascent
Point gradient_descent(const Point &p,
                        double(&function)(const Point&),
                        Point(&gradient)(const Point&),
                        double step,
                        int iterations);

Point step_descent(const Point &p, Point(&gradient)(const Point&), double step);


#endif /* GRADIENTDESCENT_HPP */
