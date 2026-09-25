# Chapter 1: Input, Output, and Numbers

## 1. A small C++ program

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b << '\n';
    return 0;
}
```

Input `3 5` prints `8`.

- `<iostream>` provides `cin` and `cout`.
- `using namespace std;` lets us write `cout` instead of `std::cout`.
- Execution starts in `main()`. Braces `{}` group its code.
- End statements with `;`. Use `//` for comments.
- `return 0;` means success; it can be omitted at the end of `main()`.

## 2. Variables and input/output

Declare a variable before using it, and give it a value before calculating with it.

```cpp
int count = 10;       // Integer
float height = 2.5;  // Number with a decimal part
count = 12;          // Change the stored value
```

`cin >> a >> b;` reads values in order, separated by spaces or new lines.
`cout << a << " " << b;` prints two values with a space between them.
Both `endl` and `'\n'` start a new line; `endl` also forces pending output to be sent.

### Text with `string`

Use `string` to store text, and include the `<string>` header.

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
}
```

Input `Harry` prints `Hello, Harry!`. `cin >> name` reads one word.
Text inside double quotes is printed literally. Add spaces and punctuation inside the quotes when needed.

## 3. Arithmetic

| Operator | Meaning | Example | Result |
|---|---|---|---|
| `+` | Add | `10 + 3` | `13` |
| `-` | Subtract | `10 - 3` | `7` |
| `*` | Multiply | `10 * 3` | `30` |
| `/` | Divide | `10 / 3` | `3` |
| `%` | Integer remainder | `10 % 3` | `1` |

When both operands are integers, `/` drops the decimal part; it does not round.
Use `%` with integers. Never divide or take a remainder by zero.

### Decimal division

```cpp
cout << 5 / 2 << '\n';    // 2: integer division
cout << 5 / 2.0 << '\n';  // 2.5: floating-point division
float x = 5.0;
cout << x / 2 << '\n';    // 2.5
```

If at least one operand is a floating-point value, division keeps the decimal part.
Storing `5 / 2` in a `float` afterward cannot recover the lost fraction.

## 4. Updating values

```cpp
int x = 5;
x = x + 3;  // x becomes 8
x += 2;     // x becomes 10
x++;        // x becomes 11
x--;        // x becomes 10
```

`=` stores a value; `==` compares values. Other update shortcuts include `-=`, `*=`, `/=`, and `%=`.

## 5. Calculation order

Parentheses first, then `* / %`, then `+ -`. Within each of these arithmetic groups, calculate left to right.
`2 + 3 * 4` is `14`; `(2 + 3) * 4` is `20`.
