# exors

Welcome to EXORS, the C++ library that's so over-engineered, it's practically a work of art.

- [Features](#features)
- [Usage](#usage)
- [Why EXORS?](#why-exors)
- [Installation](#installation)
- [License](#license)

## Features

- **i dont know**: very useful

## Usage

### Expression Template

`expression_t` template is the backbone of this library. It's so versatile, it can handle anything from simple addition to complex nested expressions. Just don't ask it to do anything useful.

### Calculator Function

Our `calculator` function is the epitome of recursion. It can handle addition, subtraction, multiplication, and division. Just don't ask it to do anything else.

```cpp
#include "exors.hpp"
#include <iostream>

int main() {
    const exors::expression number1("2000.0");
    const exors::expression number2("1500.0");
    const exors::expression sum1("+", {number1, number2});
    const exors::expression dif2("-", {number1, number2});
    const exors::expression result("*", {sum1, dif2});
    std::cout << exors::calculator(result).name;

    return 0;
}
```

## Why EXORS?

- **Over-Engineered**: Why write simple code when you can write complex code?

## Installation

Just include `exors.hpp` in your project.

## License

This library is licensed under the [MIT license](LICENSE).
