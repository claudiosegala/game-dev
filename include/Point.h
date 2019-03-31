#pragma once

// TODO: check corretude
// TODO: check if I should add const operators

namespace penguin {

    class Point {
        public:

        double x;

        double y;

        Point();

        Point(double, double);

        double Length() const;

        double Distance(const Point&) const;

        static double Distance(const Point&, const Point&);

        void Rotate(double);

        void Rotate(double, const Point&);

        void Normalize();

        Point operator+= (const Point&);

        Point operator+ (const Point&);

        Point operator-= (const Point&);

        Point operator- (const Point&);

        Point operator* (int);

        Point operator* (double);

        Point operator/ (int);

        Point operator/ (double);

        Point operator= (const Point&);

        bool operator==(const Point&);

        bool operator<(const Point&);

        private:

        bool Equal(double, double) const;
    };

}