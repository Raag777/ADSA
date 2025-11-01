# Q1 – Function Growth Order (ADSA Lab 01)

## 📘 Problem Statement

Using implementation, place the given functions in a list by **increasing order of growth**. That means, in the final list, if function *f* comes before function *g*, then **f ∈ O(g)**. In case **f ∈ Θ(g)**, either one can come first. Also, explicitly state which pairs of functions belong to the same Θ-class.

---

## 🧮 Given Functions

| No | Function |
|----|-----------|
| f1 | n log₂n |
| f2 | 12√n |
| f3 | 1/n |
| f4 | n^(log₂n) |
| f5 | 100n² + 6n |
| f6 | n^0.51 |
| f7 | n² − 324 |
| f8 | 50√n |
| f9 | 2n³ |
| f10 | log₂n |
| f11 | 3ⁿ |
| f12 | 2³²n |

---

## 📂 Files in This Folder

| File Name | Description |
|------------|-------------|
| **growth_order.c** | Implements all 12 given functions and calculates their increasing order of growth. It also displays Θ-equivalent function pairs and prints the full chain of function growths. |
| **test_growth_order.c** | Contains automated unit tests using the [MUnit](https://nemequ.github.io/munit/) framework to validate correctness of the implementation in `growth_order.c`. |
| **munit.c / munit.h** | The MUnit testing framework files. |

---

## 🧠 Overview

### ⚙️ Features:

- Defines all 12 mathematical functions.
- Evaluates their values for a given large `n` (e.g., `n = 1000`).
- Sorts the functions based on their evaluated values to determine order of growth.
- Displays:
  - Ordered list of functions.
  - Θ-equivalent function pairs.
  - Full chain of increasing growth order.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc growth_order.c -o growth_order -lm
./growth_order  
```

---

### 🖥️ Example Output

```bash
Function growth order (for n = 1000):
 1. 1/n           = 1.00e-03
 2. log₂n         = 9.97e+00
 3. n^0.51        = 1.09e+02
 4. 12√n          = 3.79e+02
 5. 50√n          = 1.58e+03
 6. n log₂n       = 9.97e+03
 7. n² - 324      = 9.97e+05
 8. 100n² + 6n    = 1.00e+08
 9. 2n³           = 2.00e+09
10. 2³²n          = 4.29e+12
11. n^(log n)     = 1.00e+30
12. 3ⁿ            = 1.37e+477

Possible Θ-equivalent pairs:
 - (12√n, 50√n)  => Θ(√n)
 - (100n² + 6n, n² - 324)  => Θ(n²)

Chain form of increasing growth order:
1/n  <  log₂n  <  n^0.51  <  12√n  <  50√n  <  n log₂n  <  n²−324  <  100n²+6n  <  2n³  <  2³²n  <  n^(log n)  <  3ⁿ
```

---

## 🧩 MUnit Test Code Overview

This test file verifies the correctness of `growth_order.c` using the MUnit testing framework.

### ⚙️ Tests Implemented:

It includes three main test suites:

1. Monotonic Growth Test

- Verifies that all functions with increasing complexity 
  (e.g., log n, n^0.51, n log n, n², etc.) grow with `n`.
- Ensures the function 1/n decreases as `n` increases.

Test name: /function-growth-tests/growth

2. Θ-Equivalence Test

- Validates that the following function pairs belong to 
  the same Θ-class:

    (12√n, 50√n)        => Θ(√n)
    (100n² + 6n, n²−324) => Θ(n²)

Test name: /function-growth-tests/theta


3. Chain Order Test

- Verifies that all 12 functions are sorted correctly 
  by increasing order of growth.
- Confirms the order:
  1/n < log₂n < n^0.51 < √n < n log n < n² < n³ < 2³²n < n^(log n) < 3ⁿ

Test name: /function-growth-tests/chain

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_growth_order.c munit.c -o test_growth_order -lm
./test_growth_order
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/function-growth-tests/growth        [ OK    ]
/function-growth-tests/theta         [ OK    ]
/function-growth-tests/chain         [ OK    ]
3 of 3 (100%) tests successful, 0 (0%) test skipped.
```
