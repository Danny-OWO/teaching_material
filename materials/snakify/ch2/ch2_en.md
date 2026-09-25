# Chapter 2: Integers and Floating-Point Numbers

In this chapter, we will take a closer look at numbers. Unlike Python, C++ does not automatically decide the type of a variable while the program is running. We must choose `int`, `long long`, `float`, or `double` ourselves. This may seem less convenient, but it also gives us a clearer understanding of how data is stored and calculated.

## 1. Integer Arithmetic

Integers are usually stored using `int`. When a value may be very large, we can use `long long`, which has a larger range.

```cpp
int a = 17;
long long population = 8000000000LL;
```

We can use `+`, `-`, `*`, `/`, and `%` with integers:

```cpp
cout << 17 / 3 << '\n';  // 5: quotient
cout << 17 % 3 << '\n';  // 2: remainder
```

In C++, dividing one integer by another produces an integer, and the fractional part is discarded. This is different from Python's `/`: in Python, `17 / 3` produces a floating-point number, while `17 // 3` is used for integer division. C++ does not have a `//` operator because `//` marks the beginning of a comment.

> Look at the types of the operands, not the type of the variable receiving the answer. `double x = 17 / 3;` still gives `5.0` because the integer division on the right has already been performed.

To keep the fractional part, make at least one operand a floating-point number:

```cpp
double x = 17.0 / 3;              // 5.66666...
double y = static_cast<double>(17) / 3;
```

### Splitting Digits with `/` and `%`

For a non-negative integer, `n % 10` gives its ones digit, while `n / 10` removes its ones digit.

```cpp
int n = 472;
int ones = n % 10;          // 2
int tens = n / 10 % 10;     // 7
int hundreds = n / 100;     // 4
```

Similarly, `n % 100` gives the last two digits, while `n / 100` removes the last two digits. We will use this technique in this chapter's digit-reversal, clock, and money problems.

C++ integers have a fixed range. Unlike Python integers, they do not automatically grow when that range is exceeded. If a calculation may produce a value greater than approximately two billion, we should usually use `long long`. If the result of multiplication may be large, one of the operands should also be converted to `long long` before multiplication.

```cpp
long long product = 1LL * a * b;
```

## 2. Floating-Point Numbers

Both `float` and `double` can store numbers with a fractional part, but we usually prefer `double` because it has greater precision.

```cpp
double x;
cin >> x;
cout << x << '\n';
```

This allows us to store a floating-point number.

## 3. The `<cmath>` Math Library

Python uses `import math`; in C++, we include `<cmath>` at the beginning of the program:

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x = 4.2;
    cout << ceil(x) << '\n';       // 5
    cout << ceil(1 + 3.8) << '\n'; // 5
}
```

`ceil(x)` gives the smallest integer value greater than or equal to `x`, while `floor(x)` gives the largest integer value less than or equal to `x`.

If we do not write `using namespace std;`, we must add `std::` before the function name:

```cpp
double answer = std::sqrt(25.0);
```

This is equivalent to Python's `math.sqrt(25.0)`. C++ does not have syntax like Python's `from math import ceil`. We normally write `std::ceil`, or use `using std::ceil;` within a small scope.

| Category | C++ Syntax | Description |
|---|---|---|
| Rounding | `floor(x)` | Rounds down: the largest integer value not greater than `x` |
| Rounding | `ceil(x)` | Rounds up: the smallest integer value not less than `x` |
| Rounding | `round(x)` | Rounds to the nearest integer; halfway values are rounded away from zero |
| Absolute value | `abs(x)` | The absolute value of `x` |
| Powers | `pow(x, y)` | Calculates x raised to the power of y |
| Square roots | `sqrt(x)` | Calculates the square root |
| Logarithms | `log(x)` | The natural logarithm with base e |
| Logarithms | `log10(x)` | The logarithm with base 10 |
| Trigonometry | `sin(x)` | The sine of `x` radians |
| Inverse trigonometry | `asin(x)` | The inverse sine, returned in radians |
| Exponents | `exp(x)` | Calculates e raised to the power of x |

Python allows us to write `x ** y`, but C++ does not have a `**` operator, so we must use `pow(x, y)`. If we only need the square of an integer, `x * x` is usually more direct and avoids unnecessarily using floating-point arithmetic.

Unlike Python's `math.log(x, base)`, C++'s `log` does not accept a second argument for the base. We can use the change-of-base formula to calculate a logarithm with any base `b`:

```cpp
double value = log(x) / log(b);
```

### π and e

When using C++20, we can include `<numbers>` and use the standard constants:

```cpp
#include <numbers>

double pi = std::numbers::pi;
double e = std::numbers::e;
```

In older environments, we can use `acos(-1.0)` to obtain π and `exp(1.0)` to obtain e. Although `M_PI` is common, it is not guaranteed to be available in every C++ compiler.

Trigonometric functions use radians, not degrees. We can convert degrees to radians as follows:

```cpp
double radians = degrees * acos(-1.0) / 180.0;
```
