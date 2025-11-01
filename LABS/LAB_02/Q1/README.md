# 🧮 Q1 – Strassen Matrix Multiplication (ADSA Lab 02)

## 📘 Problem Statement

This project implements the **Strassen Matrix Multiplication Algorithm** in C.  
It multiplies two square matrices efficiently using **divide and conquer** — reducing the number of multiplications from 8 (in traditional matrix multiplication) to **7**, resulting in faster execution for large matrices.

The implementation is verified using the **MUnit testing framework** to ensure correctness across multiple test cases.

---

## ⚙️ Algorithm Overview

**Strassen’s Algorithm** recursively divides the matrices into submatrices and computes the product using 7 multiplications and several additions/subtractions.

For two matrices `A` and `B`, each divided into four submatrices:

```bash
A = |A11 A12|     B = |B11 B12|
    |A21 A22|         |B21 B22|
```

We compute the following seven intermediate matrices:

```bash
M1 = (A11 + A22) * (B11 + B22)
M2 = (A21 + A22) * B11
M3 = A11 * (B12 - B22)
M4 = A22 * (B21 - B11)
M5 = (A11 + A12) * B22
M6 = (A21 - A11) * (B11 + B12)
M7 = (A12 - A22) * (B21 + B22)
```

Then, the result matrix `C` is obtained as:

```bash
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

---

## 🧑‍💻 Code Overview

- Implements the Strassen matrix multiplication algorithm **without using `malloc`** (using static 2D arrays).
- Handles matrices of any size by padding them to the **next power of 2**.
- Includes helper functions:
  - `add()` – adds two matrices.
  - `subtract()` – subtracts one matrix from another.
  - `printMatrix()` – displays a matrix.
  - `nextPowerOf2()` – finds the next power of 2 for padding.
- A simple interactive `main()` function allows the user to input matrices and view the result.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q1_Strassen.c -o Q1_Strassen
./Q1_Strassen
```

---

### 📥 Input Example

```bash
Enter size of square matrices: 2
Enter elements of Matrix A:
1 2
3 4
Enter elements of Matrix B:
5 6
7 8
```

---

### 📤 Output Example

```bash
Resultant Matrix (A x B):
19 22
43 50
```

---

## 🧩 MUnit Test Code Overview

- Includes **MUnit test cases** to automatically verify correctness.
- The macro `#define TEST_MODE` disables the main function in `Q1_Strassen.c` during testing.
- Tests include:
  1. ✅ **2×2 Matrix Multiplication**
  2. ✅ **3×3 Matrix (Padding check)**
  3. ✅ **1×1 Single Element Matrix**
  4. ✅ **Zero Matrix**
  5. ✅ **Identity Matrix**

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q1_Strassen.c munit.c -o test_Q1_Strassen
./test_Q1_Strassen
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/strassen-tests/2x2          [OK]
/strassen-tests/3x3          [OK]
/strassen-tests/single       [OK]
/strassen-tests/zero         [OK]
/strassen-tests/identity     [OK]
5 of 5 (100%) tests successful.
```
