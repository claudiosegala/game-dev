#include <iostream>
#include <cmath>

/////////////
// DEBUG
/////////////

#define W(x) std::cerr << "\033[31m" << #x << "=" << x << "\033[0m" << "\n";

/////////////
// UTIL
/////////////

#define UNUSED(x) (void)x
#define EQUAL(x, y) fabs(x - y) < EPS

/////////////
// MATH
/////////////

#define PI (float) 3.141592653589793
#define TAO (float) 2.0 * PI
#define EPS 0.00001

/////////////
// COLOR
/////////////

#define RED            "\x1b[31m"
#define GREEN          "\x1b[32m"
#define YELLOW         "\x1b[33m"
#define BLUE           "\x1b[34m"
#define MAGENTA        "\x1b[35m"
#define CYAN           "\x1b[36m"
#define RESET          "\x1b[0m"