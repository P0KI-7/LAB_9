#include "GroupStats.h"

// лямбда-функции
auto intKeyFunc = [] (int x) { return x%10; };
auto intValueFunc = [] (int x) { return x; };

auto doubleKeyFunc = [] (double x) {
    if (x < 0) return 0;
    if (0 <= x && x <= 10) return 1;
    if (x > 10) return 2;
};
auto doubleValueFunc = [] (double x) { return x; };

auto stringKeyFunc = [] (const std::string& x) { return x[0]; };
auto stringValueFunc = [] (const std::string& x) { return x.length(); };




int main()
{
    std::cout << "=== Demonstration of groupStats ===\n\n";
    
    std::cout << "1. Array of int\n" << std::endl;
    int intArr[] = {12, 23, 34, 45, 56, 67, 78, 89, 91, 102, 113, 124, 15, 26, 37};
    size_t intSize = sizeof(intArr) / sizeof(intArr[0]);
    auto intGroups = groupStats(intArr, intSize, intKeyFunc, intValueFunc);
    //    [](int x) { return x % 10; } вместо keyfunc и valuefunc
    //    [](int x) { return x; }      
    for (const auto& group : intGroups) {
        printGroupInfo(group);
    }
    
    std::cout << "\n2. Array of double)\n" << std::endl;   
    double doubleArr[] = {-5.5, 3.14, 7.8, 15.2, 0.0, -2.1, 9.9, 20.1, 10.5, -1.0, 5.0};
    size_t doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]); 
    auto doubleGroups = groupStats(doubleArr, doubleSize, doubleKeyFunc, doubleValueFunc);
    for (const auto& group : doubleGroups) {
        printGroupInfo(group);
    }
    
    std::cout << "\n3. Array of std::string \n" << std::endl;
    std::string strArr[] = {"apple", "banana", "apricot", "cherry", "blueberry", 
                           "avocado", "berry", "coconut", "date", "fig"};
    size_t strSize = sizeof(strArr) / sizeof(strArr[0]);    
    auto strGroups = groupStats(strArr, strSize, stringKeyFunc, stringValueFunc);
    for (const auto& group : strGroups) {
        printGroupInfo(group);
    }
    
    // Дополнительный пример
    std::cout << "\n4. Additional example (int by parity)\n" << std::endl;    
    auto evenOddGroups = groupStats(intArr, intSize,
        [](int x) -> std::string {  // ключ: строка "even" или "odd"
            return (x % 2 == 0) ? "even" : "odd";
        },
        [](int x) { return x; }  // значение: само число
    );
    for (const auto& group : evenOddGroups) {
        printGroupInfo(group);
    }

    return 0;
}