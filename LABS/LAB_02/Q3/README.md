# 🧮 Q3 – LUP Decomposition (ADSA Lab 02)

## 📘 Problem Statement

Implement an algorithm in **C** to perform **LUP Decomposition** on a square matrix **A**.
The program decomposes **A** into three matrices:

- **L** → Lower triangular matrix (with 1s on the diagonal)  
- **U** → Upper triangular matrix  
- **P** → Permutation matrix (records row swaps during pivoting)

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q3_LUP_Decomposition.c` | Contains the implementation of the LUP decomposition algorithm. |
| `test_Q3_LUP_Decomposition.c` | Contains **MUnit** test cases that automatically verify multiple LUP decomposition scenarios. |
| `munit.c` / `munit.h` | Lightweight C testing framework for automated test validation (already provided in the ADSA lab setup). |

---

## 🧠 Code Overview

This implementation avoids **dynamic memory allocation** (`malloc`) for simplicity and academic clarity.  
It uses **partial pivoting** to maintain numerical stability and handle row swaps efficiently.

### 🔍 Steps in the Code:

1. **LUP_Decompose()**  
   - Performs in-place LUP decomposition of matrix **A**.  
   - Applies partial pivoting and updates the permutation vector **P**.  
   - Returns `-1` if the matrix is **singular** or nearly singular.

2. **Main Function (Guarded by `#ifndef TEST_MODE`)**  
   - Accepts user input for **A**, performs decomposition, and displays **L**, **U**, **P**.  
   - Excluded during MUnit testing for smooth automation.

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
1 3 5
2 4 6
7 9 0
Enter vector b (3 elements):
3 1 2
```

---

### 📤 Output Example

```bash
Combined LU matrix:
    7.0000     9.0000     0.0000
    0.1429     1.7143     5.0000
    0.2857     0.8333     1.8333

L matrix:
    1.0000     0.0000     0.0000
    0.1429     1.0000     0.0000
    0.2857     0.8333     1.0000

U matrix:
    7.0000     9.0000     0.0000
    0.0000     1.7143     5.0000
    0.0000     0.0000     1.8333

Permutation vector P:
2 0 1
```

---

## 🧩 MUnit Test Code Overview

The **MUnit** testing file (`test_Q3_LUP_Decomposition.c`) automatically validates the correctness of **LUP decomposition**.

### 🧠 Key Components

#### 1. Test Cases

| Test Case | Description |
|------------|-------------|
| **Test 1 – Simple 3×3 Matrix** | Validates decomposition and solving for a basic 3×3 linear system. |
| **Test 2 – Singular Matrix** | Checks if the program correctly detects singular (non-invertible) matrices. |
| **Test 3 – Identity Matrix** | Ensures that when A = I, the solver returns x = b exactly. |
| **Test 4 – 2×2 Matrix** | Verifies solver accuracy for smaller systems with known results. |
| **Test 5 – Matrix with Negative Elements** | Tests handling of negative and near-singular matrix values. |


#### 2. Assertions and Validation

- Each test performs:
  1. **LUP Decomposition** using `LUP_Decompose()`
  2. **Validation** of results using `munit_assert_int()`.

```bash
munit_assert_int(result, ==, 0);
```
If all assertions pass →  ```[ OK ]```

If any assertion fails →  ```[ FAIL ]```

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
/LUP_Decomposition_Tests/test_simple_matrix       [ OK    ]
/LUP_Decomposition_Tests/test_singular_matrix     [ OK    ]
/LUP_Decomposition_Tests/test_identity_matrix     [ OK    ]
/LUP_Decomposition_Tests/test_2x2_matrix          [ OK    ]
/LUP_Decomposition_Tests/test_negative_elements   [ OK    ]
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
