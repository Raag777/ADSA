# 🧮 Q6 – Minimum Spanning Tree (Prim’s + Kruskal) — ADSA Lab 04

## 📘 Problem Statement
Write a program to compute the **Minimum Spanning Tree (MST)** using:

- **a) Prim’s Algorithm**  
- **b) Kruskal’s Algorithm**

The graph is given in **SIF format (u v w)** where `u` = source vertex, `v` = destination vertex, `w` = weight of the edge.

The program should:
- Accept number of vertices and edges  
- Accept edges in **SIF format**  
- Build the adjacency matrix internally  
- Print the **MST edges** and **total MST weight** using both algorithms  

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q6_MST.c` | Full implementation of **Prim’s** and **Kruskal’s** MST algorithms. Includes SIF input, adjacency matrix generation, union–find structure, and MST output. |
| `test_Q6_MST.c` | Comprehensive **MUnit test suite** that validates MST weights for multiple graphs using independent MST functions (`prim_mst_weight` and `kruskal_mst_weight`). |
| `munit.c` / `munit.h` | MUnit testing framework used to compile and execute the automated tests. |

---

## 🧠 Code Overview

This program implements **two MST algorithms**:

### 🔹 1. **Prim’s Algorithm (Adjacency Matrix)**
- Starts from vertex `0`
- Uses arrays:
  - `key[]` – minimum edge weight  
  - `select[]` – visited vertices  
  - `parentNode[]` – stores MST edges
- Time Complexity: **O(V²)**  
- Suitable for dense graphs

### 🔹 2. **Kruskal’s Algorithm (Edge List + Sorting)**
- Sorts edges by weight  
- Uses **Union–Find (DSU)** with:
  - Path compression  
  - Rank optimization  
- Builds MST by adding edges that do **not** form a cycle  
- Time Complexity: **O(E log E)**  
- Suitable for sparse graphs

---

## 🔹 Graph Input Format (SIF)

Each edge is given as:

```bash
u v w
```

For example:

```bash
0 1 2
0 3 6
1 2 3
1 4 5
```

The program internally builds an **undirected adjacency matrix** and an **edge list** for Kruskal.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q6_MST.c -o Q6_MST
./Q6_MST
```

---

### 📥 Input Example

```bash
Enter number of vertices: 5
Enter number of edges: 7
Enter edges in SIF format:
0 1 2
0 3 6
1 2 3
1 4 5
1 3 8
2 4 7
3 4 9
```

---

### 📤 Output Example

```bash
MST using Prim's Algorithm:
0 -- 1  (weight = 2)
1 -- 2  (weight = 3)
1 -- 4  (weight = 5)
0 -- 3  (weight = 6)
Total Weight = 16

MST using Kruskal's Algorithm:
0 -- 1  (weight = 2)
1 -- 2  (weight = 3)
1 -- 4  (weight = 5)
0 -- 3  (weight = 6)
Total Weight = 16
```

---

## 🧩 MUnit Code Overview

The file **`test_Q6_MST.c`** contains automated MUnit test cases that independently verify the correctness of both **Prim’s** and **Kruskal’s** MST implementations.

### 🔍 What Is Tested?

| Test Case      | Graph Type                 | Expected MST Weight |
|----------------|----------------------------|----------------------|
| `test_case1`   | Lab Example Graph (5 nodes) | **16**               |
| `test_case2`   | Square Graph (4 nodes)      | **6**                |
| `test_case3`   | Complete Graph (4 nodes)    | **9**                |
| `test_case4`   | Line Graph (5 nodes)        | **10**               |

Each test performs the following steps:

1. **Constructs a fixed graph**  
   (either adjacency matrix or edge list depending on the algorithm).

2. **Calls the MST weight functions**:

   ```c
   prim_mst_weight(n, graph);
   kruskal_mst_weight(n, edges, e);
   ```

3. **Verifies correctness** using MUnit assertions:
   
   ```c
   munit_assert_int(result, ==, expected);
   ```

These test cases ensure:
- Correct MST weight
- Correct edge selection logic
- Proper DSU behavior for Kruskal
- Reliable behavior across different graph structures

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE test_Q6_MST.c munit.c -o test_Q6_MST
./test_Q6_MST
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q6_MST_tests/prim/test_case1        [ OK    ] 
/Q6_MST_tests/kruskal/test_case1     [ OK    ] 
/Q6_MST_tests/prim/test_case2        [ OK    ] 
/Q6_MST_tests/kruskal/test_case2     [ OK    ] 
/Q6_MST_tests/prim/test_case3        [ OK    ] 
/Q6_MST_tests/kruskal/test_case3     [ OK    ] 
/Q6_MST_tests/prim/test_case4        [ OK    ] 
/Q6_MST_tests/kruskal/test_case4     [ OK    ] 
8 of 8 (100%) tests successful, 0 (0%) test skipped.
```
