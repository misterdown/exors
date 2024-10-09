#include "exors.hpp"
#include <iostream>

int main() {
    const exors::expression number1("2000.0");
    const exors::expression number2("1500.0");
    const exors::expression sum1("+", {number1, number2});
    const exors::expression dif2("-", {number1, number2});
    const exors::expression sumS("*", {sum1, dif2});
    std::cout << exors::calculator(sumS).name;

    return 0;
}