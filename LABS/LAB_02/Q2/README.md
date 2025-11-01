# 🧮 Q2 – LUP Solver (ADSA Lab 02)

## 📘 Problem Statement

Implement an algorithm in **C** to solve a system of linear equations **Ax = b** using **LUP Decomposition**.  
The program should decompose the coefficient matrix **A** into **L (Lower)**, **U (Upper)**, and **P (Permutation)** matrices,  
then solve for **x** using **forward** and **backward substitution**.

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q2_LUP_Solver.c` | Contains the implementation of LUP decomposition, solver, and display functions. |
| `test_Q2_LUP_Solver.c` | Contains **MUnit** test cases that automatically validate multiple LUP solver scenarios. |
| `munit.c` / `munit.h` | The testing framework used for unit tests (already provided in ADSA Lab setup). |

---

## 🧠 Code Overview

This program performs **LUP Decomposition** and solves linear systems without using dynamic memory allocation (`malloc`, `calloc`, etc.).  
It uses **partial pivoting** for numerical stability and avoids singular matrices.

### 🔍 Steps in the code:

1. **LUP_Decompose()**  
   - Decomposes matrix **A** into **L** and **U** using Gaussian elimination with partial pivoting.  
   - Stores row swaps in the **P** permutation array.  
   - Returns `-1` if the matrix is singular (non-invertible).

2. **LUP_Solve()**  
   - Uses the decomposed matrices **L**, **U**, and **P** to solve for **x** in **Ax = b**.  
   - Performs **forward substitution** for `Ly = Pb`, then **backward substitution** for `Ux = y`.

3. **print_matrix()** and **print_vector()**  
   - Utility functions to display matrices and vectors neatly.

4. **Main Function (when not in test mode)**  
   - Defines a 3×3 matrix `A` and vector `b`.  
   - Performs decomposition and solving, then displays **A**, **b**, and **x** clearly.  
   - Wrapped in `#ifndef TEST_MODE` so that MUnit tests can run without conflict.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q2_LUP_Solver.c -o Q2_LUP_Solver
./Q2_LUP_Solver
```

---

### 🧾 Sample Output (Normal Execution)

```bash
=== LUP Solver ===
A =
   2.0000   3.0000   1.0000
   4.0000   7.0000  -1.0000
  -2.0000   4.0000   5.0000
b = [ 1.0000 6.0000 -3.0000 ]

Solution of Ax = b:
x = [ 0.0556 0.6667 -1.1111 ]
```

---

## 🧩 MUnit Code Overview

The **MUnit testing file** automatically validates the correctness of the LUP solver using multiple test cases.  
It ensures that the computed solution vector **x** satisfies **A·x ≈ b** within a small error margin for each scenario.

### 🧠 Key Components:

1. **Helper Functions**
   - `copy_mat()` – Copies one matrix to another to preserve the original input.
   - `mat_vec_mul()` – Multiplies matrix `A` with vector `x` to verify results.
   - `vecs_close()` – Checks if two vectors are nearly equal (within a tolerance `EPS`).

2. **Test Cases**
   - `/regular_system` → Tests a standard 3×3 system of equations.  
   - `/identity_matrix` → Ensures that identity matrix returns `x = b`.  
   - `/singular_matrix` → Checks that singular matrices are detected correctly.  
   - `/negative_values` → Verifies correctness for negative and mixed values.  
   - `/random_invertible` → Tests solver on a random invertible matrix.

3. **Assertion Logic**
   - Each test decomposes a copy of the matrix `A`, solves for `x`, and checks that `A·x ≈ b` using MUnit assertions.  
   - If the solver produces correct results, the test passes; otherwise, it reports the mismatch.

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q2_LUP_Solver.c munit.c Q2_LUP_Solver.c -DTEST_MODE -o test_Q2_LUP_Solver
./test_Q2_LUP_Solver
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/LUP_Solver_Tests/regular_system     [ OK    ]
/LUP_Solver_Tests/identity_matrix    [ OK    ]
/LUP_Solver_Tests/singular_matrix    [ OK    ]
/LUP_Solver_Tests/negative_values    [ OK    ]
/LUP_Solver_Tests/random_invertible  [ OK    ]
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
