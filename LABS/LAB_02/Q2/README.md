# 🧮 Q2 – LUP Solver (ADSA Lab 02)

## 📘 Problem Statement

Implement a **C program** to solve a system of linear equations **Ax = b** using the **LUP Decomposition** method.  
The goal is to factor the matrix **A** into **L (Lower triangular)**, **U (Upper triangular)**, and **P (Permutation)** matrices,  
then use these factors to find the solution vector **x** efficiently and accurately.

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q2_LUP_Solver.c` | Implements the LUP decomposition and solver functions with user input for matrix **A** and vector **b**. |
| `test_Q2_LUP_Solver.c` | Contains automated unit tests written using the **MUnit** testing framework to validate the solver. |
| `munit.c` / `munit.h` | Unit testing framework used to run and verify the test cases (provided in the lab setup). |

---

## 🧠 Code Overview

This program uses **LUP Decomposition** to solve the system of equations `Ax = b` with high numerical stability by applying **partial pivoting**.  
It allows **manual user input** for both the matrix `A` and vector `b` and prints the solution in a clean formatted output.

### 🔹 Key Functions

1. **`LUP_Decompose(double A[N][N], int P[N])`**
   - Performs LUP decomposition on the given matrix `A`.
   - Uses **partial pivoting** to improve stability.
   - Returns `-1` if the matrix is **singular** or **nearly singular**.

2. **`LUP_Solve(double A[N][N], int P[N], double b[N], double x[N])`**
   - Solves for the vector `x` using forward and backward substitution.
   - Executes:
     - **Forward Substitution** → Solves `Ly = Pb`
     - **Backward Substitution** → Solves `Ux = y`

3. **`print_matrix()` & `print_vector()`**
   - Helper functions to display matrices and vectors neatly.

4. **`main()`**
   - Takes manual input for **matrix A** and **vector b**.
   - Performs decomposition and solving.
   - Displays the input, decomposition, and final result clearly.
   - Wrapped inside `#ifndef TEST_MODE` so it won’t conflict during MUnit testing.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q2_LUP_Solver.c -o Q2_LUP_Solver
./Q2_LUP_Solver
```

---

### 📥 Input Example

```bash
=== LUP Solver ===

Enter the elements of matrix A (3x3):
A[1][1]: 2
A[1][2]: 3
A[1][3]: 1
A[2][1]: 4
A[2][2]: 7
A[2][3]: -1
A[3][1]: -2
A[3][2]: 4
A[3][3]: 5

Enter the elements of vector b (3 values):
b[1]: 1
b[2]: 6
b[3]: -3
```

---

### 📤 Output Example

```bash
Input Matrix and Vector:
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

The **`test_Q2_LUP_Solver.c`** file validates the correctness of the LUP solver through **five test cases**.  
It confirms that for each input system, the computed solution vector **x** satisfies the equation **A·x ≈ b** (within a tolerance limit).

### 🧠 Components Overview

1. **Helper Functions**
   - `copy_mat()` → Copies one matrix to another for preserving input.
   - `mat_vec_mul()` → Multiplies a matrix by a vector (`A·x`) to verify output.
   - `vecs_close()` → Compares two vectors element-wise with a tolerance (`EPS`).

2. **Test Cases**

   | Test Name | Description |
   |------------|-------------|
   | `/regular_system` | Verifies the solver on a normal invertible matrix. |
   | `/identity_matrix` | Ensures that for an identity matrix, solution `x` equals `b`. |
   | `/singular_matrix` | Detects singular matrices correctly by returning `-1`. |
   | `/negative_values` | Tests solver behavior with negative and mixed numbers. |
   | `/random_invertible` | Validates correctness on a randomly invertible matrix. |

3. **Assertions Used**
   - `munit_assert_int()` → Checks if function return values are as expected.  
   - `munit_assert_true()` → Validates vector equality using approximate comparison.

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
