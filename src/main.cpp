#include <stdio.h>
#include <string>

// лямба-функции
auto intKeyFunc = [] (int x) { return x; };
auto intValueFunc = [] (int x) { return x; };

auto dobleKeyFunc = [] (double x) {
    if (x < 0) return 0;
    if (0 <= x && x <= 10) return 1;
    if (x > 10) return 2;
};
auto doubleValueFunc = [] (double x) { return x; };

auto stringKeyFunc = [] (const std::string& x) { return x[0]; };
auto stringValueFunc = [] (const std::string& x) { return x.length(); };




int main()
{
    return 0;
}