# 🧮 Q3 – LUP Decomposition (ADSA Lab 02)

## 📘 Problem Statement

Implement an algorithm in **C** to perform **LUP Decomposition** on a square matrix **A**.  
The program decomposes **A** into three matrices:

- **L** → Lower Triangular Matrix (with 1s on the diagonal)  
- **U** → Upper Triangular Matrix  
- **P** → Permutation Vector (records row swaps during pivoting)

The decomposition satisfies the fundamental relation:

> **P × A = L × U**

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q3_LUP_Decomposition.c` | Contains the implementation of the **LUP decomposition** algorithm. |
| `test_Q3_LUP_Decomposition.c` | Contains **MUnit** test cases that automatically verify multiple decomposition scenarios. |
| `munit.c` / `munit.h` | Lightweight **C testing framework** for unit testing (already provided in the ADSA Lab setup). |

---

## 🧠 Code Overview

This implementation performs **in-place LUP decomposition** of matrix **A** using **partial pivoting**. 

### 🔹 Key Functions

1. **`LUP_Decompose()`**
   - Performs in-place decomposition of **A** into **L**, **U**, and **P**.  
   - Applies partial pivoting to ensure numerical stability.  
   - Returns `-1` if the matrix is **singular** or nearly singular.

2. **`printMatrix()`**
   - Helper function to print any square matrix neatly formatted.

3. **`main()`**
   - Reads matrix input from the user.
   - Calls `LUP_Decompose()` and displays the combined LU matrix.  
   - Separately prints **L** and **U** matrices for clear visualization.
   - Displays the **permutation vector (P)**.  
   - Wrapped with `#ifndef TEST_MODE` to prevent interference during unit testing.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q3_LUP_Decomposition.c -o Q3_LUP_Decomposition -lm
./Q3_LUP_Decomposition
```

---

### 📥 Input Example

```bash
Enter matrix size (n x n): 3
Enter matrix A (3 x 3):
1 2 3
4 7 9
5 2 0
```
---

### 📤 Output Example

```bash
Combined LU Matrix (stored together):
    5.0000     2.0000     0.0000
    0.8000     5.4000     9.0000
    0.2000     0.2963     0.3333

L (Lower Triangular) Matrix:
    1.0000     0.0000     0.0000
    0.8000     1.0000     0.0000
    0.2000     0.2963     1.0000

U (Upper Triangular) Matrix:
    5.0000     2.0000     0.0000
    0.0000     5.4000     9.0000
    0.0000     0.0000     0.3333

Permutation Vector P:
2 1 0
```

---

## 🧩 MUnit Test Code Overview

The **MUnit** test file `test_Q3_LUP_Decomposition.c` automatically validates the correctness and stability of the **LUP decomposition** algorithm.

### 🔍 Test Scenarios

| Test Case | Description |
|------------|-------------|
| **Test 1 – Simple 3×3 Matrix** | Checks standard LUP decomposition with pivoting. |
| **Test 2 – Singular Matrix** | Ensures singular matrices are properly detected. |
| **Test 3 – Identity Matrix** | Confirms decomposition leaves identity unchanged. |
| **Test 4 – 2×2 Matrix** | Tests algorithm correctness for small systems. |
| **Test 5 – Negative Elements** | Validates algorithm stability with negative entries. |


### 🧪 Key Testing Functions

- `LUP_Decompose()` – Called directly for validation.  
- `munit_assert_int()` – Ensures expected output (`0` for success, `-1` for singularity).  
- `printMatrix()` – Debug helper for internal inspection.  

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q3_LUP_Decomposition.c munit.c Q3_LUP_Decomposition.c -DTEST_MODE -o test_Q3_LUP_Decomposition -lm
./test_Q3_LUP_Decomposition
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/LUP_Decomposition_Tests/simple_matrix          [ OK    ]
/LUP_Decomposition_Tests/singular_matrix        [ OK    ]
/LUP_Decomposition_Tests/identity_matrix        [ OK    ]
/LUP_Decomposition_Tests/2x2_matrix             [ OK    ]
/LUP_Decomposition_Tests/negative_elements      [ OK    ]
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
