#include <iostream>
#include <cmath>

#define W(x) std::cerr << "\033[31m" << #x << "=" << x << "\033[0m" << "\n";

#define PI (float) 3.141592653589793
#define TAO (float) 2.0 * PI
#define EPS 0.00001

#define UNUSED(x) (void)x
#define EQUAL(x, y) fabs(x - y) < EPS

// #include <algorithm>

// namespace range
// {

//     template<typename Range, typename Function>
//     Function for_each(Range& range, Function f) {
//         return std::for_each(begin(range), end(range), f);
//     }

//     template<typename Range, typename Function>
//     Function clear(Range& range, Function f) {
//         auto it = std::remove_if(begin(range), end(range), f);

//         return range.erase(it, end(range));
//     }

// }