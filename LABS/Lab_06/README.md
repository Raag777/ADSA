# 🧮 Q – Simplex Algorithm for Linear Programming (ADSA LAB06)

## 📘 Problem Statement

Implement a program to solve **Linear Programming (LP)** problems using the **Simplex Algorithm** in standard form.

The program must:
- Construct the **Simplex tableau**
- Perform pivot operations iteratively
- Compute the **optimal objective value (Max Z)**
- Print **optimal values of all decision variables**
- Support **MUnit-based automated testing**

This lab also includes a **testable API (`simplex_solve`)** for MUnit test automation.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Simplex_Algorithm.c` | Implements the Simplex algorithm with both interactive mode and testable API. |
| `test_Simplex_Algorithm.c` | Contains multiple MUnit test cases validating different LP scenarios. |
| `munit.c` / `munit.h` | MUnit testing framework required to run automated tests. |

---

## 🧠 Code Overview

This program solves:

Maximize  
`Z = c1*x1 + c2*x2 + ... + cn*xn`

Subject to `m` linear constraints:

```sql
a11x1 + a12x2 + ... + a1nxn ≤ b1
...
am1x1 + am2x2 + ... + amnxn ≤ bm
```

### 🔹 1. Simplex Tableau Construction

The tableau includes:
- Objective function row (converted to min form by negation)
- Constraint rows
- Slack variables to convert ≤ constraints into equalities
- RHS column (b values)


### 🔹 2. Pivot Column Selection

Function:

  ```c
  int findPivotColumn(int cols, double T[MAX][MAX]);
  ```

Selects the **most negative value** in the objective row
→ This variable enters the basis.

### 🔹 3. Pivot Row Selection

Function:

  ```c
  int findPivotRow(int rows, int pc, int rhsCol, double T[MAX][MAX]);
  ```

Applies the **minimum positive ratio test**:

```nginx
RHS / pivot_column_entry
```

→ Determines which constraint leaves the basis.

### 🔹 4. Pivot Operation

Function:

  ```c
  void pivot(int rows, int cols, int pr, int pc, double T[MAX][MAX]);
  ```

Performs full **Gauss–Jordan elimination** on the pivot element.

### 🔹 5. Extracting the Solution

After no negative entries remain in row 0:

Extract variable values by detecting identity columns

Print **optimal solution** and **Max Z**

### 🔹 6. Testable API for MUnit

```c
void simplex_solve(int m, int n, double T[MAX][MAX], double *Zout, double x[]);
```

This version:
- Does NOT print tableau
- Outputs final Z and decision variable array
  → Makes automated testing possible.

---

## 🧮 Algorithm Complexity

| Component               | Complexity                               |
|------------------------|--------------------------------------------|
| Pivot column selection | O(n)                                       |
| Pivot row selection    | O(m)                                       |
| Pivot operation        | O(m × n)                                   |
| Number of iterations   | Polynomial in practice; exponential worst-case |
| **Total Time Complexity** | **O(iterations × m × n)**               |
| Space Complexity       | O(m × n) for storing the simplex tableau   |

The Simplex Algorithm is extremely efficient on practical datasets, even though its theoretical worst-case time is exponential.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Simplex_Algorithm.c -o Simplex_Algorithm
./Simplex_Algorithm
```

---

### 📥 Input Example

```bash
Enter number of variables: 2
Enter number of constraints: 2

Enter coefficients of Objective Function (Max Z):
3 5

Enter constraint matrix A and RHS b:

Constraint 1:
1 2
6

Constraint 2:
3 2
12
```

---

### 📤 Output Example

```bash
Simplex Tableau:
    -3.000     -5.000      0.000      0.000      0.000
     1.000      2.000      1.000      0.000      6.000
     3.000      2.000      0.000      1.000     12.000

Pivot at row 1, column 1

Simplex Tableau:
    -0.500      0.000      2.500      0.000     15.000
     0.500      1.000      0.500      0.000      3.000
     2.000      0.000     -1.000      1.000      6.000

Pivot at row 2, column 0

Simplex Tableau:
     0.000      0.000      2.250      0.250     16.500
     0.000      1.000      0.750     -0.250      1.500
     1.000      0.000     -0.500      0.500      3.000

Optimal solution reached.

Max Z = 16.500

Solution:
x1 = 3.000
x2 = 1.500
```

---

## 🧩 MUnit Code Overview

The file `test_Simplex_Algorithm.c` contains automated MUnit tests that verify:

- Correct construction and solving of the Simplex tableau  
- Handling of fractional optimal values  
- Multi-variable LP scenarios  
- Detection of unbounded LPs  
- Correct slack-variable behavior  
- Accurate computation of Max Z and decision variable outputs  

### 🔍 What the Tests Check

| Test Case                    | Input LP Description                                         | Expected Output                                                             |
|------------------------------|---------------------------------------------------------------|-----------------------------------------------------------------------------|
| **/test_case1**              | Simple 2-variable LP                                          | Max Z = **18**, x₁ = **3**, x₂ = **2**                                      |
| **/test_case2**              | Fractional optimal solution                                   | Max Z = **21**, x₁ = **3**, x₂ = **1.5**                                    |
| **/test_case3**              | Larger coefficients and two constraints                       | Max Z = **57**, x₁ = **3**, x₂ = **4**                                      |
| **/test_case4**              | Constraint-limited LP where only one variable contributes     | Max Z = **3**, x₁ = **0**, x₂ = **1**                                       |
| **/test_case5**              | 3-variable LP with fractional optimal point                   | Max Z ≈ **8.333**, x₁ ≈ **6.667**, x₂ ≈ **1.667**, x₃ = **0**               |
| **/test_case6_unbounded**    | LP without upper bound on objective                           | LP is **unbounded**, Z remains unchanged (**0**)                            |

### ✔ Tested Function

```c
simplex_solve(m, n, T, &Z, xvals);
```

### ✔ Assertions Used

```c
munit_assert_double_equal(actual, expected, precision);
```

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Simplex_Algorithm.c test_Simplex_Algorithm.c munit.c -o test_SA
./test_SA
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/simplex-tests/test_case1            [ OK    ] 
/simplex-tests/test_case2            [ OK    ] 
/simplex-tests/test_case3            [ OK    ] 
/simplex-tests/test_case4            [ OK    ] 
/simplex-tests/test_case5            [ OK    ] 
/simplex-tests/test_case6_unbounded  [ OK    ] 
6 of 6 (100%) tests successful, 0 (0%) test skipped.
```
