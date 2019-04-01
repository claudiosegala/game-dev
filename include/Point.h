#pragma once

// TODO: check corretude
// TODO: check if I should add const operators

namespace penguin {

    class Point {
        public:

        float x;

        float y;

        Point();

        Point(float, float);

        float Length() const;

        float Distance(const Point&) const;

        static float Distance(const Point&, const Point&);

        void Rotate(float);

        void Rotate(float, const Point&);

        void Normalize();

        Point operator+= (const Point&);

        Point operator+ (const Point&);

        Point operator-= (const Point&);

        Point operator- (const Point&);

        Point operator* (int);

        Point operator* (float);

        Point operator/ (int);

        Point operator/ (float);

        Point operator= (const Point&);

        bool operator==(const Point&);

        bool operator<(const Point&);

        private:

        bool Equal(float, float) const;
    };

}