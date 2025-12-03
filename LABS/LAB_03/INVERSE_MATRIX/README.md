# 🧮 Q – Inverse of a Matrix (ADSA Lab 03)

## 📘 Problem Statement
Write a program to compute the **inverse of an n × n square matrix** using the **Gauss–Jordan Elimination** method.

Your task is to:
- Accept any valid square matrix  
- Convert it into its inverse using **row operations**  
- Detect if a matrix is **singular** (determinant = 0)  
- Output the **inverse matrix** if it exists  
- Implement **MUnit test cases** to verify correctness  

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `InverseMatrix.c` | Full implementation of Gauss–Jordan based matrix inversion. |
| `test_InverseMatrix.c` | Automated unit tests written using the MUnit framework. |
| `munit.c` / `munit.h` | Testing framework used to execute test cases. |

---

## 🧠 Code Overview

The program uses the **Gauss–Jordan Elimination technique** to compute the inverse of a matrix.

### 🔹 **1. Initialization**
An identity matrix `I` of size `n × n` is created:

```c
I[i][j] = (i == j) ? 1.0 : 0.0;
```

### 🔹 **2. Pivot Normalization**

Each pivot row is divided by the diagonal element:

```c
double pivot = A[i][i];
A[i][j] /= pivot;
I[i][j] /= pivot;
```

If a diagonal is 0, the matrix is singular, and inversion stops.

### 🔹 **3. Row Elimination**

For every pivot row, all other rows are eliminated:

```c
double factor = A[r][i];
A[r][c] -= factor * A[i][c];
I[r][c] -= factor * I[i][c];
```

After processing every row, I becomes the inverse of the original matrix.

### 🔹 **4. Singular Matrix Detection**

If any diagonal element becomes 0:

```c
if (A[i][i] == 0) return 0;
```

The function returns 0, indicating that the inverse does NOT exist.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc InverseMatrix.c -o InverseMatrix
./InverseMatrix
```

---

### 📥 Input Example

```bash
Enter order of matrix (n x n): 3
Enter matrix elements:
1 3 5
2 4 6
7 9 0
```

---

### 📤 Output Example

```bash
Inverse Matrix:
-2.4545  2.0455 -0.0909
 1.9091 -1.5909  0.1818
-0.4545  0.5455 -0.0909
```

---

## 🧩 MUnit Code Overview

The file **`test_InverseMatrix.c`** contains a comprehensive MUnit test suite designed to validate the correctness and numerical stability of the **matrix inversion algorithm** implemented in `InverseMatrix.c`.

### 🔍 What the test suite checks

| Test Name | Purpose |
|----------|----------|
| `/inverse_2x2` | Verifies inverse of a standard 2×2 matrix using known analytical values. |
| `/singular` | Ensures the function correctly identifies **singular matrices** (det = 0). |
| `/inverse_3x3` | Validates 3×3 inversion by checking whether **A × A⁻¹ = Identity**. |
| `/identity` | Confirms that the inverse of the identity matrix is the identity matrix itself. |
| `/diagonal` | Checks that diagonal matrices return the **reciprocal of diagonal elements**. |
| `/4x4_product_identity` | Tests inversion of a 4×4 matrix using matrix multiplication to verify correctness. |
| `/floating_point` | Ensures the algorithm works correctly with **floating-point (non-integer)** matrices. |
| `/near_singular` | Tests the handling of **ill-conditioned matrices** whose determinant is extremely small. |


### ✔️ Helper Functions Used in Testing

| Helper Function | Purpose |
|-----------------|----------|
| `float_equal()` | Compares two floating-point numbers using an EPS tolerance. |
| `matmul()` | Multiplies two matrices to verify `A × inverse = Identity`. |
| `is_identity()` | Confirms whether a matrix is effectively the identity matrix. |


### ✔️ Assertions Used

- `munit_assert_int()` – Used to validate:
  - Success/failure return value of `inverseMatrix()`
  - Singular matrix detection  

- `munit_assert_true()` – Used to validate:
  - Floating-point accuracy  
  - Matrix identity checks  
  - Product correctness (`A × A⁻¹ ≈ I`)

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE InverseMatrix.c test_InverseMatrix.c munit.c -o test_InverseMatrix
./test_IM
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/InverseMatrix_Tests/inverse_2x2           [ OK    ] 
/InverseMatrix_Tests/singular              [ OK    ] 
/InverseMatrix_Tests/inverse_3x3           [ OK    ] 
/InverseMatrix_Tests/identity              [ OK    ] 
/InverseMatrix_Tests/diagonal              [ OK    ] 
/InverseMatrix_Tests/4x4_product_identity  [ OK    ] 
/InverseMatrix_Tests/floating_point        [ OK    ] 
/InverseMatrix_Tests/near_singular         [ OK    ] 
8 of 8 (100%) tests successful, 0 (0%) test skipped.
```
