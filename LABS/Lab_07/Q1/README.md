# 🟢 Q1 – Ellipsoid Algorithm for Linear Programming (ADSA LAB07)

## 📘 Problem Statement

Implement the **Ellipsoid Algorithm** to determine the *feasibility* of a Linear Programming (LP) system of the form:

### *Ax ≤ b*

The program must:

- Accept **matrix A** and **vector b** as user input  
- Determine whether a **feasible point** exists  
- Return **a feasible solution** if the system is feasible  
- Return **“No feasible solution found”** otherwise  
- Support **MUnit automated testing** via `test_Ellipsoid_Algorithm.c`

---

## 📂 Code Files

| File Name                     | Description |
|------------------------------|-------------|
| `Ellipsoid_Algorithm.c`      | Implementation of the Ellipsoid Feasibility Algorithm + optional user input mode. |
| `test_Ellipsoid_Algorithm.c` | Comprehensive MUnit test suite for validating correctness across multiple LP systems. |
| `munit.c` / `munit.h`        | Lightweight testing framework used for unit test automation. |

---

## 🧠 Code Overview

The **Ellipsoid Algorithm** iteratively shrinks an ellipsoid that contains the feasible region until:

✅ A feasible solution is found  
or  
❌ The region becomes empty → infeasible  

### 🔹 Key Steps

1. **Initialize a large ellipsoid** centered at the origin.  
2. Check whether the current center violates any constraint *A_i x ≤ b_i*.  
3. If a constraint is violated:  
   - Use it as a **cutting plane**  
   - Compute the **next ellipsoid** that contains the feasible region  
4. Repeat for a maximum number of iterations.  
5. If no constraints are violated → **feasible point found**.

### 🔹 Additional Enhancements in This Implementation

- **Early contradiction detection**, e.g.:  
  - *x ≤ 1* and *x ≥ 5* → impossible  
- **Final feasibility validation**, preventing false positives  
- **Stable ellipsoid radius for numerical consistency**

---

## ⏳ Time Complexity

| Component                 | Complexity            |
|---------------------------|------------------------|
| Single ellipsoid update   | O(n²)                 |
| Maximum iterations        | O(log(1/ε))           |
| Practical total runtime   | **O(n² · log(1/ε))**  |
| Worst-case theoretical    | **O(n⁴ · L)**, where **L** is input bit-length |

**Explanation:**
- Each ellipsoid update requires matrix and vector operations → O(n²)
- Number of iterations depends on the precision requirement ε → O(log(1/ε))
- The theoretical worst case depends on numeric encoding size (bit complexity)
  making ellipsoid method polynomial-time but slower in practice.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Ellipsoid_Algorithm.c -o Ellipsoid_Algorithm
./Ellipsoid_Algorithm
```

---

### 📥 Input Example

```bash
Enter number of variables (n): 2
Enter number of constraints (m): 3

Enter matrix A (each row has 2 coefficients):
Constraint 1: 1 -1
Constraint 2: 1 -1
Constraint 3: -1 1

Enter vector b (RHS values):
b[0] = 4
b[1] = 2
b[2] = 2
```

---

### 📤 Output Example

```bash
Feasible solution found:
0.000000 0.000000
```

---

## 🧩 MUnit Code Overview

The file `test_Ellipsoid_Algorithm.c` includes tests for:

| Test Case                | Description |
|--------------------------|-------------|
| `/basic-feasible`        | Standard feasible LP |
| `/infeasible`            | Contradictory constraints |
| `/3d-feasible`           | Higher-dimension feasible system |
| `/redundant`             | System with redundant inequalities |
| `/tight-boundary`        | Feasible solution lies exactly on a boundary |
| `/zero-constraints`      | Always feasible case |

### ✔ Tested Function

```c
ellipsoidLP(n, m, A, b, x_out);
```

### ✔ Assertions Used

```c
munit_assert_int();
munit_assert_true();
```

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Ellipsoid_Algorithm.c test_Ellipsoid_Algorithm.c munit.c -o test_EA
./test_EA
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/ellipsoid-tests/basic-feasible      [ OK    ] 
/ellipsoid-tests/infeasible          [ OK    ] 
/ellipsoid-tests/3d-feasible         [ OK    ] 
/ellipsoid-tests/redundant           [ OK    ] 
/ellipsoid-tests/tight-boundary      [ OK    ] 
/ellipsoid-tests/zero-constraints    [ OK    ] 
6 of 6 (100%) tests successful, 0 (0%) test skipped.
```
