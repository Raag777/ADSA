# 🟢 Q2 – Interior Point Method for Linear Programming (ADSA LAB07)

## 📘 Problem Statement

Implement a **Primal–Dual Interior Point Algorithm** to solve Linear Programming (LP) problems in **standard form**:

Minimize:      **cᵀ x**  
Subject to:    **A x = b**  
               **x > 0**

The program must:

- Accept inputs for **A**, **b**, **c**, and variable counts  
- Use a **log-barrier method** with **Newton steps**  
- Ensure all variables remain **strictly positive**  
- Return:
  - Approximate solution vector **x**
  - Objective value **cᵀx**
  - Primal residual norm (accuracy check)
- Support **MUnit test automation** using `test_InteriorPoint_LP.c`

---

## 📂 Code Files

| File Name                    | Description |
|-----------------------------|-------------|
| `InteriorPoint_LP.c`        | Full implementation of the Interior Point solver with barrier updates and Newton iterations. |
| `test_InteriorPoint_LP.c`   | MUnit test suite validating feasibility handling, positivity, accuracy, and multi-constraint cases. |
| `munit.c` / `munit.h`       | MUnit testing framework used to run automated test cases. |

---

## 🧠 Code Overview

This implementation uses the **Log-Barrier Interior Point Method** combined with **Newton’s method** to solve the constrained optimization problem.

### 🔹 Key Steps in Algorithm

1. **Initialize a strictly positive starting point**  
   - Uses least-squares approximation of **(Ax = b)** 
   - Ensures positivity by shifting vector if needed  

2. **Barrier subproblem formulation**

   **phi_t(x) = t * (cᵀx) − sum(log(xᵢ))**

3. **Newton update (primal–dual)**  
   - Computes search direction using:  
     - Gradient  
     - Hessian inverse **(H⁻¹ = diag(x²))**
     - Schur complement system for dual variable update  

4. **Backtracking line search**  
   - Ensures **(x + α * dx > 0)**
   - Guarantees stable and safe Newton updates  

5. **Barrier parameter update**

   **t ← μ * t**

Until the duality gap becomes sufficiently small.

6. **Final tidy step**  
   - Very small numerical noise values are rounded to 0 for clean output  

---

## ⏳ Time Complexity

| Component                               | Complexity |
|-----------------------------------------|------------|
| Forming gradient & residuals            | O(n + m) |
| Constructing Schur complement           | O(m²·n) |
| Solving Schur system                    | O(m³) |
| Newton iterations per barrier step      | O(1)–O(log(1/ε)) |
| Number of barrier updates               | O(√n · log(1/ε)) |
| **Total Practical Complexity**          | **O(√n · (m²n + m³))** |
| Space complexity                        | O(n + m + nm) |

**Explanation:**  
The Schur complement and linear solve dominate runtime.  
Interior point methods are *polynomial time*, and extremely efficient for medium-sized dense systems.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc InteriorPoint_LP.c -o InteriorPoint_LP
./InteriorPoint_LP
```

---

### 📥 Input Example

```bash
Enter number of variables n (<=50): 3
Enter number of equality constraints m (<=50): 1
Enter matrix A (m rows, n columns):
1 1 1
Enter vector b (length m):
1
Enter objective c (length n):
1 2 3
```

---

### 📤 Output Example

```bash
Solution x (approx):
1 0 0
Objective value: 1
Primal residual norm (squared): 3.43322e-021
```

---

## 🧩 MUnit Code Overview

The file `test_InteriorPoint_LP.c` contains automated MUnit tests that validate:

| Test Case               | What It Verifies |
|-------------------------|------------------|
| **/feasible-basic**     | Checks that the solver finds a feasible solution for a simple LP and maintains positivity. |
| **/infeasible**         | Detects systems where no strictly positive solution exists (Ax = b is impossible). |
| **/degenerate**         | Ensures the algorithm converges to a boundary solution determined by the objective. |
| **/multi-constraint**   | Confirms correctness for LPs with multiple equality constraints. |
| **/identity**           | Validates exact solutions when A is the identity matrix (x = b). |

### ✔ Tested Function

```c
interior_point_lp(n, m, A, b, c, x);
```

### ✔ Assertions Used

```c
munit_assert_int();
munit_assert_true();
munit_assert_double();
```

These tests ensure correctness of:
- Feasibility detection
- Positivity constraints
- Newton step convergence
- Multi-constraint handling
- Objective minimization correctness

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE InteriorPoint_LP.c test_InteriorPoint_LP.c munit.c -o test_IP
./test_IP
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/interior-point-tests/feasible-basic     [ OK    ] 
/interior-point-tests/infeasible         [ OK    ] 
/interior-point-tests/degenerate         [ OK    ] 
/interior-point-tests/multi-constraint   [ OK    ] 
/interior-point-tests/identity           [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
