# 🧮 Q10 – Matrix Multiplication Using Strassen’s Algorithm (ADSA Lab 04)

## 📘 Problem Statement

Write a program to **multiply two matrices using Strassen’s Algorithm**.  
Strassen’s method reduces the matrix multiplication complexity from:

- **O(n³)** (naive method) → **O(n^2.81)**

It is significantly faster for large matrices and uses **divide-and-conquer** with 7 recursive multiplications instead of the usual 8.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q10_Strassen.c` | Full implementation of Strassen’s algorithm including matrix splitting, recursive computation, and combination of results. |
| `test_Q10_Strassen.c` | Automated **MUnit test suite** that validates correctness by comparing Strassen’s output with standard multiplication across multiple test cases. |
| `munit.c` / `munit.h` | MUnit testing framework used to compile and run the automated tests. |

---

## 🧠 Code Overview

The Strassen implementation in `Q10_Strassen.c` performs:

### 🔸 1. Matrix Partitioning
For an **n×n matrix**, where `n` is a power of 2, each matrix is split into 4 blocks:

```shell
A = | A11 A12 |
    | A21 A22 |

B = | B11 B12 |
    | B21 B22 |
```

### 🔸 2. Computing 7 Strassen Products

Instead of 8 multiplications, Strassen computes:

```shell
M1 = (A11 + A22)(B11 + B22)
M2 = (A21 + A22) B11
M3 = A11 (B12 - B22)
M4 = A22 (B21 - B11)
M5 = (A11 + A12) B22
M6 = (A21 - A11)(B11 + B12)
M7 = (A12 - A22)(B21 + B22)
```

### 🔸 3. Constructing Result Matrix C

```vbnet
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

### 🔸 Base Case

When the size is 1×1:

```yaml
C[0][0] = A[0][0] * B[0][0]
```

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q10_Strassen.c -o Q10_Strassen
./Q10_Strassen
```

---

### 📥 Input Example

```bash
Enter matrix size (n x n MUST be power of 2): 2

Enter matrix A:
1 2
3 4

Enter matrix B:
5 6
7 8
```

---

### 📤 Output Example

```bash
Result (Strassen Multiplication):
19 22
43 50
```

---

## 🧩 MUnit Code Overview

The file **`test_Q10_Strassen.c`** contains automated MUnit test cases that validate Strassen’s matrix multiplication by comparing it against a standard multiplication function.

### ✔ What Is Tested?

| Test Case          | Description                                |
|--------------------|--------------------------------------------|
| `/2x2/basic`       | Simple 2×2 matrix multiplication           |
| `/identity`        | Multiplication with identity matrix        |
| `/zero`            | Multiplication with zero matrix            |
| `/4x4`             | Larger 4×4 matrix correctness              |
| `/random`          | Random 2×2 correctness test                |

### ✔ How Each Test Works

Each test follows the same verification steps:

1. Construct the test matrices:

   ```c
   int A[MAX][MAX], B[MAX][MAX], C1[MAX][MAX], C2[MAX][MAX];
   ```
   
2. Compute outputs using both algorithms:

    ```c
    strassen(n, A, B, C1);
    normalMultiply(n, A, B, C2);
    ```

3. Compare every element of the matrices:

    ```c
    munit_assert_int(C1[i][j], ==, C2[i][j]);
    ```

This ensures that **Strassen’s algorithm** always produces results **identical** to classical matrix multiplication for all tested cases.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q10_Strassen.c test_Q10_Strassen.c munit.c -o test_Q10
./test_Q10
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q10_Strassen_Tests/2x2/basic        [ OK    ] 
/Q10_Strassen_Tests/identity         [ OK    ] 
/Q10_Strassen_Tests/zero             [ OK    ] 
/Q10_Strassen_Tests/4x4              [ OK    ] 
/Q10_Strassen_Tests/random           [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
