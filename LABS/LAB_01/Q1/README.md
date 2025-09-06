# Function Growth Comparison

This C program compares the growth of multiple mathematical functions over a given range of `n`.  
It calculates the **average value** of each function across the range, and then ranks them in **increasing order**.

---

## 📌 Features
- Implements **12 mathematical functions** such as `1/n`, `log2(n)`, `sqrt(n)`, `n^2`, `n log n`, `3^n`, etc.
- Accepts **user input** for:
  - Start value of `n`
  - End value of `n`
  - Step size
- Computes the **average value** of each function over the input range.
- Displays:
  - The **average value per function**
  - The **ranking in increasing order** (e.g., `f1 < f2 < f3 < ...`)

---

## 📂 Functions Implemented

The program evaluates the following functions:

| Function ID | Formula              |
|-------------|----------------------|
| f1          | 1 / n                |
| f2          | log2(n)              |
| f3          | 12 * √n              |
| f4          | 50 * √n              |
| f5          | n^0.51               |
| f6          | n * log2(n)          |
| f7          | n² - 324             |
| f8          | 100n² + 6n           |
| f9          | 2n³                  |
| f10         | n^(log2(n))          |
| f11         | 3^n                  |
| f12         | n * 2^32             |

---

## 🧑‍💻 Usage

### 🔧 Compile

```bash
Q1.exe
```

### ✅ Example Run

**Input:**

Enter start value of n: 2

Enter end value of n: 200

Enter step size: 2

**Output:**

Sum of each function over given n range:

f1(1/n)               Sum Avg = 2.593689e-002

f2(log2(n))           Sum Avg = 6.247650e+000

f3(12*sqrt(n))        Sum Avg = 1.139510e+002

f4(50*sqrt(n))        Sum Avg = 4.747960e+002

f5(n^0.51)            Sum Avg = 9.946968e+000

f6(n*log2(n))         Sum Avg = 6.999130e+002

f7(n^2-324)           Sum Avg = 1.321000e+004

f8(100n^2+6n)         Sum Avg = 1.354006e+006

f9(2n^3)              Sum Avg = 4.080400e+006

f10(n^(log2(n)))      Sum Avg = 2.607373e+016

f11(3^n)              Sum Avg = 2.988157e+093

f12(n*2^32)           Sum Avg = 4.337917e+011

Ranking of averages (in increasing order):

f1(1/n) < f2(log2(n)) < f5(n^0.51) < f3(12*sqrt(n)) < f4(50*sqrt(n)) < f6(n*log2(n)) < f7(n^2-324) < f8(100n^2+6n) < f9(2n^3) < f12(n*2^32) < f10(n^(log2(n))) < f11(3^n)

