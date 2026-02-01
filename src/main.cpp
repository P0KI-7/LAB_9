#include "GroupStats.h"

// лямбда-функции
auto intKeyFunc = [] (int x) { return x%10; };
auto intValueFunc = [] (int x) { return x; };

auto doubleKeyFunc = [] (double x) {
    if (x < 0) return 0;
    if (0 <= x && x <= 10) return 1;
    return 2;
};
auto doubleValueFunc = [] (double x) { return x; };

auto stringKeyFunc = [] (const std::string& x) { return x[0]; };
auto stringValueFunc = [] (const std::string& x) { return x.length(); };

// функтор с параметром вместо intKeyFunc, в котором можно выбирать,
// по каком разрзяду сортировать
// функтор отличается от обычного объяекта перегрузкой скобочек
class reIntKeyFunc {
    int rank = 1;
public:
    reIntKeyFunc(): rank(1) {}
    reIntKeyFunc(int rank): rank(rank) {}
    int operator()(int x) const { 
        for (int i = 1; i < rank; ++i) x /= 10;
        return x % 10;
    };
};

// мой новый объект (бренды связанные с фруктами), включающие имя фрукта и год основания бренда
// важно перегрузить "<" и ">" которые используется в шаблонной функции
// также надо перегрузить выввод для нашего объекта
struct Fruict_brands{
    std::string name;
    int yoo; // year of opening (год открытия)

    Fruict_brands(): name(""), yoo(0) {}
    Fruict_brands(std::string name, int yoo): name(name), yoo(yoo) {}

    bool operator<(const Fruict_brands& other) const {
        return yoo < other.yoo;
    }
    bool operator>(const Fruict_brands& other) const {
        return yoo > other.yoo;
    }

};

std::ostream& operator<<(std::ostream& o, const Fruict_brands& f) {
    return o << f.name << ". Year of opening: " << std::setw(4) << f.yoo << ".";
}

// специальные лябда функции для передачи в шаблонную функцию
auto fruictKeyFunc = [] (const Fruict_brands& x) { return x.name[0]; };
auto fruictValueFunc = [] (const Fruict_brands& x) { return x.yoo; };


int main()
{
    std::cout << "=== Demonstration of groupStats ===\n\n";
 
    // работа с нашим новым объектом
    std::cout << "\n-1. Array of Fruict_brends \n" << std::endl;
    Fruict_brands fruicts[] = {{"apple", 1976}, {"banana", 327}, {"apricot", 2007}, {"cherry", 1997}, {"blueberry", 1997}, 
                    {"avocado", 750}, {"berry", 1939}, {"coconut", 1954}, {"date", 1996}, {"fig", 2012}};
    size_t fruitsSize = sizeof(fruicts) / sizeof(fruicts[0]);    
    auto fruitsGroups = groupStats(fruicts, fruitsSize, fruictKeyFunc, fruictValueFunc);
    for (const auto& group : fruitsGroups) {
        printGroupInfo(group);
    }

    std::cout << "1. Array of int\n" << std::endl;
    int intArr[] = {12, 23, 34, 45, 56, 67, 78, 89, 91, 102, 113, 124, 15, 26, 37};
    size_t intSize = sizeof(intArr) / sizeof(intArr[0]);
    reIntKeyFunc func = 2; // func вместо intKeyFunc
    auto intGroups = groupStats(intArr, intSize, func, intValueFunc);
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