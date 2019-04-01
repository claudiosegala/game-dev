#define UNUSED(x) (void)x

#define PI (float) 3.141592653589793

#include <algorithm>

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