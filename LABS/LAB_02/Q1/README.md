# 🧮 Q1 – Strassen Matrix Multiplication (ADSA Lab 02)

## 📘 Problem Statement

This project implements the **Strassen Matrix Multiplication Algorithm** in C.  
It multiplies two square matrices efficiently using **divide and conquer** — reducing the number of multiplications from 8 (in traditional matrix multiplication) to **7**, resulting in faster execution for large matrices.

The implementation is verified using the **MUnit testing framework** to ensure correctness across multiple test cases.

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q1_Strassen.c` | Contains the implementation of the **Strassen Matrix Multiplication** algorithm along with helper functions for matrix addition, subtraction, and display. |
| `test_Q1_Strassen.c` | Contains **MUnit** test cases that automatically verify the correctness of Strassen’s algorithm across multiple scenarios (2x2, 3x3, single element, zero matrix, and identity matrix). |
| `munit.c` / `munit.h` | The testing framework used for all unit tests (already included in the ADSA Lab setup). |

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

## 🛠️ Code Overview

- Implements the Strassen matrix multiplication algorithm **without using `malloc`** (using static 2D arrays).
- Handles matrices of any size by padding them to the **next power of 2**.
- Includes helper functions:
  - `add()` – adds two matrices.
  - `subtract()` – subtracts one matrix from another.
  - `printMatrix()` – displays a matrix.
  - `nextPowerOf2()` – finds the next power of 2 for padding.
- A simple interactive `main()` function allows the user to input matrices and view the result.

---

## 🧮 Algorithm Complexity (Strassen Matrix Multiplication)

### ⏱️ Time Complexity

| Operation                                        | Time Complexity |
|--------------------------------------------------|------------------|
| Splitting matrices into submatrices              | **O(n²)**        |
| Matrix additions & subtractions (18 total)       | **O(n²)**        |
| 7 recursive Strassen multiplications             | **7 · T(n/2)**   |
| Overall Strassen Algorithm Complexity            | **O(n^log₂7)** ≈ **O(n²․⁸¹)** |

📌 **Explanation:**  
- Strassen’s algorithm reduces the number of multiplications from **8 → 7**, causing the recurrence:

  T(n) = 7 * T(n/2) + O(n²)

- Using the Master theorem:

  log₂(7) ≈ 2.81

- Thus, the overall time complexity becomes:

  O(n^2.81)

- This is asymptotically faster than classical multiplication (**O(n³)**).

---

### 🗃️ Space Complexity

| Component                                         | Space Used |
|---------------------------------------------------|------------|
| Input matrices (A, B) and output matrix (C)       | **O(n²)**  |
| Temporary submatrices (A11, A12, …, B22)          | **O(n²)**  |
| Temporary matrices M1–M7                          | **O(n²)**  |
| Temporary buffers (temp1, temp2)                  | **O(n²)**  |
| Recursion stack depth (log₂n levels)              | **O(log n)** |
| **Overall Space Complexity**                      | **O(n²)**  |

**Explanation:**  
- Even though multiple submatrices exist, they are all bounded by a fixed `MAX x MAX` array size.
- Thus the auxiliary memory stays at **O(n²)**.
- The recursive depth adds only **O(log n)** extra stack usage.

---

### ✔ Summary

| Metric              | Complexity |
|---------------------|------------|
| **Time Complexity** | **O(n^2.81)** |
| **Space Complexity** | **O(n²)** |

This matches the expected complexity of Strassen’s algorithm.

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
Enter size of square matrices: 4
Enter elements of Matrix A:
1 2 3 4
5 6 7 8
9 0 1 2
3 4 5 6
Enter elements of Matrix B:
6 5 4 3
2 1 0 9
8 7 6 5
4 3 2 1
```

---

### 📤 Output Example

```bash
Resultant Matrix (A x B):
50 40 30 40
130 104 78 112
70 58 46 34
90 72 54 76
```

---

## 🧩 MUnit Test Code Overview
 
This file uses the **MUnit testing framework** to verify the correctness of `strassen()` for different cases.

- **`#define TEST_MODE`** disables the main function in `Q1_Strassen.c` during testing.  
- Multiple test cases validate correctness:
  - ✅ **2x2 matrices** – basic multiplication check  
  - ✅ **3x3 matrices** – checks zero-padding handling  
  - ✅ **1x1 single element** – base case verification  
  - ✅ **Zero matrix** – ensures multiplication by zero works  
  - ✅ **Identity matrix** – ensures A × I = A  
- Each test calls `strassen()` and compares results using `munit_assert_int()`.

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
